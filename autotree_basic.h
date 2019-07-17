#ifndef _AUTOTREE_BASIC_H_
#define _AUTOTREE_BASIC_H_

#include <map>

namespace AutoTree
{

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
struct TpEx : public Tp
{
    TpEx() : Tp{} { }
    TpEx(const TpEx& other) : Tp(other) { }
    TpEx(TpEx&& other) : Tp(std::move(other)) { }
    TpEx& operator= (const TpEx& other) {
        if (&other != this) {
            Tp::operator= (other);
        }
        return *this;
    }
    TpEx& operator= (TpEx&& other) {
        if (&other != this) {
            Tp::operator= (std::move(other));
        }
        return *this;
    }
    ~TpEx() = default;

    TpEx(const Tp& val) : Tp(val) { }
    TpEx(Tp&& val) : Tp(std::move(val)) { }
    TpEx operator= (const Tp& val) { Tp::operator=(val); return *this; }

    typename std::map< Key, TpEx<Key,Tp,Compare> > mChildren;
    typename std::map< Key, TpEx<Key,Tp,Compare> >::iterator mParentIterator;
};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using MapType = typename std::map< Key, TpEx<Key,Tp,Compare> >;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
class BasicNode : public MapType<Key,Tp,Compare>::value_type
{
public:

    std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
    insert_grandchild (const BasicNode<Key,Tp,Compare>& grandchild_node)
    {
        // Insert grandchild node into map of children
        std::pair <typename MapType<Key,Tp,Compare>::iterator, bool> pr =
            mParent_terator.second.mChildren.insert (grandchild_node);
        typename MapType<Key,Tp,Compare>::iterator& grandchild_iter = pr.first;

        // Identify pointer to (parent of new grand child)
        TpEx<Key,Tp,Compare>& grandchild_valex = child_iter->second;
        MapType<Key,Tp,Compare>& child_iter = grandchild_valex.mParentIterator;

        // Establish link from new grand child to its parent
        grandchild_iter->second.mParentIterator = child_iter;

        return pr;
    }

    std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
    insert_child (const BasicNode<Key,Tp,Compare>& child_node)
    {
        // Identify parent of self
        auto& my_parent = *mParentIterator;

        return my_parent.insert_grandchild (child_node);
    }

};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
insert (
          BasicNode<Key,Tp,Compare>& parent_node,
    const BasicNode<Key,Tp,Compare>& new_node)
{
    auto pr = parent_node.second.mChildren.insert (new_node);
    // pr.first->second.mParent = pr.second;
    typename MapType<Key,Tp,Compare>::iterator& child_iter = pr.first;
    TpEx<Key,Tp,Compare>& valex = child_iter->second;
    MapType<Key,Tp,Compare>& mpar = valex.mParent;

    auto& parent_iter = pr.second;
    mpar = parent_iter;

    return pr;
}

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

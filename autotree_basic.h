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

    typename std::map< Key, TpEx<Key,Tp,Compare> >  mChildren;
    std::pair<   const Key, TpEx<Key,Tp,Compare> >* mParentPair;
};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using MapType = typename std::map< Key, TpEx<Key,Tp,Compare> >;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using BasicNode = std::pair<   const Key, TpEx<Key,Tp,Compare> >;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
insert_child (
    BasicNode<Key,Tp,Compare>& parent_node,
    BasicNode<Key,Tp,Compare>& child_node)
{
    // Map insert
    auto& parent_map = parent_node.second.mChildren;
    auto pr = parent_map.insert (child_node);

    // Back link
    pr.first->second.mParentPair = &parent_node;

    return pr;
}

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

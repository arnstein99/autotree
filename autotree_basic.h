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

    BasicNode()
     : MapType<Key,Tp,Compare>::value_type(std::make_pair(Key{}, Tp{}))
    { }

    BasicNode(const BasicNode<Key,Tp,Compare>& other)
     : MapType<Key,Tp,Compare>::value_type(other)
    { }

    BasicNode(BasicNode<Key,Tp,Compare>&& other)
     : MapType<Key,Tp,Compare>::value_type(std::move(other))
    { }

    BasicNode<Key,Tp,Compare>&
    operator= (const BasicNode<Key,Tp,Compare>& other)
    {
        if (&other != this)
        {
            MapType<Key,Tp,Compare>::value_type::operator=(other);
        }
        return *this;
    }

    BasicNode<Key,Tp,Compare>&
    operator= (BasicNode<Key,Tp,Compare>&& other)
    {
        if (&other != this)
        {
            MapType<Key,Tp,Compare>::value_type::operator=(std::move(other));
        }
        return *this;
    }

    BasicNode(const typename MapType<Key,Tp,Compare>::value_type& raw_pair)
     : MapType<Key,Tp,Compare>::value_type(raw_pair)
    { }

    BasicNode(typename MapType<Key,Tp,Compare>::value_type&& raw_pair)
     : MapType<Key,Tp,Compare>::value_type(std::move(raw_pair))
    { }

    const Key& key() const { return this->first; }
    TpEx<Key,Tp,Compare>& valex() { return this->second; }

    std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
    insert_child (const BasicNode<Key,Tp,Compare>& child_node)
    {
        // Identify pointer to (parent of self)
        TpEx<Key,Tp,Compare>& my_valex = valex();
        typename MapType<Key,Tp,Compare>::iterator& my_parent_iterator =
            my_valex.mParentIterator;

        // Identify (part of) parent of self
        auto& vx = my_parent_iterator->second;

        return insert_grandchild (vx, child_node);
    }

};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
class BasicTree
{
public:

    BasicTree()
    {
        // The root node will have a null parent iterator 
        // because it has no parent
        BasicNode<Key,Tp,Compare> rootNode;
        rootNode.valex().mParentIterator = mRootRootMap.end();

        // The root node will be placed in a special map all by itself
        mRootMap.insert (rootNode);
    }

    typename MapType<Key,Tp,Compare>::iterator top()
    {
        auto root_iter = mRootMap.begin();
        return root_iter->second.mChildren.begin();
    }

    std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
    insert_child (const BasicNode<Key,Tp,Compare>& child_node)
    {
        // The new node becomes a child of the root node
        auto& rootNode = *(mRootMap.begin());
        auto& children_of_root = rootNode.second.mChildren;
        auto pr = children_of_root.insert (child_node);

        // Parent iterator for new node will point to root node.
        pr.first->second.mParentIterator = mRootMap.begin();

        return pr;
    }

private:

    MapType<Key,Tp,Compare> mRootMap;
    MapType<Key,Tp,Compare> mRootRootMap;

};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
insert_grandchild (
    TpEx<Key,Tp,Compare>& tpex,
    const BasicNode<Key,Tp,Compare>& grandchild_node)
{
    // Insert grandchild node into map of children
    std::pair <typename MapType<Key,Tp,Compare>::iterator, bool> pr =
        tpex.mParentIterator->second.mChildren.insert (
            grandchild_node);
    typename MapType<Key,Tp,Compare>::iterator& grandchild_iter = pr.first;

    // Identify pointer to (parent of new grand child)
    TpEx<Key,Tp,Compare>& grandchild_valex = grandchild_iter->second;
    typename MapType<Key,Tp,Compare>::iterator& child_iter =
        grandchild_valex.mParentIterator;

    // Establish link from new grand child to its parent
    grandchild_iter->second.mParentIterator = child_iter;

    return pr;
}

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

#ifndef _AUTOTREE_BASIC_H_
#define _AUTOTREE_BASIC_H_

#include <set>
#include <list>
#include <utility>

namespace AutoTree
{
template < typename Key,
           typename Tp >
using value_type = std::pair<const Key, Tp>;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
class BasicNode
{
public:

    struct BasicCompare {
        constexpr bool operator() (
	    const BasicNode<Key,Tp,Compare>& left,
	    const BasicNode<Key,Tp,Compare>& right)
	const
	{
	    return Compare().operator() (
	        left.mUserData.first, right.mUserData.first);
	}
    };

    using value_type = std::pair<const Key, Tp>;
    using SetType = std::set<BasicNode, BasicCompare >;

    BasicNode ()
     : mUserData{}, mParentNode(nullptr), mChildren()
    { }
    BasicNode (const value_type& vt)
     : mUserData(vt), mParentNode(nullptr), mChildren()
    { }

    std::pair<typename SetType::iterator, bool> insert_child (
	BasicNode<Key,Tp,Compare>& child_node)
    {
	// Set insert
	auto pr = mChildren.insert (child_node);

	// Back link
	pr.first->mParentNode = this;

	return pr;
    }

    value_type& user_access() const { return mUserData; }

private:

    BasicNode<Key,Tp,Compare> * & parent() const { return mParentNode; }
    SetType& children() const { return mChildren; }

    mutable value_type mUserData;
    mutable BasicNode<Key,Tp,Compare>* mParentNode;
    mutable SetType mChildren;

}; // class BasicNode

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
class BasicTree : public  BasicNode<Key,Tp,Compare>
{
public:

    class iterator;
    iterator start() const {
        iterator retval;
        auto set_iter =
	    new typename BasicNode<Key,Tp,Compare>::SetType::iterator (
	        this->mChildren.begin());
	retval.mStack.push_front (set_iter);
	return retval;
    };
    class iterator_beyond;

private:

    mutable iterator_beyond mBeyond;

}; // class BasicTree

template < typename Key,
           typename Tp,
           typename Compare >
class BasicTree<Key,Tp,Compare>::iterator
{
public:

    bool operator== (const iterator& other) const {
        return (*mStack[0] == *other.mStack[0]);
    }
    bool operator== (const iterator_beyond& ) const {
        return (mStack[0] == nullptr);
    }
    iterator& operator++ () {
        ++(*(mStack[0]));
	return* this;
    }
    iterator& operator-- () {
        --(*(mStack[0]));
	return* this;
    }
    iterator& pop() {
        mStack.pop();
	return *this;
    }
    iterator& push() {
        auto& my_children = mStack[0]->children();
        auto set_iter =
	    new typename BasicNode<Key,Tp,Compare>::SetType::iterator (
	        my_children.begin());
	mStack.push_front (set_iter);
	return *this;
    };

private:

    std::list< typename BasicNode<Key,Tp,Compare>::SetType::iterator* > mStack;

}; // class BasicNode::iterator

template < typename Key,
           typename Tp,
           typename Compare >
class BasicTree<Key,Tp,Compare>::iterator_beyond
{
public:

    bool operator== (
        const typename BasicNode<Key,Tp,Compare>::iterator& other)
    {
        return (other.mStack[0] == nullptr);
    }
};

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

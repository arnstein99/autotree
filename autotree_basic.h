#ifndef _AUTOTREE_BASIC_H_
#define _AUTOTREE_BASIC_H_

#include <set>
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

    class iterator;
    iterator start() const;
    class iterator_beyond;
    iterator_beyond beyond();

private:

    BasicNode<Key,Tp,Compare> * & parent() const { return mParentNode; }
    SetType& children() const { return mChildren; }

    mutable value_type mUserData;
    mutable BasicNode<Key,Tp,Compare>* mParentNode;
    mutable SetType mChildren;

}; // class BasicNode

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

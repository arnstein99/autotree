#include "autotree.h"

namespace AutoTree
{

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Node<Key,Tp,Parent,Compare,Equ>::Node (
    Node<Key,Tp,Parent,Compare,Equ>&& other)
 : mSelf(std::move(other.mSelf)), mChildren(std::move(other.mChildren))
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Node<Key,Tp,Parent,Compare,Equ>& Node<Key,Tp,Parent,Compare,Equ>::operator= (
    Node<Key,Tp,Parent,Compare,Equ>&& other)
{
    if (&other != this)
    {
        mSelf = std::move(other.mSelf);
	mChildren = std::move(other.mChildren);
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Node<Key,Tp,Parent,Compare,Equ>::Node(const Key& key, const Tp& val)
: mSelf(std::make_pair(key, val)), mChildren()
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
void Node<Key,Tp,Parent,Compare,Equ>::insert (const Key& key, const Tp& val)
{
    // Construct list with new key at the beginning and
    // a direct child of self-key at the end.
    Key keyCopy (key);
    Equ eq;
    Parent par;
    std::list<Key> klist;
    while (!eq (keyCopy, Key{}))
    {
	klist.push_back (keyCopy);
	keyCopy = par(keyCopy);
	if (eq (keyCopy, mSelf.first)) break;
    }

    // This if-test handles the case where the input key does not belong in this
    // tree.
    if (eq (keyCopy, Key{})) return;
    
    // Begin recursion
    insert (klist, val);
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
void Node<Key,Tp,Parent,Compare,Equ>::insert (
    std::list<Key>& klist, const Tp& val)
{
    // Precondition: a direct child-key is at end of klist.
    Key child_key = klist.back();
    klist.pop_back();
    if (klist.empty())  // end of recursion
    {
        mSelf.second = val;
    }
    else // continue recursion
    {
	// Insert new member into map of children, or point to existing child
	Key grand_child_key (klist.back());
	Node<Key,Tp,Parent,Compare,Equ> candidate (grand_child_key, Tp{});
	std::pair<Key, Node<Key,Tp,Parent,Compare,Equ> > pr;
	pr.first = child_key;
	pr.second = std::move(candidate);
	auto iter = mChildren.insert (std::move(pr)).first; // map iterator
	// Iterator may point to candidate, or to existing child in map.
	iter->second.insert (klist, val);
    }
}

} // namespace AutoTree

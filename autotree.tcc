#ifndef _AUTOTREE_TCC_
#define _AUTOTREE_TCC_

namespace AutoTree
{

//////////////////
// Node methods //
//////////////////

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Node<Key,Tp,Parent,Compare,Equ>::Node (
    Node<Key,Tp,Parent,Compare,Equ>&& other)
 : BasicNode<Key,Tp,Compare>(std::move(other))
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
        BasicNode<Key,Tp,Compare>::operaor= (std::move(other));
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Node<Key,Tp,Parent,Compare,Equ>::Node(const Tp& val)
: BasicNode<Key,Tp,Compare>(std::make_pair(val,Tp{}))
{
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
    if (klist.empty())  // end of recursion
    {
        Tp::operator=(val);
    }
    else // continue recursion
    {
	Key child_key = klist.back();
	klist.pop_back();

	// Insert new member into set of children, or point to existing child
	Node<Key,Tp,Parent,Compare,Equ> candidate (Tp{});
	std::pair<Key, Node<Key,Tp,Parent,Compare,Equ> > pr;
	pr.first = child_key;
	pr.second = std::move(candidate);
        // Set iterator
	auto iter = this->mChildren.insert (std::move(pr)).first;
	// Iterator may point to candidate, or to existing child in set.
	iter->second.mParent = this;
	iter->second.insert (klist, val);
    }
}

//////////////////
// Tree methods //
//////////////////

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>::Tree (
    Tree<Key,Tp,Parent,Compare,Equ>&& other)
 : Node<Key,Tp,Parent,Compare,Equ> (std::move(other))
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>& Tree<Key,Tp,Parent,Compare,Equ>::operator= (
    Tree<Key,Tp,Parent,Compare,Equ>&& other)
{
    if (&other != this)
    {
	Node<Key,Tp,Parent,Compare,Equ>::operator= (std::move(other));
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
std::pair< typename BasicTree<Key,Tp,Compare>::iterator, bool > 
Tree<Key,Tp,Parent,Compare,Equ>::insert (
    const value_type<Key,Tp>& val)
{
    // Construct list with new key at the beginning and
    // a direct child of self-key at the end...
    std::list<Key> klist;
    if (!expand (this->user_access().first, val.first, klist)) return;
    // ...that if-test handles the case where the input key does not belong in
    // this tree.
    
    // Begin recursion
    return Node<Key,Tp,Parent,Compare,Equ>::insert (klist, val);
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
bool
Tree<Key,Tp,Parent,Compare,Equ>::expand (
    const Key& base_key, const Key& new_key, std::list<Key>& klist)
{
    // Construct list with new key at the beginning and
    // a direct child of self-key at the end.
    //
    // A return value of true means success.
    Key keyCopy (new_key);
    Parent par;
    Equ eq;
    while (!eq (keyCopy, Key{}))
    {
	klist.push_back (keyCopy);
	keyCopy = par(keyCopy);
	if (eq (keyCopy, base_key)) break;
    }
    return !(eq (keyCopy, Key{}));
}

} // namespace AutoTree

#endif // _AUTOTREE_TCC_

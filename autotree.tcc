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
 : Tp(std::move(other)), mParent(nullptr),
   mChildren(std::move(other.mChildren))
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
        Tp(std::move(other));
	mParent = nullptr;
	mChildren = std::move(other.mChildren);
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Node<Key,Tp,Parent,Compare,Equ>::Node(const Tp& val)
: Tp(val), mParent(nullptr), mChildren()
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

	// Insert new member into map of children, or point to existing child
	Node<Key,Tp,Parent,Compare,Equ> candidate (Tp{});
	std::pair<Key, Node<Key,Tp,Parent,Compare,Equ> > pr;
	pr.first = child_key;
	pr.second = std::move(candidate);
	auto iter = mChildren.insert (std::move(pr)).first; // map iterator
	// Iterator may point to candidate, or to existing child in map.
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
 : Node<Key,Tp,Parent,Compare,Equ> (std::move(other)),
   mBase (std::move (other.mBase))
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
        mBase = std::move(other.mBase);
	Node<Key,Tp,Parent,Compare,Equ>::operator= (std::move(other));
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>::Tree(const Key& base)
: Node<Key,Tp,Parent,Compare,Equ>(),  mBase(base)
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
void Tree<Key,Tp,Parent,Compare,Equ>::insert (const Key& key, const Tp& val)
{
    // Construct list with new key at the beginning and
    // a direct child of self-key at the end...
    std::list<Key> klist;
    if (!expand (mBase, key, klist)) return;
    // ...that if-test handles the case where the input key does not belong in
    // this tree.
    
    // Begin recursion
    Node<Key,Tp,Parent,Compare,Equ>::insert (klist, val);
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

////////////////////////////
// Tree::iterator methods //
////////////////////////////

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>::iterator::iterator()
 : mMapIterStack(), mBelowBottom(false)
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>::iterator::~iterator()
{
    auto iter = mMapIterStack.begin();
    while (iter != mMapIterStack.end())
    {
        delete *iter;
        mMapIterStack.pop_front();
    }
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>::iterator::iterator(iterator&& other)
 : mMapIterStack(std::move(other.mMapIterStack)),
   mBelowBottom(other.mBelowBottom)
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
Tree<Key,Tp,Parent,Compare,Equ>::iterator::iterator(const iterator& other)
 : mMapIterStack(), mBelowBottom(other.mBelowBottom)
{
    for (auto mit : other.mMapIterStack)
    {
        auto new_mit = new typename MapType::iterator (mit);
        mMapIterStack.push_front (mit);
    }
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::operator= (
    Tree<Key,Tp,Parent,Compare,Equ>::iterator&& other)
{
    if (&other != *this)
    {
        mMapIterStack = std::move(other.mMapIterStack);
        mBelowBottom = other.mBelowBottom;
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::operator= (
    const Tree<Key,Tp,Parent,Compare,Equ>::iterator& other)
{
    if (&other != *this)
    {
        mMapIterStack = MapType{};
        for (auto mit : other.mMapIterStack)
        {
            auto new_mit = new typename MapType::iterator (mit);
            mMapIterStack.push_front (mit);
        }
        mBelowBottom = other.mBelowBottom;
    }
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::go_start (
    const Tree<Key,Tp,Parent,Compare,Equ>& tree)
{
    auto miter = new typename MapType::iterator();
    mMapIterStack.push_front(miter);
    *miter = tree.Children.begin();
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::go_level_start ()
{
    if (mMapIterStack.empty)
    {
        // TODO: throw an exception
    }
    MapType& parent_map = (*mMapIterStack[0])->second;
    *(mMapIterStack[0]) = parent_map.begin();
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::go_prev ()
{
    if (mMapIterStack.empty)
    {
        // TODO: throw an exception
    }
    --(*(mMapIterStack[0]));
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::go_next ()
{
    if (mMapIterStack.empty)
    {
        // TODO: throw an exception
    }
    ++(*(mMapIterStack[0]));
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::go_up ()
{
    if (mMapIterStack.empty)
    {
        // TODO: throw an exception
    }
    mMapIterStack.pop_front();
    return *this;
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
typename Tree<Key,Tp,Parent,Compare,Equ>::iterator&
Tree<Key,Tp,Parent,Compare,Equ>::iterator::go_down ()
{
    if (mMapIterStack.empty)
    {
        // TODO: throw an exception
    }
    auto miter = new typename MapType::iterator();
    *miter = this->begin();
    mMapIterStack.push_front(miter);
    return *this;
}

} // namespace AutoTree

#endif // _AUTOTREE_TCC_

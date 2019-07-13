#include "autotree.h"

namespace AutoTree
{

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
    Key keyCopy (key);
    Equ eq;
    Parent par;
    KeyStack<Key> stack;
    while (keyCopy != Key{})
    {
	if (eq (keyCopy, mSelf.first)) break;
	stack.push (keyCopy);
	keyCopy = par(keyCopy);
    }

    if (eq (keyCopy, mSelf.first)) insert (stack, val);
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
void Node<Key,Tp,Parent,Compare,Equ>::insert (
    KeyStack<Key>& stack, const Tp& val)
{
    Key key = stack.pop();
    Equ eq;
    std::pair<Key,Tp> pr (std::make_pair (key, val));
    if (eq (key, Key{}))
    {
        // mSelf = pr;
	mSelf.first = pr.first;
	mSelf.second = pr.second;
    }
    else
    {
	auto child_iter = mChildren.insert(pr).first;
	child_iter->insert (stack, val);
    }
}

} // namespace AutoTree

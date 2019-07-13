#include "autotree.h"

namespace AutoTree
{

namespace // anonymous
{

template <typename Key>
class KeyNode
{
public:
    KeyNode() = delete;
    KeyNode(KeyNode const& other) = delete;
    KeyNode& operator=(KeyNode const& other) = delete;   
    KeyNode(KeyNode&& other) = default;
    KeyNode& operator=(KeyNode&& other) = default;   
    ~KeyNode() { delete mNext; }

    KeyNode(const Key& data)
     : mData(data), mNext{} { }
    KeyNode(const Key& data, const KeyNode<Key>* next)
     : mData(data), mNext(next) { }

private:

    Key mData;
    KeyNode* mNext;
};

template <typename Key>
class KeyStack
{
public:

    KeyStack() : mTop() { }
    KeyStack(KeyStack const& other) = delete;
    KeyStack& operator=(KeyStack const& other) = delete;   
    KeyStack(KeyStack&& other) = default;
    KeyStack& operator=(KeyStack&& other) = default;   
    ~KeyStack();

    void push (const Key& key)
    {
        auto copy = new KeyNode<Key> (key, mTop);
        mTop = copy;
    }

    KeyNode<Key> pop()
    {
        KeyNode<Key>* retNode = mTop;
	if (mTop) mTop = mTop->mNext;
	Key retVal (std::move<Key>(*(retNode.mData)));
	delete retNode;
	return retVal;
    }

private:

    KeyNode<Key>* mTop;
};

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare = std::less<Key>,
          typename Equ = equal<Key> >
void insert (
    std::map<Key, Node<Key,Tp,Parent,Compare,Equ>, Compare>& children,
    KeyStack<Key>& stack,
    std::pair<const Key, Tp>& pr
)
{
    KeyNode node = stack.pop();
    if (node == KeyNode<Key>{})
    {
        mSelf = pr;
    }
    else
    {
	auto map_iter = children.insert(pr).first;
	auto sub_map = iter->mChildren;
	insert (sub_map, stack, pr);
    }
}

} // namespace anonymous

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare = std::less<Key>,
          typename Equ = equal<Key> >
Node<Key,Tp,Parent,Compare,Equ>::Node(const Key& key, const Tp& val)
: mSelf(std::make_pair(key, val)), mChildren()
{
}

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare = std::less<Key>,
          typename Equ = equal<Key> >
Node<Key,Tp,Parent,Compare,Equ>::void insert (
    const Key& key, const Tp& val)
{
    KeyStack<Key> stack;
    Key keyCopy (key);
    while (keyCopy != Key{})
    {
	if (keyCopy == mBase) break;
	stack.push (keyCopy);
	keyCopy = Parent (keyCopy);
    }
    if (keyCopy == mBase)
        insert (mChildren, stack, std::make_pair(key, val));
}

} // namespace AutoTree

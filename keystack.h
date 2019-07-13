#ifndef _KEYSTACK_H_
#define _KEYSTACK_H_

namespace AutoTree
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
    KeyNode(const Key& data, KeyNode<Key>* next)
     : mData(data), mNext(next) { }
    Key data() const { return mData; }
    KeyNode* next() const { return mNext; }

private:

    Key mData;
    KeyNode* mNext;

}; // class KeyNode

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

    Key pop()
    {
        KeyNode<Key>* retnode = mTop;
	Key retval{};
	if (mTop)
	{
	    mTop = mTop->next();
	    retval = retnode->data();
	    delete retnode;
	}
	return retval;
    }

private:

    KeyNode<Key>* mTop;

}; // class KeyStack

} // namespace AutoTree

#endif // _KEYSTACK_H_

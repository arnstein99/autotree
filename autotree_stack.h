#ifndef _AUTOTREE_STACK_H_
#define AUTOTREE_STACK_H_

namespace AutoTree
{

template <typename Typ>
class StackNode
{
public:
    StackNode() = delete;
    StackNode(StackNode const& other) = delete;
    StackNode& operator=(StackNode const& other) = delete;   
    StackNode(StackNode&& other)
     : mData(std::move(other.mData)), mNext(other.mNext)
    {
    }
    StackNode& operator=(StackNode&& other)
    {
        if (&other != this)
	{
	    mData = std::move(other.mData);
	    mNext = other.mNext;
	}
	return *this;
    }
    ~StackNode() { delete mNext; }

    StackNode(const Typ& data)
     : mData(data), mNext{} { }
    StackNode(const Typ& data, StackNode<Typ>* next)
     : mData(data), mNext(next) { }
    Typ data() const { return mData; }
    StackNode* next() const { return mNext; }

private:

    Typ mData;
    StackNode* mNext;

}; // class StackNode

template <typename Typ>
class Stack
{
public:

    Stack() : mTop() { }
    Stack(Stack const& other) = delete;
    Stack& operator=(Stack const& other) = delete;   
    Stack(Stack&& other)
     : mTop(other.mTop)
    {
    }
    Stack& operator=(Stack&& other)
    {
        if (&other != this) mTop = other.mTop;
	return *this;
    }
    ~Stack();

    void push (const Typ& t)
    {
        auto copy = new StackNode<Typ> (t, mTop);
        mTop = copy;
    }

    void pop()
    {
        StackNode<Typ>* old_node = mTop;
	if (mTop)
	{
	    mTop = mTop->next();
	    delete old_node;
	}
    }

    Typ& top()
    {
        return *mTop;
    }

private:

    StackNode<Typ>* mTop;

}; // class Stack

} // namespace AutoTree

#endif // AUTOTREE_STACK_H_

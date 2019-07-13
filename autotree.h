#ifndef _AUTOTREE_H_
#define _AUTOTREE_H_

#include <utility>
#include <map>
#include "keystack.h"

namespace AutoTree
{

template <typename Key>
struct equal
{
    constexpr bool operator() (const Key& lhs, const Key& rhs) {
        return (lhs == rhs);
    }
};

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare = std::less<Key>,
          typename Equ = equal<Key> >
class Node
{
public:

    Node() = default;
    Node(Node const& other) = delete;
    Node& operator=(Node const& other) = delete;   
    Node(Node&& other) = default;
    Node& operator=(Node&& other) = default;   
    ~Node() = default;

    Node (const Key& key, const Tp& tp);

    // TODO: provide useful return value
    void insert (const Key& key, const Tp& val);

private:

    void insert (KeyStack<Key>& stack, const Tp& val);

    std::pair<Key,Tp> mSelf;
    std::map<Key, Node<Key,Tp,Parent,Compare,Equ> > mChildren;

}; // class Node

} // namespace AutoTree

#endif // _AUTOTREE_H_

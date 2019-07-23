#ifndef _AUTOTREE_H_
#define _AUTOTREE_H_

#include <utility>
#include "autotree_basic.h"

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
class Node : public BasicNode<Key,Tp,Parent>
{
public:

    Node() = default;
    Node(Node const& other) = delete;
    Node& operator=(Node const& other) = delete;   
    Node(Node&& other);
    Node& operator=(Node&& other);
    ~Node() = default;

    Node (const Tp& tp);

private:

    void insert (std::list<Key>& klist, const Tp& val);

}; // class Node

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare = std::less<Key>,
          typename Equ = equal<Key> >
class Tree : public Node<Key,Tp,Parent,Compare,Equ>
{
public:

    Tree() = default;
    Tree(Tree const& other) = delete;
    Tree& operator=(Tree const& other) = delete;   
    Tree(Tree&& other);
    Tree& operator=(Tree&& other);
    ~Tree() = default;

    Tree (const Key& base);

    // TODO: provide useful return value
    void insert (const Key& key, const Tp& val);

    using value_type=std::pair<const Key&, Tp&>;

private:

    bool expand (
        const Key& base_key, const Key& new_key, std::list<Key>& klist);

}; // class Tree

} // namespace AutoTree

#endif // _AUTOTREE_H_

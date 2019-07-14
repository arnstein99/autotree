#ifndef _AUTOTREE_H_
#define _AUTOTREE_H_

#include <utility>
#include <list>
#include <map>

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
    Node(Node&& other);
    Node& operator=(Node&& other);
    ~Node() = default;

    Node (const Tp& tp);

protected:

    void insert (std::list<Key>& klist, const Tp& val);

private:

    Tp mVal;
    std::map<Key, Node<Key,Tp,Parent,Compare,Equ> > mChildren;

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

    typedef std::pair<const Key, Tp> value_type;
    class depth_first_iterator;
    depth_first_iterator start();
    depth_first_iterator end();

private:

    bool expand (
        const Key& base_key, const Key& new_key, std::list<Key>& klist);

    Key mBase;

}; // class Tree

template <typename Key,
          typename Tp,
          typename Parent,
          typename Compare,
          typename Equ>
class Tree<Key,Tp,Parent,Compare,Equ>::depth_first_iterator
{
public:

    depth_first_iterator();
    depth_first_iterator(depth_first_iterator const& other);
    depth_first_iterator& operator=(depth_first_iterator const& other);
    depth_first_iterator(depth_first_iterator&& other);
    depth_first_iterator& operator=(depth_first_iterator&& other);
    ~depth_first_iterator();

    depth_first_iterator next() const;
    depth_first_iterator& operator++();
    depth_first_iterator& operator++(int);
    value_type operator->();

}; // class Tree::depth_first_iterator

} // namespace AutoTree

#endif // _AUTOTREE_H_

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
class Node : public Tp
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

    Node* mParent;
    using MapType = std::map<Key, Node<Key,Tp,Parent,Compare,Equ> >;
    MapType mChildren;

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

    // Note that this differs from the standard C++ library
    typedef std::pair<const Key&, Tp&> value_type;

    class iterator;

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
class Tree<Key,Tp,Parent,Compare,Equ>::iterator
{
public:

    iterator();
    iterator(iterator const& other);
    iterator& operator=(iterator const& other);
    iterator(iterator&& other);
    iterator& operator=(iterator&& other);
    ~iterator();

    // These are in-place operations that return self.
    iterator& go_start();
    iterator& go_level_start();
    iterator& go_prev();
    iterator& go_next();
    iterator& go_up();
    iterator& go_down();

    bool at_level_end() const;
    bool at_vertical_end() const;

    value_type operator->();

private:

    using MapType = std::map<Key, Node<Key,Tp,Parent,Compare,Equ> >;
    std::list<iterator*>  mMapIterStack;
    bool mBelowBottom;

}; // class Tree::iterator

} // namespace AutoTree

#endif // _AUTOTREE_H_

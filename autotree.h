#ifndef _AUTOTREE_H_
#define _AUTOTREE_H_

#include <map>

namespace AutoTree
{

template<typename Key,
         typename Tp,
         typename Equ = AutoTree::equal<Key>,
         typename Compare = std::less<Key>,
         typename Parent,
         typename Alloc = std::allocator<pair<const Key, T> >,
         > class Node
{
public:

    Node();
    Node(Node const& other) = delete;
    Node& operator=(Node const& other) = delete;   
    Node(Node&& other) = default;
    Node& operator=(Node&& other) = default;   
    ~Node() = default;

    Node (const Key& key, const Tp& tp);

private:

    std::pair<const Key,Tp> mSelf;
    std::map<Key, Node<Key,Tp,Equ,Compare,Parent,Alloc>, Compare, Alloc >
        mChildren;

};

template<typename Key,
         typename Tp,
         typename Equ = AutoTree::equal<Key>,
         typename Compare = std::less<Key>,
         typename Parent,
         typename Alloc = std::allocator<pair<const Key, T> >,
         > class Tree
{
public:

    Tree();
    Tree(Tree const& other) = delete;
    Tree& operator=(Tree const& other) = delete;   
    Tree(Tree&& other) = default;
    Tree& operator=(Tree&& other) = default;   
    ~Tree() = default;

    Tree (const Key& base);

private:

    Key mBase;
    std::map<Key, Node<Key,Tp,Equ,Compare,Parent,Alloc>, Compare, Alloc >
        mChildren;

};

}; // namespace AutoTree

#endif // _AUTOTREE_H_

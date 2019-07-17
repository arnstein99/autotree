#ifndef _AUTOTREE_BASIC_H_
#define _AUTOTREE_BASIC_H_

#include <map>

namespace AutoTree
{

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
struct TpEx : public Tp
{
    TpEx() : Tp{} { }
    TpEx(const TpEx& other) : Tp(other) { }
    TpEx(TpEx&& other) : Tp(std::move(other)) { }
    TpEx& operator= (const TpEx& other) {
        if (&other != this) {
            Tp::operator= (other);
        }
        return *this;
    }
    TpEx& operator= (TpEx&& other) {
        if (&other != this) {
            Tp::operator= (std::move(other));
        }
        return *this;
    }
    ~TpEx() = default;

    TpEx(const Tp& val) : Tp(val) { }
    TpEx(Tp&& val) : Tp(std::move(val)) { }
    TpEx(Tp&& val) : Tp(std::move(val)) { }
    TpEx operator= (const Tp& val) { Tp::operator=(val); return *this; }

    std::map< Key, TpEx<Key,Tp,Compare> > mChildren;
    std::map< Key, TpEx<Key,Tp,Compare> >::iterator mParent;
};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using MapType = typename std::map< Key, TpEx<Key,Tp,Compare> >;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using BasicNode = typename MapType::value_type;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
std::pair < BasicNode::iterator, bool>
insert (BasicNode& parent_node, MapType::iterator& iter)
{
    auto pr = node.mChildren.insert (
}

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

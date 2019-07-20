#ifndef _AUTOTREE_BASIC_H_
#define _AUTOTREE_BASIC_H_

#include <set>
#include <utility>

namespace AutoTree
{
template < typename Key,
           typename Tp >
using value_type = std::pair<const Key, Tp>;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
class BasicNode
{
public:

    value_type<Key,Tp>& user_access() const { return mUserData; }
    struct BasicCompare {
        constexpr bool operator() (
	    const BasicNode<Key,Tp,Compare>& left,
	    const BasicNode<Key,Tp,Compare>& right)
	const
	{
	    return Compare(left.mUserData.first, right.mUserData.first);
	}
    };

private:

    BasicNode<Key,Tp,Compare> * & parent() const { return mParentNode; }
    std::set<BasicNode, BasicCompare>& children() const { return mChildren; }

    mutable value_type<Key,Tp> mUserData;
    mutable BasicNode<Key,Tp,Compare>* mParentNode;
    mutable std::set<BasicNode, BasicCompare> mChildren;

}; // class BasicNode

#if 0 // {

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
    TpEx operator= (const Tp& val) { Tp::operator=(val); return *this; }

    typename std::map< Key, TpEx<Key,Tp,Compare> >  mChildren;
    std::pair<   const Key, TpEx<Key,Tp,Compare> >* mParentPair;
};

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using MapType = typename std::map< Key, TpEx<Key,Tp,Compare> >;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
using BasicNode = std::pair<   const Key, TpEx<Key,Tp,Compare> >;

template < typename Key,
           typename Tp,
           typename Compare = std::less<Key> >
std::pair <typename MapType<Key,Tp,Compare>::iterator, bool>
insert_child (
    BasicNode<Key,Tp,Compare>& parent_node,
    BasicNode<Key,Tp,Compare>& child_node)
{
    // Map insert
    auto& parent_map = parent_node.second.mChildren;
    auto pr = parent_map.insert (child_node);

    // Back link
    pr.first->second.mParentPair = &parent_node;

    return pr;
}

#endif // } 0

} // namespace AutoTree

#endif // _AUTOTREE_BASIC_H_

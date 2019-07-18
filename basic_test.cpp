#include <iostream>
#include <string>
#include "autotree_basic.h"

using namespace std;
using namespace AutoTree;

struct Payload
{
    Payload() : value(0) { }
    Payload(int v) : value(v) { }
    int value;
};

typedef BasicNode<string, Payload> StringNode;
typedef BasicTree<string, Payload> StringTree;

int main (int, char* [])
{
    StringTree tree;

    Payload payload (1);
    StringNode a_Node(make_pair("a", payload));
    tree.insert_child (a_Node);

    // Test
    auto top_ptr = tree.top();
    auto my_text = top_ptr->first;
    auto my_val  = top_ptr->second.value;

    auto back_ptr = top_ptr->second.mParentIterator;
    auto root_node = *back_ptr;
    auto root_text = root_node.first;
    auto root_val = root_node.second.value;

    payload = 2;
    StringNode b_Node(make_pair("b", payload));
    a_Node.insert_child (b_Node);

    return 0;
}

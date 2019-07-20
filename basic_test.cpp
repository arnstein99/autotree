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
typedef StringNode StringTree;

int main (int, char* [])
{
    Payload payload (1);
    StringNode a_Node(make_pair("a", payload));

    // Test
    auto& top_ptr = a_Node.user_access();
    auto& my_text = top_ptr.first;
    auto& my_val  = ++top_ptr.second.value;
    cout << "Step 1: got " << my_text << " : " << my_val << endl;

    payload = 10;
    StringNode b_Node(make_pair("b", payload));
    auto iter = a_Node.insert_child (b_Node).first;
    auto& b_Ptr = *iter;
    auto& b_User = b_Ptr.user_access();
    cout << "Step 2: got " << b_User.first << " : " << b_User.second.value
         << endl;

    return 0;
}

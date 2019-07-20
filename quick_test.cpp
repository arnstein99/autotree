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

int test_function (StringNode& node)
{
    return node.user_access().second.value;
}

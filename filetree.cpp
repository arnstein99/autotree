#include <string>
#include "autotree.h"

using namespace std;
using namespace AutoTree;

struct Parent
{
    string operator() (const string& str);
};

typedef Tree<string, int, Parent> FileTree;

FileTree ft;

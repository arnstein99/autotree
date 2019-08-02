#include <string>
#include "autotree.h"

using namespace std;
using namespace AutoTree;

struct Parent
{
    string operator() (const string& str)
    {
	string retval{};
        auto pos = str.find_last_of('/');
	switch (pos)
	{
	case 0:
	    retval = '/';
	    break;
	case string::npos:
	    break;
	default:
	    retval = str.substr(0, pos);
	    break;
	}
	return retval;
    }
};

struct Payload
{
    Payload() : value(0) { }
    Payload(int v) : value(v) { }
    int value;
};

typedef Tree<string, Payload, Parent> FileTree;

int main (int, char* [])
{
    FileTree ft ("/a");
    auto pr1 = pair<string,Payload>("/a/b/c/d", {42});
    ft.insert (pr1);
    auto pr2 = pair<string,Payload>("/a/b/xx", {43});
    ft.insert (pr2);
    auto pr3 = pair<string,Payload>("/a/b/cc", {44});
    ft.insert (pr3);
    return 0;
}

#include "autotree.tcc"

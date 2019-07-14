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

typedef Tree<string, int, Parent> FileTree;

int main (int, char* [])
{
    FileTree ft ("/a");
    ft.insert ("/a/b/c/d", 42);
    ft.insert ("/a/b/xx", 43);
    ft.insert ("/a/b/cc", 44);
    return 0;
}

#include "autotree.tcc"

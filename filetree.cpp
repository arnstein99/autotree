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

typedef Node<string, int, Parent> FileNode;

int main (int, char* [])
{
    FileNode fn ("/a", 41);
    fn.insert ("/a/b/c/d", 42);
    fn.insert ("/a/b/cc", 43);
    return 0;
}

#include "autotree.tcc"

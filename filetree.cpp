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
	if (pos != string::npos)
	{
	    retval = str.substr(0, pos-1);
	}
	return retval;
    }
};

typedef Node<string, int, Parent> FileNode;

FileNode fn ("/", 41);

int main (int, char* [])
{
    fn.insert ("a/b/c/d", 42);
    return 0;
}

#include "autotree.tcc"

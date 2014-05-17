#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

map<string, string> mapArgs;
map<string, vector<string> > mapMultiArgs;

void ParseParameters(int argc, const char* const argv[])
{
	mapArgs.clear();
	mapMultiArgs.clear();

	for (int i = 1; i < argc; i++)
	{
		string str(argv[i]);
/* ---debug--- */ cout << "argv[" << i << "] = " << str << endl;
		string strValue;
		size_t is_index = str.find('=');
/* ---debug--- */ cout << "is_index = " << hex << is_index << endl;
		if (is_index != string::npos)
		{
			strValue = str.substr(is_index + 1);
/* ---debug--- */ cout << "strValue = " << strValue << endl;
			str = str.substr(0, is_index);
/* ---debug--- */ cout << "str = " << str << endl;
		}

		if (str[0] != '-')
		{
			cout << "Wrong param!" << endl;
			break;
		}

		mapArgs[str] = strValue;
		mapMultiArgs[str].push_back(strValue);
	}
}


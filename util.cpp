#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "util.h"

#include <boost/regex.hpp>
#include <boost/foreach.hpp>

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

		boost::regex regex("[-]{1,2}\\w+([=].+)?");
		if (!boost::regex_match(str, regex))
		{
			cout << "Wrong param: " << str << endl;
			continue;
		}

		string strValue;
		size_t is_index = str.find('=');
		if (is_index != string::npos)
		{
			strValue = str.substr(is_index + 1);
			str = str.substr(0, is_index);
		}

		if (str[0] != '-')
		{
			cout << "Wrong param!" << endl;
			break;
		}

		mapArgs[str] = strValue;
		mapMultiArgs[str].push_back(strValue);
	}

	BOOST_FOREACH(const PAIRTYPE(string, string)& entry, mapArgs)
	{
		string name = entry.first;

		// Interpret --foo as -foo as long as both are not set.
		if (name.find("--") == 0)
		{
			string singleDash(name.begin() + 1, name.end());
			if (mapArgs.count(singleDash) == 0)
			{
				mapArgs[singleDash] = entry.second;
				mapArgs.erase(name);
			}
		}
	}
}


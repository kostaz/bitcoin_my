#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/regex.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <stdarg.h>

#include "util.h"
#include "chainparams.h"

using namespace std;

map<string, string> mapArgs;
map<string, vector<string> > mapMultiArgs;

// Interpret -nofoo as -foo=0; -nofoo=0 as -foo=1 as long
// as -foo is not set.
static void InterpretNegativeSettings(string singleDashArgName, map<string, string>& map)
{
	string name = singleDashArgName;

	if (name.find("-no"))
		return;

	string positive("-");
	positive.append(name.begin() + 3, name.end());

	if (map.count(positive) != 0)
		return;

	bool val = !GetBoolArg(name, false);
	map[positive] = (val ? "1" : "0");
	map.erase(name);
}

bool GetBoolArg(const string& argName, bool fDefault)
{
	if (mapArgs.count(argName) == 0)
		return fDefault;

	string argVal = mapArgs[argName];
	if (argVal.empty())
		return true;

	int n = atoi(argVal.c_str());
	return n != 0;
}

const boost::filesystem::path& GetDataDir(bool fNetSpecific)
{
	int nNet = CChainParams::MAX_NETWORK_TYPES;

	if (fNetSpecific)
	{
		nNet = Params().NetworkID();
	}
}

void DumpMap(const map<string, string>& map)
{
	for (std::map<string, string>::const_iterator it = map.begin();
	     it != map.end(); ++it)
	{
		cout << __func__ << ": " << it->first << "=" << it->second << endl;
	}
}

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

	map<string, string> tmpMapArgs(mapArgs);

	BOOST_FOREACH(const PAIRTYPE(string, string)& entry, tmpMapArgs)
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

			name = singleDash;
		}

		InterpretNegativeSettings(name, mapArgs);
	}
}


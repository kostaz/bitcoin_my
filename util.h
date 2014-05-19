#ifndef BITCOIN_UTIL_H
#define BITCOIN_UTIL_H

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <boost/filesystem.hpp>

using namespace std;

extern std::map<string, string> mapArgs;
extern std::map<string, vector<string> > mapMultiArgs;

#define PAIRTYPE(t1, t2)	std::pair<t1, t2>

void ParseParameters(int argc, const char* const argv[]);

boost::filesystem::path GetDefaultDataDir();
const boost::filesystem::path& GetDataDir(bool fNetSpecific = true);
void ReadConfigFile(map<string, string>& mapSettingsReg,
		    map<string, vector<string> >& mapMultiSettingsReg);

bool GetBoolArg(const string& argName, bool fDefault);
string GetArg(const string& arg, const string& argDefault);

#endif // BITCOIN_UTIL_H


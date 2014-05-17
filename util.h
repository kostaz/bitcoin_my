#ifndef BITCOIN_UTIL_H
#define BITCOIN_UTIL_H

#include <string>
#include <utility>

using namespace std;

#define PAIRTYPE(t1, t2)	std::pair<t1, t2>

void ParseParameters(int argc, const char* const argv[]);
bool GetBoolArg(const string& argName, bool fDefault);

#endif // BITCOIN_UTIL_H


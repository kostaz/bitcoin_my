#ifndef BITCOIN_UTIL_H
#define BITCOIN_UTIL_H

#include <utility>

#define PAIRTYPE(t1, t2)	std::pair<t1, t2>

void ParseParameters(int argc, const char* const argv[]);

#endif // BITCOIN_UTIL_H


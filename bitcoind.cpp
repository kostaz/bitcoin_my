#include <stdio.h>
#include <boost/filesystem.hpp>

#include "noui.h"
#include "ui_interface.h"
#include "util.h"
#include "chainparams.h"

bool AppInit(int argc, char* argv[])
{
	ParseParameters(argc, argv);

	namespace fs = boost::filesystem;

	fs::path dataDir = GetDataDir();

	if (!fs::is_directory(dataDir))
	{
		fprintf(stderr, "%s: Error: Specified data directory "
			"\"%s\" does not exists.\n", __func__, mapArgs["-datadir"].c_str());
		return false;
	}

	try
	{
		ReadConfigFile(mapArgs, mapMultiArgs);
	}
	catch (std::exception& e)
	{
		fprintf(stderr, "%s: Error: Error reading config file %s.\n",
			__func__, e.what());
		return false;
	}

	if (!SelectParamsFromCommandLine())
	{
		fprintf(stderr, "%s: Invalid combination of -regtest and -tested.\n", __func__);
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	noui_connect();

	if (!AppInit(argc, argv))
	{
		fprintf(stderr, "%s: AppInit() failed.\n", __func__);
		return 1;
	}

	return 0;
}


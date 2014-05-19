#include <stdio.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#include "noui.h"
#include "init.h"
#include "ui_interface.h"
#include "util.h"
#include "chainparams.h"

void DetectShutdownThread(boost::thread_group* threadGroup)
{
	bool fShutdown = ShutdownRequested();

	while (!fShutdown)
	{
		MilliSleep(200);
		fShutdown = ShutdownRequested();
	}

	if (threadGroup)
	{
		threadGroup->interrupt_all();
		threadGroup->join_all();
	}
}

bool AppInit(int argc, char* argv[])
{
	boost::thread_group threadGroup;
	boost::thread *detectShutdownThread = 0;
	bool fRet = false;

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

	if (mapArgs.count("-?") || mapArgs.count("--help"))
	{
		fprintf(stdout, "Printing help message...\n");
		return false;
	}

	SoftSetBoolArg("-server", true);

	detectShutdownThread = new boost::thread(
		boost::bind(&DetectShutdownThread, &threadGroup));

	fRet = AppInit2(threadGroup);

	if (!fRet)
	{
		if (detectShutdownThread)
		{
			detectShutdownThread->interrupt();
		}

		threadGroup.interrupt_all();
	}

	if (detectShutdownThread)
	{
		detectShutdownThread->join();
		delete detectShutdownThread;
		detectShutdownThread = NULL;
	}

	Shutdown();

	return fRet;
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


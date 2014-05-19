#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <boost/thread.hpp>

#include "init.h"

volatile bool fRequestShutdown = false;

void StartShutdown()
{
    fRequestShutdown = true;
}

bool ShutdownRequested()
{
    return fRequestShutdown;
}

void Shutdown()
{
	// Temporary empty.
}

void HandleSIGTERM(int)
{
	fRequestShutdown = true;
}

void HandleSIGHUP(int)
{
	// fReopenDebugLog = true;
}

bool AppInit2(boost::thread_group& threadGroup)
{
	umask(077);

	struct sigaction sa;
	sa.sa_handler = HandleSIGTERM;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);

	// Reopen debug.log on SIGHUP
	struct sigaction sa_hup;
	sa_hup.sa_handler = HandleSIGHUP;
	sigemptyset(&sa_hup.sa_mask);
	sa_hup.sa_flags = 0;
	sigaction(SIGHUP, &sa_hup, NULL);
}


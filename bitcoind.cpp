#include "noui.h"
#include "ui_interface.h"
#include "util.h"

bool AppInit(int argc, char* argv[])
{
	ParseParameters(argc, argv);
	return true;
}

int main(int argc, char* argv[])
{
	noui_connect();
	AppInit(argc, argv);
	return 0;
}


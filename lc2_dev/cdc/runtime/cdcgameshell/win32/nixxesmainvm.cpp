#include "mainvm.h"

#include "../../../3rdparty/nxapp/src/nxapp.h"
#include "../cdcgameshell.h"

int NxMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine)
{
	std::string buildString = nx::app::GetBuildString();
	//nx::Log::Log("[%s] Starting Lara Croft and the Temple of Osiris %s", "Main", buildString);

	cdc::PCGameShell* gameShell = new cdc::PCGameShell();

	///@TODO
	/*cdc::PCSettings::PCSettings(&gameShell->deviceSettings);*/
	gameShell->m_appTerminateDelay = 0;
	gameShell->m_quitTime = 0;
	gameShell->m_aspectRatio = -1.f;
	gameShell->m_aspectRatioEyefinityIgnored = -1.f;

	cdc::GameShell::s_gameShell = gameShell;
	gameShell->m_finishedLoading = false;

	ParseCommandLine(lpCmdLine);

	return ERROR_SUCCESS;
}

void ParseCommandLine(char* lpCmdLine)
{
}
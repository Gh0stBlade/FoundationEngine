#include "mainvm.h"

#include "../../../3rdparty/nxapp/src/nxapp.h"
#include "../cdcgameshell.h"

int NxMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine)
{
	std::string buildString = nx::app::GetBuildString();
	//nx::Log::Log("[%s] Starting Lara Croft and the Temple of Osiris %s", "Main", buildString);

	cdc::PCGameShell* gameShell = new cdc::PCGameShell();

	cdc::GameShell::s_gameShell = gameShell;
	gameShell->m_finishedLoading = false;

	ParseCommandLine(lpCmdLine);

	bool bValue[4];
	bValue[0] = false;

	bool bDefault = true;

	//nx::settingsmanager::Load("FirstRun", SETTING_CATEGORY_NONE, bValue, &bDefault);
	//nx::DisplaySettings displaySettings();

	if (bValue[0])
	{
		//nx::settingsmanager::Save(&displaySettings);

		//cdc::NixxesActionMapper::ResetDefaultMapping();
		//cdc::NixxesActionMapper::SaveMapping();

		//nx::settingsmanager::Save("FirstRun", SETTING_CATEGORY_NONE, 0);
	}
	else
	{
		//nx::settingsmanager::Load(&displaySettings);
	}

	bool bigPictureModeActive = nx::app::IsSteamBigPictureModeActive();

	//bool fullscreen = displaySettings.m_bFullscreen;
	//displaySettings.m_bFullscreen = bigPictureModeActive ? true : fullscreen;

	//ApplyNxSettingsToCDCSettings(&displaySettings, &((cdc::PCGameShell*)cdc::GameShell::s_gameShell)->deviceSettings);

	return ERROR_SUCCESS;
}

void ParseCommandLine(char* lpCmdLine)
{
}

cdc::PCGameShell::PCGameShell()
	: GameShell(), deviceSettings()
{
	this->m_appTerminateDelay = 0;
	this->m_quitTime = 0;
	this->m_aspectRatio = -1.f;
	this->m_aspectRatioEyefinityIgnored = -1.f;
}
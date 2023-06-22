#pragma once

#include <windows.h>

#include "../cdcgameshell.h"
#include "../../cdcrender/pcshared/pcsettings.h"

extern int NxMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine);
extern void ParseCommandLine(char* lpCmdLine);

namespace cdc
{
	class PCGameShell : public cdc::GameShell
	{
	public:
		unsigned int dontPauseOnFocusLoss;
		unsigned int dontSleepOnFocusLoss;

		char gamepad[128];
		cdc::PCSettings deviceSettings;

		int m_appTerminateDelay;
		unsigned int m_quitTime;

		float m_aspectRatio;
		float m_aspectRatioEyefinityIgnored;
	};
}
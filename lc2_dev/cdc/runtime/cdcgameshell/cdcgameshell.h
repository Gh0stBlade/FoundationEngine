#pragma once

#include "../cdcsys/list.h"
#include "updateloopcallback.h"

namespace cdc
{
	class GameShell
	{
	public:
		GameShell();

		char m_commandLine[1024];
		char m_remoteHostName[128];
		char m_remoteHostIPv4[128];
		char m_startUnitName[128];
		bool m_bStartingHostFromCmdLine;
		bool m_bStartingPeerFromCmdLine;
		bool m_finishedLoading;
		bool m_garbageCollectNextFrame;
		cdc::List<cdc::UpdateLoopCallback*> m_updateCallbackList;
		int m_preferredController;
		bool m_useArgfile;
		char m_argfile[256];
		bool m_useExternalCinematics;
		bool m_useExternalResources;
		bool m_createDongleFile;
		bool m_createDumps;
		bool m_externalConnection;
		bool m_quitGame;
		bool m_pauseFlag;

		static GameShell* s_gameShell;
	};
}
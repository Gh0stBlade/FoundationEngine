#pragma once

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

		static GameShell* s_gameShell;
	};
}
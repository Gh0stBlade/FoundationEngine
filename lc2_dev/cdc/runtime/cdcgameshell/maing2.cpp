#include "cdcgameshell.h"

#include <string.h>

cdc::GameShell* cdc::GameShell::s_gameShell;

cdc::GameShell::GameShell()
	: m_updateCallbackList()
{
	this->m_commandLine[0] = 0;
	this->m_remoteHostName[0] = 0;
	this->m_remoteHostIPv4[0] = 0;
	this->m_startUnitName[0] = 0;

	this->m_bStartingHostFromCmdLine = false;
	this->m_preferredController = 0;
	this->m_createDongleFile = false;
	this->m_useArgfile = false;

	strcpy(this->m_argfile, "LC2.arg");

	this->m_useExternalCinematics = false;
	this->m_createDumps = false;
}
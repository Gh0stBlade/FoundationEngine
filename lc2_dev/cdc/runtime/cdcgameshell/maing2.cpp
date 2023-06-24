#include "cdcgameshell.h"

#include <string.h>

cdc::GameShell* cdc::GameShell::s_gameShell;

cdc::GameShell::GameShell()
	: m_commandLine{}, m_remoteHostName{}, m_remoteHostIPv4{}, m_startUnitName{}, m_bStartingHostFromCmdLine(false)
{
	///@TODO m_updateCallbackList initialization

	this->m_preferredController = 0;
	this->m_createDongleFile = false;
	this->m_useArgfile = false;

	strcpy(this->m_argfile, "LC2.arg");

	this->m_useExternalCinematics = false;
	this->m_createDumps = false;
}
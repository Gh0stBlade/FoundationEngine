#include "../src/nxapp.h"
#include "../../../runtime/cdcgameshell/win32/mainvm.h"

#include <windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!nx::app::PreInit(hInstance) /*&& nx::d3d::IsFeatureLevelOkay()*/)
	{
		exit(EXIT_FAILURE);
	}

	NxMain(hInstance, hPrevInstance, lpCmdLine);

	nx::app::Destroy();

	return ERROR_SUCCESS;
}
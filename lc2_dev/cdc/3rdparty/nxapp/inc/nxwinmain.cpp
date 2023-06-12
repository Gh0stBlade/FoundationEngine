#include "../src/nxapp.h"

#include <windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!nx::app::PreInit(hInstance) /*&& nx::d3d::IsFeatureLevelOkay()*/)
	{
		exit(EXIT_FAILURE);
	}

	return ERROR_SUCCESS;
}
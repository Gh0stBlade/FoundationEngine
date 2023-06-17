#pragma once

#include <Windows.h>
#include <stdio.h>
#include <wchar.h>

#include <cdc/runtime/cdcsys/assert.h>

namespace nx
{
	class app
	{
	public:
		static bool PreInit(HINSTANCE instance);
		static bool InitializeVersion(HINSTANCE instance);
		static void SetGameProperties(const wchar_t* gameName, int versionMajor, int versionMinor, int versionBuildMajor, int versionBuildMinor);
	};
}

typedef INT(CALLBACK* LPFNDLLFUNC1)(LPCWSTR, LPDWORD);
typedef BOOL(CALLBACK* LPFNDLLFUNC2)(PWCHAR, DWORD, UINT, PVOID);
typedef BOOL(CALLBACK* LPFNDLLFUNC3)(LPCVOID, LPCWSTR, LPVOID*, PUINT);
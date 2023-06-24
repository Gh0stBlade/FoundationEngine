#pragma once

#include <Windows.h>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <shlobj.h>

#include <cdc/runtime/cdcsys/assert.h>

namespace nx
{
	extern std::wstring* widen(std::wstring* result, const char* text, unsigned int length);

	class app
	{
	public:
		static bool PreInit(HINSTANCE instance);
		static bool InitializeVersion(HINSTANCE instance);
		static void SetGameProperties(const wchar_t* gameName, int versionMajor, int versionMinor, int versionBuildMajor, int versionBuildMinor);
		static void OpenLog();
		static const std::wstring& GetGameName();
		static const std::string& GetBuildString();
		static bool IsSteamBigPictureModeActive();
		static void Destroy();
	};
}

typedef INT(CALLBACK* LPFNDLLFUNC1)(LPCWSTR, LPDWORD);
typedef BOOL(CALLBACK* LPFNDLLFUNC2)(PWCHAR, DWORD, UINT, PVOID);
typedef BOOL(CALLBACK* LPFNDLLFUNC3)(LPCVOID, LPCWSTR, LPVOID*, PUINT);
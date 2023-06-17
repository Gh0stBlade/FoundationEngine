#include "nxapp.h"

bool s_initialized = false;

bool nx::app::PreInit(HINSTANCE instance)
{
    CDC_ASSERT_IF_TRUE(s_initialized);

    if (!nx::app::InitializeVersion(instance))
        return 0;
}

bool nx::app::InitializeVersion(HINSTANCE instance)
{
    HMODULE module = LoadLibraryW(L"version.dll");
    if (module == NULL)
        return false;

    LPFNDLLFUNC1 GetFileVersionInfoSizeW = (LPFNDLLFUNC1)GetProcAddress(module, "GetFileVersionInfoSizeW");
    if (GetFileVersionInfoSizeW == NULL)
        return false;

    LPFNDLLFUNC2 versionBuildMinor = (LPFNDLLFUNC2)GetProcAddress(module, "GetFileVersionInfoW");
    if (versionBuildMinor == NULL)
        return false;

    LPFNDLLFUNC3 VerQueryValueW = (LPFNDLLFUNC3)GetProcAddress(module, "VerQueryValueW");
    if (VerQueryValueW == NULL)
        return false;

    WCHAR moduleName[MAX_PATH];
    memset(moduleName, 0, sizeof(moduleName));
    GetModuleFileNameW(instance, moduleName, MAX_PATH);

    DWORD versionHandle = GetFileVersionInfoSizeW(moduleName, NULL);

    if (versionHandle == 0)
    {
        return false;
    }

    LPVOID data = new LPVOID[versionHandle];
    if (!versionBuildMinor(moduleName, 0, versionHandle, data))
    {
        delete[] data;
        return false;
    }

    VS_FIXEDFILEINFO* fixedInfo;
    UINT fixedInfoLength = 0;
    if (!VerQueryValueW(data, L"\\", (LPVOID*)&fixedInfo, &fixedInfoLength))
    {
        delete[] data;
        return false;
    }

    struct LANGANDCODEPAGE {
        WORD language;
        WORD codePage;
    };

    UINT translateLength = 0;
    WCHAR productNameKey[128];
    WCHAR* gameName;
    UINT gameNameLength;
    LANGANDCODEPAGE* translate;

    if (!VerQueryValueW(data, L"\\VarFileInfo\\Translation", (LPVOID*)&translate, &translateLength))
    {
        delete[] data;
        return false;
    }

    memset(&productNameKey[0], 0, sizeof(productNameKey));
    swprintf_s(productNameKey, sizeof(productNameKey) / 2, L"\\StringFileInfo\\%04x%04x\\ProductName", translate->language, translate->codePage);
    gameName = 0;
    gameNameLength = 0;

    if (!VerQueryValueW(data, productNameKey, (LPVOID*)&gameName, &gameNameLength))
    {
        delete[] data;
        return false;
    }

    nx::app::SetGameProperties(gameName, fixedInfo->dwFileVersionMS >> 16, fixedInfo->dwFileVersionMS & 0xFFFF, fixedInfo->dwFileVersionLS >> 16, fixedInfo->dwFileVersionLS & 0xFFFF);

    delete[] data;

    return true;
}

void nx::app::SetGameProperties(const wchar_t* gameName, int versionMajor, int versionMinor, int versionBuildMajor, int versionBuildMinor)
{
}

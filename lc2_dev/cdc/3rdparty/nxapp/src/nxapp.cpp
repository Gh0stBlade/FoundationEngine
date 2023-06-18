#include "nxapp.h"

#include "nxexceptions.h"
#include "nxcallstack.h"

bool s_initialized = false;

std::wstring s_GameName;

int s_BuildIdentifier;

std::string s_BuildString;

wchar_t* pSeriesNameW = NULL;

std::wstring s_BuildStringWide;

wchar_t s_GameDirectory[260];

bool nx::app::PreInit(HINSTANCE instance)
{
    CDC_ASSERT_IF_TRUE(s_initialized);

    if (!nx::app::InitializeVersion(instance))
        return 0;

    nx::exceptions::Initialize();
    nx::callstack::Initialize();
    nx::app::OpenLog();
    //nx::Log::Log("[PreInit] NxApp PreInit");
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
    unsigned int v5;
    unsigned int v6;
    std::wstring* v7;
    DWORD flags;
    char buildString[256];
    std::wstring result;

    s_GameName.assign(gameName, gameName[0] ? wcslen(gameName) : 0);

    s_BuildIdentifier = (int)((float)versionMajor * 1.0e10 + (float)versionMinor * 100000000.0 + (float)versionBuildMajor * 10000.0 + (float)versionBuildMinor * 100.0 + 32.0);
    memset(buildString, 0, sizeof(buildString));

    sprintf_s(buildString, sizeof(buildString), "v%i.%i build %i.%i_%i", versionMajor, versionMinor, versionBuildMajor, versionBuildMinor, 32);
    s_BuildString.assign(buildString, buildString[0] ? strlen(buildString) : 0);
    nx::widen(&result, buildString, strlen(buildString));

    if (s_BuildStringWide.size() >= 8)
    {
        s_BuildStringWide.clear();
    }

    s_BuildStringWide.reserve(7);

    s_BuildStringWide = result;

    if (result.size() >= 8)
    {
        result.clear();
    }

    if (SHGetFolderPathW(NULL, CSIDL_PERSONAL, 0, 0, s_GameDirectory))
    {
        s_GameDirectory[0] = 0;
    }
    else
    {
        wcscat_s(s_GameDirectory, sizeof(s_GameDirectory)>>2, L"\\");
        wcscat_s(s_GameDirectory, sizeof(s_GameDirectory)>>2, s_GameName.c_str());
        wcscat_s(s_GameDirectory, sizeof(s_GameDirectory)>>2, L"\\");
        
        CreateDirectoryW(s_GameDirectory, 0);
        
        flags = GetFileAttributesW(s_GameDirectory);
        
        if (flags == FILE_INVALID_FILE_ID || (flags & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
            s_GameDirectory[0] = 0;
        }
    }
}

void nx::app::OpenLog()
{

}

std::wstring* nx::widen(std::wstring* result, const char* text, unsigned int length)
{
    int len;
    std::wstring widened;

    widened.reserve(7);
    widened.assign(pSeriesNameW, 0);

    len = MultiByteToWideChar(CP_UTF8, 0, text, length, 0, 0);
    if (len)
    {
        if (len + 1 > widened.size())
        {
            widened.append((len + 1) - widened.size(), 0);
        }
        else
        {
            ///@TODO
            /*v5 = &widened;
            if (widened._Myres >= 8)
                v5 = (std::wstring*)widened._Bx._Ptr;
            widened._Mysize = len + 1;
            v5->_Bx._Buf[v4] = 0;*/
        }

        if (widened.size() >= 8)
            widened.shrink_to_fit();
        MultiByteToWideChar(CP_UTF8, 0, text, length, (LPWSTR)widened.c_str(), len);
    }

    *result = widened;
    if (widened.size() >= 8)
        widened.clear();

    return result;
}
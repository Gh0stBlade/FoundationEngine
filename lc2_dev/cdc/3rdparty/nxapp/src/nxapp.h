#pragma once

#include <Windows.h>

#include <cdc/runtime/cdcsys/assert.h>

namespace nx
{
	class app
	{
	public:
		static bool PreInit(HINSTANCE instance);
		static bool InitializeVersion(HINSTANCE instance);
	};
}
#pragma once

#include <stdio.h>

struct AssertInfo
{
    bool bIgnore;
    int nextWarningTime;
};

namespace cdc
{
	extern bool Assert(const char* file, int line, const char* msg, AssertInfo* const& pAssertInfo, int typeAssert);
}

extern bool s_initialized;
extern AssertInfo assertInfo;

#define CDC_ASSERT(expr) cdc::Assert(__FILE__, __LINE__, #expr, &assertInfo, 0)
#define CDC_ASSERT_IF_TRUE(value) if(value && !CDC_ASSERT(value == false)) { __debugbreak(); }
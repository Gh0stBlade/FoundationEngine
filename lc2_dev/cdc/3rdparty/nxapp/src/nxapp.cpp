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
    return false;
}

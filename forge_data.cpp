#include "forge_data.h"
#include "forge_types.h"
#include "singleton_t.h"
#include "error.h"
#include <stdio.h>
#include <string.h>


forge_status
forge_data::mode( forge_mode mode )
{
    if ( ( mode != MODE_AUTO ) && ( mode != MODE_MANUAL ) )
    {
        error& err = singleton_t<error>::instance();
        err.error_code(  ERR_UNKNOWN_MODE );
        err.message( (const char*)"Unknown MODE.  Must be MODE_MANUAL or MODE_AUTO");
    }

    m_mode = mode;
}


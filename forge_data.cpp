#include "forge_data.h"
#include "forge_types.h"
#include "singleton_t.h"
#include <stdio.h>
#include <string.h>


forge_status
forge_data::set_mode( forge_mode mode )
{
    if ( ( mode != MODE_AUTO ) && ( mode != MODE_MANUAL ) )
    {
        error_struct& err = singleton_t<error_struct>::instance();
        err.error_code = ERR_UNKNOWN_MODE;
        strncpy( err.error_message, "Unknown MODE.  Must be MODE_MANUAL or MODE_AUTO", sizeof(err.error_message));
    }

    m_mode = mode;
}


#include "forge_data.h"
#include "forge_types.h"
#include <stdio.h>


forge_status
forge_data::set_mode( forge_mode mode )
{
    if ( ( mode != MODE_AUTO ) && ( mode != MODE_MANUAL ) )
    {
        error_struct& err = error_st.instance();
    }

    m_mode = mode;
}


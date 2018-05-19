#include "error.h"
#include <string.h>

void error::message( const char* message )
{
    strncpy( m_message, message, MESSAGE_LEN - 1 );
}


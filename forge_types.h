#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

typedef unsigned short forge_err;
typedef unsigned short forge_status;
typedef unsigned short forge_mode;

static const forge_err ERR_UNKNOWN_MODE = 1;
static const forge_status SUCCESS      = 1;
static const forge_status ERR          = 0;    
static const forge_mode MODE_AUTO      = 0;
static const forge_mode MODE_MANUAL    = 1; 

struct error_struct
{
    forge_err error_code;
    char error_message[20];
};


#endif FORGE_TYPES_H

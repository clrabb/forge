#ifndef FORGE_TYPES_H
#define FORGE_TYPES_H

typedef unsigned short short_t;
typedef short_t forge_err;
typedef short_t forge_status;
typedef short_t forge_mode;

static const forge_err ERR_UNKNOWN_MODE = 1;
static const forge_status SUCCESS       = 1;
static const forge_status ERR           = 0;    
static const forge_mode MODE_AUTO       = 0;
static const forge_mode MODE_MANUAL     = 1; 

#endif FORGE_TYPES_H
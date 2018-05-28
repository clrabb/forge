#ifndef ERROR_H
#define ERROR_H

#include "forge_types.h"

class error
{
private:
    // Members
    static const short_t MESSAGE_LEN = 20;
    short_t  m_error_code;
    char m_message[ MESSAGE_LEN ];

public:
    // Ctor
    //
    error() {};

    // Setters/getters
    //
    short_t error_code() { return m_error_code; }
    void error_code( short_t code ) { m_error_code = code; }
    const char* message() { return m_message; }
    void message( const char* message );
         
private:
    // disable the usual compiler generated crap
    //
    error( const error& );
    error operator=( const error& );
};

#endif // ERROR_H


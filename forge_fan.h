#ifndef FORGE_FAN_H
#define FORGE_FAN_H

#include "forge_types.h"


class forge_fan 
{
    public:
        forge_fan( short pin )
            : m_pin( pin )
        {
            this->m_percent_open = 0;
        }

    public:
        uint8_t pin() { return this->m_pin; }
        void set_percent( short percent );
        void tick();

    private:
        uint8_t m_pin;
        short   m_percent_open;

    
            
    private:
        forge_fan( const forge_fan& );
        forge_fan& operator=( const forge_fan& );
        
};

    


#endif // FORGE_FAN_H

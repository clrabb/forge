#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

class button;


class button_state
{
public:
    button_state() {}
    
    virtual void update_setpoint( button* btn ) = 0;
    virtual void button_pressed( button* btn ) = 0;
    virtual bool is_unpushed() = 0;
    virtual bool is_pushed() = 0;
    virtual bool is_latched() = 0;
};

class button_state_unpushed : public button_state
{
public:
    button_state_unpushed() {}

    virtual void update_setpoint( button* btn );
    virtual void button_pressed( button* btn );
    virtual bool is_unpushed() { return true; }
    virtual bool is_pushed() { return false; }
    virtual bool is_latched() { return false; }
};

class button_state_pushed : public button_state
{
private:
    bool m_has_updated_setpoint;

    bool has_updated_setpoint() { return m_has_updated_setpoint; }
    void has_updated_setpoint( bool val ) { m_has_updated_setpoint = val; }
    bool has_not_updated_setpoint() { return this->has_updated_setpoint() == false; }
    
public:
    button_state_pushed() { this->has_updated_setpoint( false ); }
    
    virtual void update_setpoint( button* btn );
    virtual void button_pressed( button* btn );
    virtual bool is_unpushed() { return false; }
    virtual bool is_pushed() { return true; }
    virtual bool is_latched() { return false; }
};





class button_state_latched : public button_state_pushed
{
public:
    button_state_latched() {}
    
    virtual void update_setpoint( button* btn );
    virtual void button_pressed( button* btn );
    
    virtual bool is_unpushed() { return false; }
    virtual bool is_pushed() { return true; }
    virtual bool is_latched() { return true; }
};

#endif // BUTTON_STATE_H

#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

class button_state
{
public:
    button_state() {}
    virtual button_state* update_setpoint() = 0;
    virtual bool is_unpushed() = 0;
    virtual bool is_pushed() = 0;
    virtual bool is_latched() = 0;
};

class button_state_pushed : public button_state
{
public:
    button_state_pushed() {}
    virtual button_state* update_setpoint();

    virtual bool is_unpushed() { return false; }
    virtual bool is_pushed() { return true; }
    virtual bool is_latched() { return false; }
};


class button_state_unpushed : public button_state
{
public:
    button_state_unpushed() {}
    virtual button_state* update_setpoint();
    
    virtual bool is_unpushed() { return true; }
    virtual bool is_pushed() { return false; }
    virtual bool is_latched() { return false; }
};


class button_state_latched : public button_state_pushed
{
public:
    button_state_latched() {}
    virtual button_state* update_setpoint();

    virtual bool is_unpushed() { return false; }
    virtual bool is_pushed() { return true; }
    virtual bool is_latched() { return true; }
};

#endif // BUTTON_STATE_H

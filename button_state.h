#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

class button;


class button_state
{
protected:
    virtual void switch_to_pressed( button* btn );
    virtual void switch_to_unpressed( button* btn );
    virtual void switch_to_latched( button* btn );

public:
    button_state() {}
    
    virtual void button_pressed( button* btn )   = 0;
    virtual void button_unpressed( button* btn ) = 0;
    virtual void reset_state() {}
    virtual bool is_unpressed() = 0;
    virtual bool is_pressed()   = 0;
    virtual bool is_latched()   = 0;
    void update( button* btn );

private:
    button_state( button_state& );
    button_state& operator=( button_state& );
};

class button_state_unpressed : public button_state
{    
public:
    button_state_unpressed() {}

    virtual void button_pressed( button* btn );
    virtual void button_unpressed( button* btn );
    virtual bool is_unpressed() { return true;  }
    virtual bool is_pressed()   { return false; }
    virtual bool is_latched()  { return false; }
};

class button_state_pressed: public button_state
{
private:
    unsigned long   m_first_pressed_mills;
    bool            m_has_updated_setpoint;
                 
    void            first_pressed_mills( unsigned long mills ) { m_first_pressed_mills = mills; }
    bool            is_first_pressed();
    bool            should_latch();
    bool            has_updated_setpoint() { return m_has_updated_setpoint; }
    void            has_updated_setpoint( bool updated ) { m_has_updated_setpoint = updated; }
    void            switch_to_latched_if_needed( button* btn );
    
protected:
    unsigned long   mills_since_first_pressed();
    unsigned long   first_pressed_mills() { return m_first_pressed_mills; }    
     
public:    
    button_state_pressed();
    virtual void button_pressed( button* btn );
    virtual void button_unpressed( button* btn );
    virtual bool is_unpressed() { return false; }
    virtual bool is_pressed()   { return true;  }
    virtual bool is_latched()   { return false; }
    virtual void reset_state() override;

private:
    button_state_pressed( button_state_pressed& );
    button_state_pressed& operator=( button_state_pressed& );
};



class button_state_latched : public button_state_pressed
{
private:
    unsigned long m_last_sp_change_mills;

    unsigned long last_sp_change_mills() { return m_last_sp_change_mills; }
    void last_sp_change_mills( unsigned long mills ) { m_last_sp_change_mills = mills; }
    
public:
    button_state_latched() {}
    
    virtual bool is_latched() override { return true; }
    virtual void button_pressed( button* btn ) override;
    virtual void reset_state() override;
};

#endif // BUTTON_STATE_H

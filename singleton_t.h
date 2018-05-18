#ifndef SINGLETON_T_H
#define SINGLETON_T_H

template <class T>
class singleton
{
private:
    static singleton<T>* s_instance;

public:
    static singleton<T>* instance() { return s_instance; }
    singleton<T>(){}; // ctor

private:
    singleton(const singleton&);             // disable copy ctor
    singleton& operator=(const singleton&);  //disable assignment op
};

#endif // SINGLETON_T_H

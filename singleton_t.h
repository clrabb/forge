#ifndef SINGLETON_T_H
#define SINGLETON_T_H

template <class T>
class singleton_t
{
private:
    static T* s_instance;

public:
    static T& instance() { return *s_instance; }
    singleton_t<T>(T* i){ singleton_t<T>::s_instance = i; } // ctor

private:
    singleton_t(const singleton_t&);             // disable copy ctor
    singleton_t& operator=(const singleton_t&);  //disable assignment op
};

template<typename T> T* singleton_t<T>::s_instance;

#endif // SINGLETON_T_H

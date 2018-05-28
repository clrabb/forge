#ifndef SINGLETON_T_H
#define SINGLETON_T_H

// This is a templatized class that deals with the singleton pattern.
// For what this is see: https://en.wikipedia.org/wiki/Singleton_pattern
// I didn't feel like writing it over and over since many variables
// are global.  Instead I just wrote a template you can use to 
// make anything a singleton.
//
template <class T>
class singleton_t
{
private:
    static T* s_instance;

public:
    static T& instance() { return *s_instance; }
    singleton_t<T>(T* i){ singleton_t<T>::s_instance = i; } // ctor

private:
    singleton_t( const singleton_t& );             // disable copy ctor
    singleton_t& operator=( const singleton_t& );  //disable assignment op
};

template<typename T> T* singleton_t<T>::s_instance;

#endif // SINGLETON_T_H


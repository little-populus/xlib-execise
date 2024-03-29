#include "header/thread.hpp"
#include <pthread.h>
thread::thread()
{
}
thread::thread(f foo, argu arg) : _arg(arg), _fucntion(foo)
{
}
pthread_t thread::run()
{
    pthread_create(&_id, nullptr, _fucntion, _arg);
    return _id;
}
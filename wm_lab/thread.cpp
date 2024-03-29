#include <pthread.h>
struct thread
{
    using f = void *(*)(void *);
    using argu = void *;
    thread()
    {
    }
    thread(f foo, argu arg) : _arg(arg), _fucntion(foo)
    {
    }
    pthread_t run()
    {
        pthread_create(&_id, nullptr, _fucntion, _arg);
        return _id;
    }
    f _fucntion;
    argu _arg;
    pthread_t _id;
};
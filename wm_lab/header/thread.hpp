#include <pthread.h>
struct thread
{
    using f = void *(*)(void *);
    using argu = void *;
    thread();
    thread(f foo, argu arg);
    pthread_t run();
    f _fucntion;
    argu _arg;
    pthread_t _id;
};
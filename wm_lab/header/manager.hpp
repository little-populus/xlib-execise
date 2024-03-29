#include "thread.hpp"
#include <X11/Xlib.h>
#include <iostream>
void *foo(void *);
struct Manager
{
    Manager();
    void run();

    Display *_display;
};
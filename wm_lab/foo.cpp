#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
void *foo(void *arg)
{
    auto display = XOpenDisplay(":0");
    auto scr = XDefaultScreenOfDisplay(display);
    auto window = XCreateSimpleWindow(display, RootWindowOfScreen(scr), 0, 0, 100, 100, 0, XWhitePixelOfScreen(scr),
                                      XBlackPixelOfScreen(scr));
    XSelectInput(display, window, ButtonPressMask | ButtonReleaseMask | ExposureMask);
    XMapWindow(display, window);
    XFlush(display);
    XEvent event;
    int x = 10;
    while (x)
    {
        XNextEvent(display, &event);
        switch (event.type)
        {
        case Expose:
            std::cout << "Hello World\n";
            break;
        default:
            std::cout << "default\n";
            break;
        }
        sleep(1);
        --x;
    }
    pthread_exit((void *)0);
}
#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
void *foo(void *arg)
{
    std::cout << "in thread\n";
    auto display = XOpenDisplay(nullptr);
    if (!display)
        std::cout << "disconnected\n";
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
            std::cout << "expose" << x << '\n';
            break;
        default:
            std::cout << "default\n";
            break;
        }
        --x;
    }
    XUnmapWindow(display, window);
    XCloseDisplay(display);
    pthread_exit((void *)0);
}
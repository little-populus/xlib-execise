#include "header/manager.hpp"
#include "header/foo.hpp"
#include "header/thread.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>
#include <unistd.h>

Manager::Manager() : _display(XOpenDisplay(nullptr))
{
    if (!_display)
        std::cout << "error in opening display\n";
}
void Manager::run()
{
    XSelectInput(_display, XDefaultRootWindow(_display), SubstructureRedirectMask | SubstructureNotifyMask);
    XEvent event;
    thread t{foo, (void *)1};
    t.run();
    while (1)
    {
        XNextEvent(_display, &event);
        switch (event.type)
        {
        case CreateNotify:
            std::cout << "window created\n";
            break;
        case DestroyNotify:
            std::cout << "window destroyed\n";
            break;
        case MapNotify:
            std::cout << "window mapped\n";
            break;
        case UnmapNotify:
            std::cout << "window unmapped\n";
            break;
        default:
            std::cout << "default option in manager\n";
        }
    }
}
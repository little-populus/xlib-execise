#include "header/foo.hpp"
#include "header/thread.hpp"
#include <X11/Xlib.h>
#include <iostream>
struct Manager
{
    Manager() : _display(XOpenDisplay(":0"))
    {
        if (!_display)
            std::cout << "error in opening display\n";
    }
    void run()
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
            default:
                std::cout << "default option in manager\n";
            }
        }
    }

    Display *_display;
};
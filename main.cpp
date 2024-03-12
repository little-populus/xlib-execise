#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>

int count1, count2;
int main(int argc, char **argv)
{
    std::fstream file("log.txt", std::ios::in | std::ios::app);
    auto con = XOpenDisplay(NULL);
    if (!con)
        std::cerr << "connection failure\n";
    // std::cout << XDisplayString(con) << '\n';
    XEvent *event = new XEvent;
    auto num = XDefaultScreen(con);
    auto screen = XScreenOfDisplay(con, num);
    auto root = XRootWindowOfScreen(screen);
    auto window = XCreateSimpleWindow(con, root, (1920 - 300) / 2, (1080 - 300) / 2, 300, 300, 0,
                                      BlackPixelOfScreen(screen), WhitePixelOfScreen(screen));
    XRaiseWindow(con, window);
    XMapWindow(con, window);
    XFlush(con);
    XSelectInput(con, window, ExposureMask | ButtonPressMask | ButtonReleaseMask);
    while (true)
    {
        XNextEvent(con, event);
        switch (event->type)
        {
        case Expose: {
            file << "hello world" << count1++ << '\n';
            file.flush();
            XFlush(con);
        }
        break;
        default: {
            file << "Not determined yet" << count2++ << '\n';
            file.flush();
        }
        }
    }
    delete event;
    file.close();
    XFree(con);
    return 0;
}
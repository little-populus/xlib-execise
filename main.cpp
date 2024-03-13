#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>

int count1, count2;
int main(int argc, char **argv)
{
    int a[10];
    std::cout << std::size(a) << '\n';
    // std::fstream file("log.txt", std::ios::in | std::ios::app);
    auto con = XOpenDisplay(NULL);
    if (!con)
        std::cerr << "connection failure\n";
    // std::cout << XDisplayString(con) << '\n';
    XEvent *event = new XEvent;
    auto num = XDefaultScreen(con);
    auto screen = XScreenOfDisplay(con, num);
    auto root = XRootWindowOfScreen(screen);
    auto window =
        XCreateSimpleWindow(con, root, 0, 0, 300, 300, 0, BlackPixelOfScreen(screen), WhitePixelOfScreen(screen));
    // XRaiseWindow(con, window);
    Visual();
    XMapWindow(con, window);
    // XSetNormalHints(con, window,(XSizeHints[]){{.flags = PPosition | PSize, .x = (1920 - 300) / 2, .y = (1080 - 300)
    // / 2}});
    XMoveWindow(con, window, (1920 - 300) / 2, (1080 - 300) / 2);
    XFlush(con);
    XSelectInput(con, window, ExposureMask | ButtonPressMask | ButtonReleaseMask);
    XGCValues();
    GC gc = XCreateGC(con, window, GCForeground | GCBackground | GCCapStyle | GCJoinStyle,
                      (XGCValues[]){{.foreground = XWhitePixelOfScreen(screen),
                                     .background = XBlackPixelOfScreen(screen),
                                     .cap_style = CapButt,
                                     .join_style = JoinBevel,
                                     .fill_style = FillSolid}});
    XSetLineAttributes(con, gc, 2, LineSolid, CapRound, JoinRound);
    auto sub1 = XCreateSimpleWindow(con, window, 0, 0, 200, 200, 0, XBlackPixelOfScreen(screen), 0xff0000);
    auto sub2 = XCreateSimpleWindow(con, window, 0, 0, 100, 100, 0, XBlackPixelOfScreen(screen), 0x00ff00);
    XMapWindow(con, sub1);
    XMapWindow(con, sub2);
    XFlush(con);
    bool x = false;
    while (true)
    {
        XNextEvent(con, event);
        switch (event->type)
        {
        case Expose: {
            // file << "hello world" << count1++ << '\n';
            // file.flush();
            int x, y;
            unsigned int width, length, border, depth;
            Window get;
            XGetGeometry(con, window, &get, &x, &y, &width, &length, &border, &depth);
            XDrawLine(con, window, gc, width / 4, length / 2, width / 4 * 3, length / 2);
            XFlush(con);
        }
        break;
        case ButtonPress: {
            // file << "Not determined yet" << count2++ << '\n';
            // file.flush();
            x = !x;
            std::cout << std::boolalpha;
            std::cout << x << '\n';
            x ? XRaiseWindow(con, sub1) : XRaiseWindow(con, sub2);
            XFlush(con);
        }
        }
    }
    delete event;
    // file.close();
    XFree(con);
    return 0;
}
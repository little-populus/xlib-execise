#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstring>
#include <iostream>
#include <tile_stipple.hxx>
int main()
{
    XEvent event;
    auto con = XOpenDisplay(nullptr);
    auto num = XDefaultScreen(con);
    auto scr = XScreenOfDisplay(con, num);
    auto window = XCreateSimpleWindow(con, XRootWindowOfScreen(scr), 0, 0, 300, 300, 0, XBlackPixelOfScreen(scr),
                                      XWhitePixelOfScreen(scr));
    XMapWindow(con, window);
    XMoveWindow(con, window, (1920 - 300) / 2, (1080 - 300) / 2);
    XSelectInput(con, window, ButtonPressMask | ButtonReleaseMask | ExposureMask);
    XFlush(con);
    auto pixmap1 = XCreatePixmap(con, window, 50, 50, XDefaultDepthOfScreen(scr));
    auto pixmap2 = XCreatePixmap(con, window, 20, 50, XDefaultDepthOfScreen(scr));
    auto gc1 = XCreateGC(con, window, GCForeground | GCBackground | GCCapStyle | GCJoinStyle,
                         (XGCValues[]){{.foreground = 0x00ff00,
                                        .background = XBlackPixel(con, XDefaultScreen(con)),
                                        .cap_style = CapButt,
                                        .join_style = JoinBevel}});
    XFillRectangle(con, pixmap1, gc1, 0, 0, 50, 50);
    XSetForeground(con, gc1, 0xff0000);
    XFillRectangle(con, pixmap1, gc1, 25, 25, 25, 25);
    XFillRectangle(con, pixmap1, gc1, 0, 0, 25, 25);
    XFillRectangle(con, pixmap2, gc1, 0, 0, 50, 10);
    XSetForeground(con, gc1, 0x0000ff);
    XFillRectangle(con, pixmap2, gc1, 0, 10, 50, 10);
    auto gc2 = CreateTile(con, window, pixmap1);
    auto gc3 = CreateTile(con, window, pixmap2);
    XFontStruct *font_info = XLoadQueryFont(con, "fixed");
    XSetFont(con, gc3, font_info->fid);
    while (true)
    {
        XNextEvent(con, &event);
        switch (event.type)
        {
        case Expose: {
            XFillRectangle(con, window, gc1, 0, 0, 100, 100);
            XFlush(con);
            break;
        }
        case ButtonPress: {
            XFillRectangle(con, window, gc2, 100, 100, 75, 75);
            XFlush(con);
            break;
        }
        case ButtonRelease: {
            XSetForeground(con, gc2, 0x0000ff);
            XDrawString(con, window, gc2, 130, 50, "Hello world", strlen("Hello world"));
            XFlush(con);
            break;
        }
        default: {
            std::cout << "world\n";
        }
        }
    }
    return 0;
}
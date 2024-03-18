#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstring>
#include <do_n.hxx>
#include <iostream>
#include <tile_stipple.hxx>

template <typename Tp, typename... Arg> void func(Tp tp, Arg... arg)
{
    tp(arg...);
}

int main()
{
    XEvent *event = new XEvent;
    auto con = XOpenDisplay(nullptr);
    auto num = XDefaultScreen(con);
    auto scr = XScreenOfDisplay(con, num);
    auto window = XCreateSimpleWindow(con, XRootWindowOfScreen(scr), 0, 0, 300, 300, 0, XBlackPixelOfScreen(scr),
                                      XWhitePixelOfScreen(scr));
    XChangeWindowAttributes(
        con, window, CWBitGravity | CWWinGravity | CWBackingStore,
        (XSetWindowAttributes[]){
            {.bit_gravity = SouthEastGravity, .win_gravity = NorthWestGravity, .backing_store = NotUseful}});
    XMapWindow(con, window);
    XMoveWindow(con, window, (1920 - 300) / 2, (1080 - 300) / 2);
    XSelectInput(con, window, ButtonPressMask | ButtonReleaseMask | ExposureMask);
    auto sub = CreateSubwindow(con, window);
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
    object_call_n foo(XFillRectangle, 6, con, window, gc1, 0, 0, 100, 100);
    XMapWindow(con, sub);
    std::cout << std::boolalpha;
    std::cout << XDoesBackingStore(scr) << ' ' << XDoesSaveUnders(scr) << '\n';
    while (true)
    {
        XNextEvent(con, event);
        switch (event->type)
        {
        case Expose: {
            // XFillRectangle(con, window, gc1, 0, 0, 100, 100);
            static int x = 0;
            if (++x == 1)
                func(XFillRectangle, con, window, gc1, 0, 0, 100, 100);
            XDrawString(con, sub, gc1, 1, 10, "subwindow", strlen("subwindow"));
            XFlush(con);
            break;
        }
        case ButtonPress: {
            XUnmapWindow(con, sub);
            XFlush(con);
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
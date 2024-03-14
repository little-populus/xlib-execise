#include <X11/X.h>
#include <X11/Xlib.h>
#include <tile_stipple.hxx>
GC CreateTile(Display *con, Window window, Pixmap pixmap)
{
    auto gc = XCreateGC(con, window, GCForeground | GCBackground | GCCapStyle | GCJoinStyle,
                        (XGCValues[]){{.foreground = 0x00ff00,
                                       .background = XBlackPixel(con, XDefaultScreen(con)),
                                       .cap_style = CapButt,
                                       .join_style = JoinBevel}});
    XSetFillStyle(con, gc, FillTiled);
    XSetTile(con, gc, pixmap);
    return gc;
}
GC CreateStipple(Display *con, Window window, Pixmap pixmap)
{
    auto gc = XCreateGC(con, window, GCForeground | GCBackground | GCCapStyle | GCJoinStyle,
                        (XGCValues[]){{.foreground = 0x0000ff,
                                       .background = XBlackPixel(con, XDefaultScreen(con)),
                                       .cap_style = CapButt,
                                       .join_style = JoinBevel}});
    XSetFillStyle(con, gc, FillOpaqueStippled);
    XSetStipple(con, gc, pixmap);
    return gc;
}
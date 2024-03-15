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
Window CreateSubwindow(Display *con, Window window)
{
    auto sub = XCreateWindow(con, window, 200, 200, 100, 100, 0, XDefaultDepth(con, XDefaultScreen(con)),
                             CopyFromParent, XDefaultVisual(con, XDefaultScreen(con)), CWBackPixel | CWSaveUnder,
                             (XSetWindowAttributes[]){{.background_pixel = 0x00ff00, .save_under = True}});
    XChangeWindowAttributes(con, sub, CWBitGravity | CWEventMask | CWWinGravity,
                            ((XSetWindowAttributes[]){{
                                .bit_gravity = NorthWestGravity,
                                .win_gravity = NorthWestGravity,
                                .event_mask = KeyPressMask | ExposureMask | ButtonPressMask,
                            }}));
    return sub;
}
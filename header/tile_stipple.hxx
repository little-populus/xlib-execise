#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstring>
GC CreateTile(Display *con, Window window, Pixmap pixmap);
GC CreateStipple(Display *con, Window window, Pixmap pixmap);
Window CreateSubwindow(Display *con, Window window);
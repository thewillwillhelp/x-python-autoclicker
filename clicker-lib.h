#ifndef CLICKER_LIB_H
#define CLICKER_LIB_H

#include <X11/Xlib.h>
#include <X11/Xutil.h> // XGetPixel and XDestroyImage

// Simulate mouse click
void click(Display *display, int button);

// Get mouse coordinates
void coords(Display *display, int *x, int *y);

// Move mouse pointer (relative)
void move(Display *display, int x, int y);

// Move mouse pointer (absolute)
void move_to(Display *display, int x, int y);

// Get pixel color at coordinates x,y
void pixel_color(Display *display, int x, int y, XColor *color);

#endif

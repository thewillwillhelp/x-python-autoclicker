#include <stdio.h>
#include "clicker-lib.h"
#include "python-wrapper.hpp"

bool isDebugMode() {
    char * is_debug_mode = getenv("DEBUG");

    return is_debug_mode && is_debug_mode[0];
}

void python_routine(Display *display) {
    PythonWrapper::SetDisplay(display);
    PythonWrapper::setIsDebugMode(isDebugMode());

    PythonWrapper pw;

    pw.RunCode();
}

void print_info() {
    if (isDebugMode()) {
        printf("Debug mode\n");
    }
}

int main() {
    print_info();

    Display *display = NULL;
    display = XOpenDisplay(NULL);

    if (display == NULL)
    {
        fprintf (stderr, "Can't open display!\n");
        return -1;
    }

    python_routine(display);
}

# xlib-python-autoclicker
Simple tool to emulate pointer events in Linux X11 using python script.

To build: ```make default```\
Python should be installed. Check the version of library in makefile.

To use:
1. Create file 'script.py' in the same folder with the executable.
2. Put ```import x_clicker``` to use tool's functions and write python code
3. Execute `xclicker` binary file.

Example:

    import x_clicker
    import time

    direction = 1
    for i in range(10):
        if i >= 5:
            direction = -1

        x_clicker.move_pointer(10 * direction, 20 * direction)
        time.sleep(0.1)
        
    print(x_clicker.get_position())
    print(x_clicker.get_color())
    
Available functions:

`x_clicker.get_position()` - returns current pointer position as a Tuple (e.g. `(1033, 851)`)\
`x_clicker.get_color()` - returns color of point in current pointer position (e.g. `(16448, 16448, 16448)`)\
`x_clicker.click()` - emulates click in current pointer position\
`x_clicker.move_pointer(int x, int y)` - moves cursor from current pointer position to X and Y pixels

#ifndef CLICKER_PYTHON_WRAPPER_LIB_H
#define CLICKER_PYTHON_WRAPPER_LIB_H

#include <X11/Xlib.h>
#include <python3.6/Python.h>

class PythonWrapper {
    static Display *display;
    PyMethodDef XClickerMethods[6];
    static bool isDebugMode;

    static PyObject* move_pointer(PyObject *self, PyObject *args);
    // static PyObject* move_pointer_to(PyObject *self, PyObject *args);
    static PyObject* click(PyObject *self, PyObject *args);
    static PyObject* get_position(PyObject *self, PyObject *args);
    static PyObject* get_color(PyObject *self, PyObject *args);

    static PyObject* PyInit_x_clicker(void);
    static void AppendLibrary();
public:
    static PyModuleDef XClickerModule;
    PythonWrapper();
    ~PythonWrapper();

    void RunCode();
    static void SetDisplay(Display *display);
    static void setIsDebugMode(bool debugMode);
};

#endif

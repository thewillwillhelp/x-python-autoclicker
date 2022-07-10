#include "python-wrapper.hpp"
#include "clicker-lib.h"

PyModuleDef PythonWrapper::XClickerModule = {};
Display* PythonWrapper::display = NULL;
bool PythonWrapper::isDebugMode = false;

PythonWrapper::PythonWrapper() {
    XClickerMethods[0] = {
        "move_pointer",
        PythonWrapper::move_pointer,
        METH_VARARGS,
        "Moves pointer"
    };
    XClickerMethods[1] = {
        "click",
        PythonWrapper::click,
        METH_VARARGS,
        "Clicks at current position"
    };
    XClickerMethods[2] = {
        "get_position",
        PythonWrapper::get_position,
        METH_VARARGS,
        "Returns current position"
    };
    XClickerMethods[3] = {
        "get_color",
        PythonWrapper::get_color,
        METH_VARARGS,
        "Returns color at the position"
    };
    XClickerMethods[4] = { NULL, NULL, 0, NULL };

    PythonWrapper::XClickerModule = {
        PyModuleDef_HEAD_INIT, "x_clicker", NULL, -1, XClickerMethods,
        NULL, NULL, NULL, NULL
    };

    PythonWrapper::AppendLibrary();

    Py_Initialize();
}

PythonWrapper::~PythonWrapper() {
    Py_Finalize();
}

void PythonWrapper::setIsDebugMode(bool newValue) {
    PythonWrapper::isDebugMode = newValue;
}

void PythonWrapper::RunCode() {
    PyRun_SimpleString("print(\"XClicker v0.0.1\")");

    FILE *f = NULL;
    f = fopen("./script.py", "r");

    PyRun_SimpleFile(f, "script.py");

    fclose(f);
}

PyObject* PythonWrapper::PyInit_x_clicker(void)
{
    return PyModule_Create(&XClickerModule);
}

void PythonWrapper::AppendLibrary() {
    PyImport_AppendInittab("x_clicker", &PythonWrapper::PyInit_x_clicker);
}

void PythonWrapper::SetDisplay(Display *display) {
    PythonWrapper::display = display;
}

PyObject* PythonWrapper::move_pointer(PyObject *self, PyObject *args) {
    int default_x = 0;
    int default_y = 0;

    PyObject *x = NULL;
    PyObject *y = NULL;

    if(PyArg_UnpackTuple(args, "", 0, 2, &x, &y))
    {
        int shift_x = x ? PyLong_AsLong(x) : default_x;
        int shift_y = y ? PyLong_AsLong(y) : default_y;

        if (PythonWrapper::isDebugMode) {
            printf(
                "Move pointer by x=%d, y=%d\n",
                shift_x,
                shift_y
            );
        }

        move(PythonWrapper::display, shift_x, shift_y);
    }

    return PyLong_FromLong(0);
}

PyObject* PythonWrapper::click(PyObject *self, PyObject *args) {
    if (PythonWrapper::isDebugMode) {
        printf("Click\n");
    }

    ::click(PythonWrapper::display, Button1);

    return PyLong_FromLong(0);
}

PyObject* PythonWrapper::get_position(PyObject *self, PyObject *args) {
    int x = 0, y = 0;

    if (PythonWrapper::isDebugMode) {
        printf("Get position: ");
    }

    coords(PythonWrapper::display, &x, &y);

    if (PythonWrapper::isDebugMode) {
        printf("C++: x=%d y=%d\n", x, y);
    }

    PyObject* out = Py_BuildValue("(ii)", x, y);
    Py_INCREF(out);

    return out;
}

PyObject* PythonWrapper::get_color(PyObject *self, PyObject *args) {
    XColor *color;

    int default_x = 0;
    int default_y = 0;
    int target_x = 0;
    int target_y = 0;

    color = new XColor;

    PyObject *x = NULL;
    PyObject *y = NULL;

    if(PyArg_UnpackTuple(args, "", 0, 2, &x, &y))
    {
        if (!x || !y) {
            coords(PythonWrapper::display, &default_x, &default_y);
        }

        target_x = x ? PyLong_AsLong(x) : default_x;
        target_y = y ? PyLong_AsLong(y) : default_y;

        if (PythonWrapper::isDebugMode) {
            printf(
                "Get color at x=%d, y=%d\n",
                target_x,
                target_y
            );
        }

        pixel_color(PythonWrapper::display, target_x, target_y, color);

        if (PythonWrapper::isDebugMode) {
            printf("R(%x) G(%x) B(%x)\n", color->red, color->green, color->blue);
        }
    }

    PyObject* out = Py_BuildValue("(iii)", color->red, color->green, color->blue);
    Py_INCREF(out);

    delete color;

    return out;
}

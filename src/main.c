#include <Python.h>
#include <structmember.h>
#include <gtk/gtk.h>
#include <geanyplugin.h>
#include <pygtk/pygtk.h>
#include "plugin.h"


extern GeanyPlugin		*geany_plugin;
extern GeanyData		*geany_data;
extern GeanyFunctions	*geany_functions;


static PyObject *
Main_is_realized(PyObject *module, PyObject *args)
{
    if (main_is_realized())
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}


static PyObject *
Main_locale_init(PyObject *module, PyObject *args)
{
    gchar *locale_dir = NULL, *package = NULL;

    if (PyArg_ParseTuple(args, "ss", &locale_dir, &package))
        main_locale_init(locale_dir, package);

    Py_RETURN_NONE;
}


static PyObject *
Main_reload_configuration(PyObject *module, PyObject *args)
{
    main_reload_configuration();
    Py_RETURN_NONE;
}


static
PyMethodDef MainModule_methods[] = {
    { "is_realized", (PyCFunction) Main_is_realized, METH_VARARGS },
    { "locale_init", (PyCFunction) Main_locale_init, METH_VARARGS },
    { "reload_configuration", (PyCFunction) Main_reload_configuration, METH_VARARGS },
    { NULL }
};


PyMODINIT_FUNC
init_geany_main(void)
{
    PyObject *m;

    m = Py_InitModule("_geany_main", MainModule_methods);
}

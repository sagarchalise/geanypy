#include "geanypy.h"


static PyObject *
Glog_glog(PyObject *module, PyObject *args, PyObject *kwargs)
{
	static gchar *kwlist[] = { "log_domain", "log_level", "message", NULL };
	gchar *log_domain, *message;
	GLogLevelFlags log_level;

	if (PyArg_ParseTupleAndKeywords(args, kwargs, "sis", kwlist, &log_domain, &log_level, &message))
	{
		g_log(log_domain, log_level, "%s", message);
	}
	Py_RETURN_NONE;
}


static
PyMethodDef GlogModule_methods[] = {
	{ "glog", (PyCFunction) Glog_glog, METH_KEYWORDS, "Wrapper around g_log()." },
	{ NULL }
};


PyMODINIT_FUNC PyInit_glog(void)
{
	PyObject *m;
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "glog",     /* m_name */
        "GLib Log utility function.",  /* m_doc */
        -1,                  /* m_size */
        GlogModule_methods,    /* m_methods */
        NULL,                /* m_reload */
        NULL,                /* m_traverse */
        NULL,                /* m_clear */
        NULL,                /* m_free */
    };

	m = PyModule_Create(&moduledef);

	/* TODO: These constants are for the geany.logger.GLIB_LOG_LEVEL_MAP mapping.
	 *       It would be better to build this mapping on the C layer but how to
	 *       access the Python logging.* level constants here? */
	PyModule_AddIntConstant(m, "LOG_LEVEL_DEBUG", G_LOG_LEVEL_DEBUG);
	PyModule_AddIntConstant(m, "LOG_LEVEL_INFO", G_LOG_LEVEL_INFO);
	PyModule_AddIntConstant(m, "LOG_LEVEL_MESSAGE", G_LOG_LEVEL_MESSAGE);
	PyModule_AddIntConstant(m, "LOG_LEVEL_WARNING", G_LOG_LEVEL_WARNING);
	PyModule_AddIntConstant(m, "LOG_LEVEL_ERROR", G_LOG_LEVEL_ERROR);
	PyModule_AddIntConstant(m, "LOG_LEVEL_CRITICAL", G_LOG_LEVEL_CRITICAL);
    return m;
}

#include "geanypy.h"


typedef struct
{
	PyObject_HEAD
	GeanySearchPrefs *search_prefs;
} SearchPrefs;


static void
SearchPrefs_dealloc(SearchPrefs *self)
{
	g_return_if_fail(self != NULL);
	Py_TYPE(self)->tp_free((PyObject *) self);
}


static int
SearchPrefs_init(SearchPrefs *self)
{
	g_return_val_if_fail(self != NULL, -1);
	self->search_prefs = geany_data->search_prefs;
	return 0;
}


static PyObject *
SearchPrefs_get_property(SearchPrefs *self, const gchar *prop_name)
{
	g_return_val_if_fail(self != NULL, NULL);
	g_return_val_if_fail(prop_name != NULL, NULL);

	if (!self->search_prefs)
	{
		PyErr_SetString(PyExc_RuntimeError,
			"SearchPrefs instance not initialized properly");
		return NULL;
	}

	if (g_str_equal(prop_name, "use_current_word"))
	{
		if (self->search_prefs->use_current_word)
			Py_RETURN_TRUE;
		else
			Py_RETURN_FALSE;
	}

	Py_RETURN_NONE;
}
GEANYPY_PROPS_READONLY(SearchPrefs);


static PyGetSetDef SearchPrefs_getseters[] = {
	GEANYPY_GETSETDEF(SearchPrefs, "use_current_word",
		"Use current word for default search text."),
	{ NULL }
};


static PyTypeObject SearchPrefsType = {
	PyVarObject_HEAD_INIT(NULL, 0)										/* ob_size */
	"geany.search.SearchPrefs",							/* tp_name */
	sizeof(SearchPrefs),								/* tp_basicsize */
	0,											/* tp_itemsize */
	(destructor) SearchPrefs_dealloc,					/* tp_dealloc */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* tp_print - tp_as_buffer */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,	/* tp_flags */
	"Wrapper around a GeanySearchPrefs structure.",		/* tp_doc  */
	0, 0, 0, 0, 0, 0, 0, 0,						/* tp_traverse - tp_members */
	SearchPrefs_getseters,								/* tp_getset */
	0, 0, 0, 0, 0,								/* tp_base - tp_dictoffset */
	(initproc) SearchPrefs_init,						/* tp_init */
	0, 0,										/* tp_alloc - tp_new */
};


static PyObject *
Search_show_find_in_files_dialog(PyObject *self, PyObject *args, PyObject *kwargs)
{
	gchar *dir = NULL;
	static gchar *kwlist[] = { "init_dir", NULL };

	PyArg_ParseTupleAndKeywords(args, kwargs, "s", kwlist, &dir);
	search_show_find_in_files_dialog(dir);

	Py_RETURN_NONE;
}


static PyMethodDef SearchPrefsModule_methods[] = {
	{ "show_find_in_files_dialog",
		(PyCFunction) Search_show_find_in_files_dialog,
		METH_KEYWORDS,
		"Shows the Find in Files dialog, taking an optional directory "
		"to search in for the dialog or if not specified then uses "
		"the current document's directory." },
	{ NULL }
};


PyMODINIT_FUNC PyInit_search(void)
{
	PyObject *m;
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "search",     /* m_name */
        "Search preferences and information.",  /* m_doc */
        -1,                  /* m_size */
        SearchPrefsModule_methods,    /* m_methods */
        NULL,                /* m_reload */
        NULL,                /* m_traverse */
        NULL,                /* m_clear */
        NULL,                /* m_free */
    };

	SearchPrefsType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&SearchPrefsType) < 0)
		return NULL;

	m = PyModule_Create(&moduledef);

	Py_INCREF(&SearchPrefsType);
	PyModule_AddObject(m, "SearchPrefs", (PyObject *) &SearchPrefsType);
    return m;
}

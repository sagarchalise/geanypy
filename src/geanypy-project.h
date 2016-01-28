#ifndef GEANYPY_PROJECT_H__
#define GEANYPY_PROJECT_H__

PyTypeObject ProjectType;

typedef struct
{
	PyObject_HEAD
	GeanyProject *project;
} Project;

PyMODINIT_FUNC PyInit_project(void);

#endif /* GEANYPY_PROJECT_H__ */

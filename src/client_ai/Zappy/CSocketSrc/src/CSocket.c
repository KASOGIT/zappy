/*
** test.c for Zappy in /home/oliva/_workspace_zappy/ai_client/CSocket
** 
** Made by Clement Oliva
** Login   <oliva@epitech.net>
** 
** Started on  Tue Jun 14 17:16:54 2016 Clement Oliva
** Last update Sun Jun 26 21:42:28 2016 
*/

#include <python3.4/Python.h>
#include <python3.4/structmember.h>

#include "CSocket.h"

static PyObject* py_testFunction(__attribute__((unused))PyObject* self,
				 __attribute__((unused))PyObject* args)
{
  return (Py_BuildValue("s", "Hello from C!"));
}

/*
 * Binding C functions to Python functions
 */

static PyMethodDef	cSocket_functions[] = {
  {"testFunction", py_testFunction, METH_VARARGS, ""},
  {NULL, NULL, 0, NULL}
};

/*
 * Defining member functions of CSocket object
 */

static PyMethodDef	cSocket_methods[] = {
  {"test", (PyCFunction)pyCSocket_test, METH_NOARGS, "test function"},
  {"connect", (PyCFunction)pyCSocket_connect, METH_NOARGS, "connect"},
  {"bind", (PyCFunction)pyCSocket_bind, METH_NOARGS, "bind"},
  {"listen", (PyCFunction)pyCSocket_listen, METH_NOARGS, "listen"},
  {"send", (PyCFunction)pyCSocket_send, METH_VARARGS, "send"},
  {"receive", (PyCFunction)pyCSocket_receive, METH_VARARGS, "receive (1024)"},
  {NULL}
};

/*
 * Defining member attributes of CSocket object
 */

static PyMemberDef	cSocket_attributes[] = {
  {NULL}
};

/*
 * Defining CSocket class
 */

static PyTypeObject	cSocket_type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "CSocket.CSocket",				/* tp_name */
  sizeof(t_PyCSocket),				/* tp_basicsize */
  0,						/* tp_itemsize */
  (destructor)pyCSocket_dealloc,		/* tp_dealloc */
  0,						/* tp_print */
  0,						/* tp_getattr */
  0,						/* tp_setattr */
  0,						/* tp_reserved */
  0,						/* tp_repr */
  0,						/* tp_as_number */
  0,						/* tp_as_sequence */
  0,						/* tp_as_mapping */
  0,						/* tp_hash */
  0,						/* tp_call */
  0,						/* tp_str */
  0,						/* tp_getattro */
  0,						/* tp_setattro */
  0,						/* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,	/* tp_flags */
  "CSocket object",				/* tp_doc */
  0,						/* tp_traverse */
  0,						/* tp_clear */
  0,						/* tp_richcompare */
  0,						/* tp_weaklistoffset */
  0,						/* tp_iter */
  0,						/* tp_iternext */
  cSocket_methods,				/* tp_methods */
  cSocket_attributes,				/* tp_members */
  0,						/* tp_getset */
  0,						/* tp_base */
  0,						/* tp_dict */
  0,						/* tp_descr_get */
  0,						/* tp_descr_set */
  0,						/* tp_dictoffset */
  (initproc)pyCSocket_init,			/* tp_init */
  0,						/* tp_alloc */
  pyCSocket_new,	       		       	/* tp_new */
  0,						/* tp_free */
  0,						/* tp_is_gc */
  0,						/* tp_bases */
  0,						/* tp_mro */
  0,						/* tp_cache */
  0,						/* tp_subclasses */
  0,						/* tp_weaklist */
  0,						/* tp_del */
  0,						/* tp_version_tag */
  0						/* tp_finalize */
};

/*
 * CSocket module definition
 */

static struct PyModuleDef	pyCSocket_module = {
  PyModuleDef_HEAD_INIT,
  "CSocket", "C Socket for Zappy project",
  -1,  cSocket_functions,
  NULL, NULL, NULL, NULL
};

/*
 * Python module initialization
 */

PyMODINIT_FUNC	PyInit_CSocket(void)
{
  PyObject	*module;

  cSocket_type.tp_new = PyType_GenericNew;
  if (PyType_Ready(&cSocket_type) < 0)
    return (NULL);
  if ((module = PyModule_Create(&pyCSocket_module)) == NULL)
    return (NULL);
  Py_INCREF(&cSocket_type);
  PyModule_AddObject(module, "CSocket", (PyObject *)&cSocket_type);
  return (module);
}

/*
** CSocketFunctions.c for Zappy in /home/oliva/_workspace_zappy/ai_client/Zappy/CSocketSrc/src
** 
** Made by Clement Oliva
** Login   <oliva@epitech.net>
** 
** Started on  Tue Jun 21 17:32:52 2016 Clement Oliva
** Last update Sun Jun 26 21:41:26 2016 
*/

#include "CSocket.h"

PyObject	*pyCSocket_new(PyTypeObject *type,
			       __attribute__((unused))PyObject *args,
			       __attribute__((unused))PyObject *kwds)
{
  return ((PyObject *)type->tp_alloc(type, 0));
}

void		pyCSocket_dealloc(t_PyCSocket *self)
{
  Py_TYPE(self)->tp_free((PyObject *)self);
}

int		pyCSocket_init(t_PyCSocket *self,
			       __attribute__((unused))PyObject *args,
			       __attribute__((unused))PyObject *kwds)
{
  int		port;
  char		*addr;

  if (!PyArg_ParseTuple(args, "is", &port, &addr))
    return (-1);
  socket_init(&self->socket, port, addr);
  return (0);
}

PyObject	*pyCSocket_test(__attribute__((unused))t_PyCSocket *self)
{
  return (Py_BuildValue("s", "test"));
}

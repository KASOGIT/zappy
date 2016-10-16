/*
** CSocket.h for Zappy in /home/oliva/_workspace_zappy/ai_client/Zappy/CSocketSrc/src
** 
** Made by Clement Oliva
** Login   <oliva@epitech.net>
** 
** Started on  Sat Jun 18 14:16:14 2016 Clement Oliva
** Last update Sun Jun 26 21:43:04 2016 
*/

#ifndef ZAPPY_CSOCKET_H
#define ZAPPY_CSOCKET_H

/*
 * Python 3.4 C API
 */

#include <python3.4/Python.h>

/*
 * Sockets in C that will be wrapped by the python CSocket class
 */

#include "socket/socket.h"

/*
 * CSocket class definition
 */

typedef struct		s_PyCSocket
{
  PyObject_HEAD;
  t_socket		socket;
}			t_PyCSocket;

/*
 * CSocket member functions
 */

PyObject	       	*pyCSocket_new(PyTypeObject *type,
				       PyObject *args,
				       PyObject *kwds);
void			pyCSocket_dealloc(t_PyCSocket *self);
int			pyCSocket_init(t_PyCSocket *self,
				       PyObject *args,
				       PyObject *kwds);
PyObject       		*pyCSocket_test(t_PyCSocket *self);
PyObject       		*pyCSocket_connect(t_PyCSocket *self);
PyObject       		*pyCSocket_bind(t_PyCSocket *self);
PyObject       		*pyCSocket_listen(t_PyCSocket *self);
PyObject       		*pyCSocket_receive(t_PyCSocket *self, PyObject *args);
PyObject       		*pyCSocket_send(t_PyCSocket *self, PyObject *args);

#endif /* !ZAPPY_CSOCKET_H */

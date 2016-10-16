/*
** CSocketWrapper.c for Zappy in /home/oliva/_workspace_zappy/ai_client/Zappy/CSocketSrc/src
** 
** Made by Clement Oliva
** Login   <oliva@epitech.net>
** 
** Started on  Wed Jun 22 16:02:39 2016 Clement Oliva
** Last update Thu Jun 23 21:23:25 2016 Clement Oliva
*/

#include <sys/select.h>
#include <sys/time.h>

#include "CSocket.h"

PyObject	*pyCSocket_connect(t_PyCSocket *self)
{
  return (Py_BuildValue("i", self->socket.connect(&self->socket)));
}

PyObject	*pyCSocket_bind(t_PyCSocket *self)
{
  return (Py_BuildValue("i", self->socket.bind(&self->socket)));
}

PyObject	*pyCSocket_listen(t_PyCSocket *self)
{
  return (Py_BuildValue("i", self->socket.listen(&self->socket)));
}

PyObject	*pyCSocket_send(t_PyCSocket *self, PyObject *args)
{
  char		*msg;

  if (!PyArg_ParseTuple(args, "s", &msg))
    return (NULL);
  return (Py_BuildValue("i", write(self->socket._fd, msg, strlen(msg))));
}

PyObject		*pyCSocket_receive(t_PyCSocket *self, PyObject *args)
{
  char			msg[1024 + 1];
  fd_set		set;
  int			ret;
  int			timeout;
  struct timeval	tval;

  FD_ZERO(&set);
  FD_SET(self->socket._fd, &set);
  bzero(&tval, sizeof(struct timeval));
  bzero(msg, 1024 + 1);
  timeout = 0;
  if (!PyArg_ParseTuple(args, "|i", &timeout))
    return (NULL);
  tval.tv_usec = 1000 * timeout;
  ret = select(FD_SETSIZE, &set, NULL, NULL, &tval);
  if (ret == -1)
    return (NULL);
  else if (ret && read(self->socket._fd, msg, 1024) > 0)
    return (Py_BuildValue("s", msg));
  else
    return (Py_BuildValue("s", ""));
}

/*
** prend_pose.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 20:31:23 2016 
** Last update Fri Jun 24 20:32:54 2016 
*/

#include "commands.h"

t_object_converter   g_object_converter[9] =
  {
    {"linemate",    LINEMATE},
    {"deraumere",   DERAUMERE},
    {"sibur",       SIBUR},
    {"mendiane",    MENDIANE},
    {"phiras",      PHIRAS},
    {"linemate",    LINEMATE},
    {"thystame",    THYSTAME},
    {"nourriture",  FOOD},
    {NULL,          NONE}
  };

inline t_object	get_object_type(char *str)
{
  int		i;

  for (i = 0; g_object_converter[i].raw_object; i++)
    {
      if (strcmp(str, g_object_converter[i].raw_object) == 0)
	return (g_object_converter[i].object);
    }
  return (NONE);
}

inline const char	*get_raw_object_type(t_object obj)
{
  int			i;

  for (i = 0; g_object_converter[i].raw_object; i++)
    {
      if (g_object_converter[i].object == obj)
	return (g_object_converter[i].raw_object);
    }
  return (NULL);
}

int		is_object_type(void *data, void *args)
{
  t_object	objectFromData;
  t_object	objectFromArgs;

  objectFromData = *((t_object *)data);
  objectFromArgs = *((t_object *)args);
  return (objectFromArgs == objectFromData);
}

inline void	send_prend_pose_to_graphics(t_handle_client *this,
					    t_server *server,
					    t_object object,
					    enum WHICH_PREND_POSE which)
{
  char		msg[1024];

  memset(msg, '\0', 1024);
  if (which == PREND)
    sprintf(msg, "pgt #%d %d\n", this->_id, object);
  else
    sprintf(msg, "pdr #%d %d\n", this->_id, object);
  server->send_msg_to_client_graph(server, msg);
  this->send_msg(this, "ok\n");
  cmd_pin(this, GRAPHICS);
  cmd_bct(this, GRAPHICS);
}

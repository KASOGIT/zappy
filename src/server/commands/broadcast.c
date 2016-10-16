/*
** broadcast.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 25 01:28:05 2016 
** Last update Sat Jun 25 01:34:30 2016 
*/

#include "commands.h"

static const double	g_trigo_circle[9][2] =
  {
    {0.0,   -1.0},
    {-1.0,  -1.0},
    {-1.0,  0.0},
    {-1.0,  1.0},
    {0.0,   0.0},
    {0.0,   1.0},
    {1.0,   1.0},
    {1.0,   0.0},
    {1.0,   -1.0}
  };

static double	broadcast_get_angle(t_handle_client *dest,
				    t_handle_client *src,
				    int min)
{
  int		i;
  double	rad;
  t_vector2d	tab_vector[9];

  for (i = 0; i < 9; i++)
    {
      tab_vector[i].x = (g_trigo_circle[i][0] * dest->_parent->_world->_s_x)
	+ dest->_player->_pos_x;
      tab_vector[i].y = (g_trigo_circle[i][1] * dest->_parent->_world->_s_y)
	+ dest->_player->_pos_y;
      tab_vector[i].distance = calc_distance(tab_vector[i].x, tab_vector[i].y,
					     src->_player->_pos_x,
					     src->_player->_pos_y);
      if (tab_vector[min].distance > tab_vector[i].distance)
	min = i;
    }
  rad = atan2(src->_player->_pos_y - tab_vector[min].y,
	      src->_player->_pos_x - tab_vector[min].x);
  if (rad >= -0.000001 && rad <= 0.000001 &&
      src->_player->_pos_x < tab_vector[min].x)
    rad += M_PI;
  if (rad < 0)
    rad += 2 * M_PI;
  return ((rad * 180) / M_PI);
}

static int	broadcast_get_direction(double angle)
{
  if (angle >= 247.5 && angle <= 292.5)
    return (1);
  else if (angle > 202.5 && angle < 247.5)
    return (2);
  else if (angle >= 157.5 && angle <= 202.5)
    return (3);
  else if (angle > 112.5 && angle < 157.5)
    return (4);
  else if (angle >= 67.5 && angle <= 112.5)
    return (5);
  else if (angle < 67.5 && angle > 22.5 )
    return (6);
  if (angle <= 22.5 || angle >= 337.5)
    return (7);
  else if (angle > 292.5 && angle < 337.5)
    return (8);
  return (-1);
}

static int	broadcast_take_orientation(t_way way)
{
  if (way == NORTH)
    return (1);
  else if (way == EAST)
    return (7);
  else if (way == WEST)
    return (3);
  else if (way == SOUTH)
    return (5);
  return (way);
}

static void	broadcast_send_message(int dir,
				       const char *txt,
				       t_handle_client *dest,
				       t_handle_client *src)
{
  char		*msg;

  if ((msg = malloc(strlen(txt) + strlen("message  ") + 1)) == NULL)
    {
      perror("malloc");
      return ;
    }
  if (src->_player->_pos_x == dest->_player->_pos_x &&
      src->_player->_pos_y == dest->_player->_pos_y)
    dir = 0;
  sprintf(msg, "message %d, %s\n", dir, txt);
  dest->send_msg(dest, msg);
  sprintf(msg, "pbc #%d %s\n", src->_id, txt);
  src->_parent->send_msg_to_client_graph(src->_parent, msg);
  free(msg);
}

void			broadcast(void *data, void *args)
{
  t_handle_client	*dest;
  t_handle_client	*src;
  double		angle;
  int			direction;
  char			*txt;

  dest = (t_handle_client *)(data);
  src = (t_handle_client *)(args);
  if (dest == src || dest->_type == CLIENT_GRAPH)
    return;
  angle = broadcast_get_angle(dest, src, 0);
  direction = (MAX_ORIENTATION
	       - broadcast_take_orientation(dest->_player->_way)
	       + broadcast_get_direction(angle)) % MAX_ORIENTATION + 1;
  txt = wordtab_to_str(src->_args);
  broadcast_send_message(direction, txt, dest, src);
  free(txt);
}

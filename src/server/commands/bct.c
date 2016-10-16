/*
** bct.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 25 01:27:28 2016 
** Last update Sun Jun 26 23:20:09 2016 
*/

#include "commands.h"

int	check_args_bct(t_handle_client *this,
		       int *pos_x,
		       int *pos_y)
{
  return (!this->_args || !this->_args[0] || !this->_args[1]
	  || ((*pos_x = atoi(this->_args[0])) < 0
	      || *pos_x > this->_parent->_world->_s_x)
	  || ((*pos_y = atoi(this->_args[1])) < 0
	      || *pos_y > this->_parent->_world->_s_y));
}

void		prepare_bct_message(t_handle_client *this,
				    int pos_x,
				    int pos_y,
				    char *msg)
{
  t_list	*list;
  int		i;

  sprintf(msg, "bct %d %d {", pos_x, pos_y);
  list = this->_parent->_world->_map[pos_y][pos_x]->_objects;
  reset_inventaire();
  list->for_each(list, &inventaire);
  for (i = 0; g_inventaire[i].obj != NONE; i++)
    sprintf(msg + strlen(msg), "%s %d, ",
	    get_raw_object_type(g_inventaire[i].obj),
	    g_inventaire[i].nbr);
  sprintf(msg + strlen(msg) - 2, "}\n");
}

void		cmd_bct_with_pos(t_handle_client *this,
				 int pos_x, int pos_y)
{
  char		msg[1024];

  prepare_bct_message(this, pos_x, pos_y, msg);
  this->send_msg(this, msg);
}

void		cmd_bct_with_pos_graphics(t_handle_client *this,
					  int pos_x,
					  int pos_y)
{
  char		msg[1024];

  prepare_bct_message(this, pos_x, pos_y, msg);
  this->_parent->send_msg_to_client_graph(this->_parent, msg);
}

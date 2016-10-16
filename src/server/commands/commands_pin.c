/*
** commands_pin.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun Jun 26 21:22:43 2016 
** Last update Sun Jun 26 21:23:46 2016 
*/

#include "commands.h"

inline static int	calc_food(t_handle_client *this)
{
  return (int)((((this->_player->_unit_time / 1000.0f)
		 / (1.0f / (double)g_time_delay)) / 126.0f));
}

int			get_user_by_id(void *data, void *arg)
{
  char			**args;
  t_handle_client	*client;

  args = (char **)arg;
  client = (t_handle_client *)data;
  if (ASSERT_ARGS_CMD(args) == -1 || strlen(args[0]) < 2)
    return (0);
  return (client->_id == atoi(&args[0][1]));
}

void	pin_send_msg(t_handle_client *player,
		     enum WHOSE_SEND_MSG whose,
		     char *msg,
		     t_handle_client *this)
{
  int	i;

  i = 0;
  if (!player->_player || !player->_player->_inventory)
    return ;
  player->_player->_inventory->for_each(player->_player->_inventory,
					&inventaire);
  sprintf(msg, "pin #%d %d %d ", player->_id, player->_player->_pos_x,
	  player->_player->_pos_y);
  sprintf(msg + strlen(msg), "{");
  for (i = 0; g_inventaire[i].obj != NONE; i++)
    {
      sprintf(msg + strlen(msg), "%s ",
	      get_raw_object_type(g_inventaire[i].obj));
      if (g_inventaire[i].obj == FOOD)
	sprintf(msg + strlen(msg), "%d,", calc_food(player));
      else
	sprintf(msg + strlen(msg), "%d,",
		g_inventaire[i].nbr);
    }
  sprintf(msg + strlen(msg) - 1, "}\n");
  if (whose == CLIENT)
    this->send_msg(this, msg);
  else
    player->_parent->send_msg_to_client_graph(player->_parent, msg);
}

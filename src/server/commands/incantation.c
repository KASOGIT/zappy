/*
** incantation.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 20:27:42 2016 
** Last update Sun Jun 26 23:25:43 2016 
*/

#include "commands.h"

static const t_incantation_rules	g_incantation_rules[] =
  {
    {2, 1, 1, 0, 0, 0, 0, 0},
    {3, 2, 1, 1, 1, 0, 0, 0},
    {4, 2, 2, 0, 1, 0, 2, 0},
    {5, 4, 1, 1, 2, 0, 1, 0},
    {6, 4, 1, 2, 1, 3, 0, 0},
    {7, 6, 1, 2, 3, 0, 1, 0},
    {8, 6, 2, 2, 2, 2, 2, 1}
  };

int			get_nb_players_incantation(void *data, va_list ap)
{
  t_handle_client	*tmp;
  t_handle_client	*client;
  t_list		*list;
  char			*msg;

  tmp = (t_handle_client *)(data);
  client = va_arg(ap, t_handle_client *);
  if (tmp == client)
    return (0);
  if (tmp->_type == CLIENT_AI &&
      tmp->_player->_lvl == client->_player->_lvl &&
      tmp->_player->_pos_x == client->_player->_pos_x &&
      tmp->_player->_pos_y == client->_player->_pos_y)
    {
      msg = va_arg(ap, char *);
      list = va_arg(ap, t_list *);
      sprintf(msg + strlen(msg), " #%d", tmp->_id);
      list->push_back(list, tmp);
      return (1);
    }
  return (0);
}

int	check_for_incantation(t_handle_client *this,
			      int nb_players)
{
  int	i;

  if (this->_player->_lvl > 8)
    return (0);
  for (i = 0; i < 9; i++)
    if (this->_player->_lvl + 1 == g_incantation_rules[i].LEVEL)
      return (nb_players >= g_incantation_rules[i].NB_REQUIRED_PLAYERS
	      && g_inventaire[0].nbr >= g_incantation_rules[i].NB_LINEMATE
	      && g_inventaire[1].nbr >= g_incantation_rules[i].NB_DERAUMERE
	      && g_inventaire[2].nbr >= g_incantation_rules[i].NB_SIBUR
	      && g_inventaire[3].nbr >= g_incantation_rules[i].NB_MENDIANE
	      && g_inventaire[4].nbr >= g_incantation_rules[i].NB_PHIRAS
	      && g_inventaire[5].nbr >= g_incantation_rules[i].NB_THYSTAME);
  return (0);
}

static void	incantation_send_msg(t_handle_client *tmp, char *msg)
{
  tmp->send_msg(tmp, "elevation en cours\n");
  ++tmp->_player->_lvl;
  ++tmp->_player->_range;
  sprintf(msg, "pie %d %d 1\n", tmp->_player->_pos_x, tmp->_player->_pos_y);
  tmp->_parent->send_msg_to_client_graph(tmp->_parent, msg);
  sprintf(msg, "niveau actuel : %d\n", tmp->_player->_lvl);
  tmp->send_msg(tmp, msg);
  sprintf(msg, "plv #%d %d\n", tmp->_id, tmp->_player->_lvl);
  tmp->_parent->send_msg_to_client_graph(tmp->_parent, msg);
}

void			incantation_end(t_handle_client *current,
					t_list *list_players,
					char *msg)
{
  t_elem		*front;
  t_handle_client	*tmp;

  incantation_send_msg(current, msg);
  if (list_players->size(list_players) > 0)
    {
      for (front = list_players->begin(list_players);
	   front != list_players->end(list_players);
	   front = front->next(front))
	{
	  tmp = (t_handle_client *)(front->data(front));
	  incantation_send_msg(tmp, msg);
	}
      tmp = (t_handle_client *)(front->data(front));
      incantation_send_msg(tmp, msg);
    }
    cmd_bct_with_pos_graphics(current,
			      current->_player->_pos_x,
			      current->_player->_pos_y);
}

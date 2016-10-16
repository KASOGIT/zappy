/*
** commands_incant.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 17:39:42 2016 
** Last update Sun Jun 26 10:56:31 2016 
*/

#include "commands.h"

void	begin_incantation(int *nb_players,
			  t_handle_client *this,
			  char *msg,
			  t_list *list_players)
{
  sprintf(msg, "pic %d %d %d #%d ", this->_player->_pos_x,
	  this->_player->_pos_y, this->_player->_lvl, this->_id);
  *nb_players = this->_parent
    ->_users->count_match_pred_args(this->_parent->_users,
				    &get_nb_players_incantation,
				    this, msg, list_players) + 1;
  sprintf(msg + strlen(msg), "\n");
  this->_parent->send_msg_to_client_graph(this->_parent, msg);
}

void		PROTO_CMD(cmd_incantation)
{
  t_list	*list_objects;
  t_list	*list_players;
  int		nb_players;
  char		msg[1024];

  reset_inventaire();
  (void) arg;
  list_objects = server->_world->_map[this->_player->_pos_y]
    [this->_player->_pos_x]->_objects;
  list_objects->for_each(list_objects, &inventaire);
  list_players = list_create();
  begin_incantation(&nb_players, this, msg, list_players);
  if (check_for_incantation(this, nb_players))
    incantation_end(this, list_players, msg);
  else
    {
      sprintf(msg, "pie %d %d 0\n",
	      this->_player->_pos_x, this->_player->_pos_y);
      server->send_msg_to_client_graph(server, msg);
      this->send_msg(this, "ko\n");
    }
  list_destroy(list_players);
}

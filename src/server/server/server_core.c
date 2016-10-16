/*
** server.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 13:03:19 2016 
** Last update Sun Jun 26 19:05:14 2016 
*/

#include "server.h"

void	server_set_methods(t_server *this)
{
  this->server_listen = &server_listen;
  this->server_handle_client = &server_handle_client;
  this->server_accept = &server_accept;
  this->auth_client = &server_auth_client;
  this->get_team_from_name = &server_get_team_from_name;
  this->create_actions = &server_create_actions;
  this->send_msg_to_client_graph = &server_send_msg_to_client_graph;
  this->is_team_win = &server_is_team_win;
  this->get_lvl_users_by_id = &server_get_lvl_users_by_id;
  this->expulse_players = &server_expulse_players;
  this->connect_eggs = &server_connect_eggs;
  this->is_player_at = &server_is_player_at;
  this->reset_time_players = &server_reset_time_players;
}

void    server_error(t_server *this, const char *err_msg)
{
  fprintf(stderr, "[%d] Server error on func: %s\n",
	  (int)getpid(),
	  err_msg);
  server_destroy(this);
  exit(EXIT_FAILURE);
}

void    server_destroy(t_server *this)
{
  if (this->_sock != NULL)
    {
      socket_destroy(this->_sock);
      free(this->_sock);
    }
  list_destroy(this->_users);
  list_destroy(this->_client_graph);
  world_destroy(this->_world);
}

void	server_init(t_server *this, t_arg *arg)
{
  int	i;

  server_set_methods(this);
  this->_rand_gen = handle_random_create();
  if ((this->_sock = malloc(sizeof(t_socket))) == NULL)
    server_error(this, "malloc");
  socket_init(this->_sock, arg->port, NULL);
  this->_users = list_create();
  this->_client_graph = list_create();
  this->_world = world_create(arg);
  this->_id_egg = 0;
  this->_time = handle_time_create();
  this->_time->start_chrono(this->_time);
  i = 0;
  while (arg->name_team[i] != NULL)
    {
      this->_world->add_team(this->_world,
			     arg->name_team[i],
			     arg->max_client);
      i++;
    }
}

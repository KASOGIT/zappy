/*
** server_exec.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myirc
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 29 00:29:49 2016 
** Last update Fri Jun 17 21:24:41 2016 
*/

#include "server.h"

void	server_listen(t_server *this)
{
  this->_sock->socket_listen(this->_sock);
}

void	server_accept(t_server *this,
		      t_handle_client *client)
{
  this->_sock->socket_accept(this->_sock, client);
}

void	server_auth_client(t_server *this)
{
  this->_users->for_each_arg(this->_users, &auth_client, this);
}

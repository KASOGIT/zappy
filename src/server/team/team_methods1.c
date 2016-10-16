/*
** team_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/team
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun  4 02:40:16 2016 
** Last update Thu Jun  9 21:50:19 2016 
*/

#include "team.h"

void	team_add_client(t_team *this, t_handle_client *client)
{
  this->_client->push_back(this->_client, client);
}

/*
** avance.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 25 01:27:16 2016 
** Last update Sat Jun 25 01:27:21 2016 
*/

#include "commands.h"

t_avance_cmd    g_avance_cmd[5] =
  {
    {NORTH, &avance_nord},
    {SOUTH, &avance_sud},
    {EAST,  &avance_est},
    {WEST, &avance_ouest},
    {-1, NULL}
  };

void	PROTO_AVANCE(avance_nord)
{
  this->_player->_pos_y--;
  if (this->_player->_pos_y < 0)
    this->_player->_pos_y = server->_world->_s_y - 1;
}

void	PROTO_AVANCE(avance_sud)
{
  this->_player->_pos_y++;
  if (this->_player->_pos_y == server->_world->_s_y)
    this->_player->_pos_y = 0;
}

void	PROTO_AVANCE(avance_est)
{
  this->_player->_pos_x++;
  if (this->_player->_pos_x == server->_world->_s_x)
    this->_player->_pos_x = 0;
}

void	PROTO_AVANCE(avance_ouest)
{
  this->_player->_pos_x--;
  if (this->_player->_pos_x < 0)
    this->_player->_pos_x = server->_world->_s_x - 1;
}

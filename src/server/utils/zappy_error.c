/*
** utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/utils
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Mon Jun 20 18:32:50 2016 
** Last update Mon Jun 20 18:36:09 2016 
*/

#include "zappy_error.h"

void	zappy_error(const char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

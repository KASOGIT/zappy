/*
** case_utils1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 13:44:56 2016 
** Last update Thu Jun  2 13:45:38 2016 
*/

#include "case.h"

void	free_object(void *obj)
{
  if (obj)
    free(obj);
}

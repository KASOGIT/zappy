/*
** object.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/include/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 13:28:13 2016 
** Last update Thu Jun 23 15:36:35 2016 
*/

#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdlib.h>

typedef enum	e_object
  {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NONE,
    PLAYER
  }		t_object;

typedef struct	s_assos_obj
{
  t_object	obj;
  const char	*obj_str;
}		t_assos_obj;

extern struct s_assos_obj	g_assos_obj[8];

#endif /* !OBJECT_H_ */

/*
** case.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed Jun  1 23:48:49 2016 
** Last update Wed Jun 22 19:53:31 2016 
*/

#include "case.h"

void	case_set_methods(t_case *this)
{
  this->add_object = &case_add_object;
  this->fill = &case_fill;
  this->see = &case_see;
}

t_case		*case_create()
{
  t_case	*c;

  c = malloc(sizeof(t_case));
  if (c == NULL)
    zappy_error("malloc");
  case_init(c);
  return (c);
}

void	case_init(t_case *this)
{
  case_set_methods(this);
  this->_objects = list_create();
  this->_rand_gen = handle_random_create();
  this->_data_obj[0] = LINEMATE;
  this->_data_obj[1] = DERAUMERE;
  this->_data_obj[2] = SIBUR;
  this->_data_obj[3] = MENDIANE;
  this->_data_obj[4] = PHIRAS;
  this->_data_obj[5] = THYSTAME;
  this->_data_obj[6] = FOOD;
}

void	case_destroy(t_case *this)
{
  list_destroy(this->_objects);
  list_destroy_pred(this->_objects, &free_object);
}

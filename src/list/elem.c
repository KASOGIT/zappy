/*
** elem.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myirc/src/list
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat May 21 20:02:39 2016 
** Last update Sun Jun 26 21:17:43 2016 
*/

#include "elem.h"

static void	set_methods(t_elem *this)
{
  this->data = &elem_data;
  this->next = &elem_next;
  this->prev = &elem_prev;
}

t_elem		*elem_create(void *data)
{
  t_elem	*new_elem;

  new_elem = malloc(sizeof(t_elem));
  if (new_elem == NULL)
    elem_error(new_elem, "malloc", __FILE__, __LINE__);
  set_methods(new_elem);
  new_elem->_next = NULL;
  new_elem->_prev = NULL;
  new_elem->_data = data;
  return (new_elem);
}

void	elem_destroy(t_elem *this)
{
  if (this)
    {
      this->_next = NULL;
      this->_prev = NULL;
      this->_data = NULL;
      free(this);
    }
  else
    elem_warning(this, "elem_destroy", __FILE__, __LINE__);
}

void	elem_destroy_pred(t_elem *this, void (*pred)(void *elem))
{
  if (this)
    {
      (*pred)(this->_data);
      free(this);
      this->_next = NULL;
      this->_prev = NULL;
      this->_data = NULL;
    }
  else
    elem_warning(this, "elem_destroy", __FILE__, __LINE__);
}

/*
** handle_random.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Mon Jun 20 14:56:43 2016 
** Last update Sat Jun 25 01:50:04 2016 
*/

#ifndef HANDLE_RANDOM_H_
#define HANDLE_RANDOM_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "zappy_error.h"

typedef struct	s_handle_random
{
  /*
  ** Attributes
  */
  /*
  ** Methods
  */
  int	(*int_range)(struct s_handle_random *this, int min, int max);
}		t_handle_random;

/*
** Core methods
*/

void		handle_random_set_methods(t_handle_random *this);
void		handle_random_init(t_handle_random *this);
t_handle_random	*handle_random_create();
void		handle_random_destroy(t_handle_random *this);

/*
** Methods
*/

int	handle_random_int_range(t_handle_random *this, int min, int max);

/*
** Utils
*/

#endif /* !HANDLE_RANDOM_H_ */

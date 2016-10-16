/*
** handle_time.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 18 15:49:44 2016 
** Last update Sat Jun 25 17:53:33 2016 
*/

#ifndef HANDLETIME_H_
#define HANDLETIME_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "zappy_error.h"

typedef struct	s_handle_time
{
  /*
  ** Attributes
  */
  struct timeval	_start;
  struct timeval	_stop;
  /*
  ** Methods
  */
  void		(*start_chrono)(struct s_handle_time *this);
  double	(*get_mill_elapsed)(struct s_handle_time *this);
  double	(*get_micro_elapsed)(struct s_handle_time *this);
}		t_handle_time;

/*
** Core methods
*/

void		handle_time_set_methods(t_handle_time *this);
void		handle_time_init(t_handle_time *this);
t_handle_time	*handle_time_create();
void		handle_time_destroy(t_handle_time *this);

/*
** Methods
*/

void	handle_time_start_chrono(t_handle_time *this);
double	handle_time_get_mill_elapsed(t_handle_time *this);
double	handle_time_get_micro_elapsed(t_handle_time *this);

/*
** Utils
*/

#endif /* !HANDLETIME_H_ */

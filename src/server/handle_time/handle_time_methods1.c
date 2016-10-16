/*
** handle_time_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/handle_time
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 18 16:11:04 2016 
** Last update Sat Jun 25 17:50:33 2016 
*/

#include "handle_time.h"

void	handle_time_start_chrono(t_handle_time *this)
{
  gettimeofday(&this->_start, NULL);
}

double	handle_time_get_mill_elapsed(t_handle_time *this)
{
  gettimeofday(&this->_stop, NULL);
  return ((this->_stop.tv_sec - this->_start.tv_sec) * 1000.0f
	  + (this->_stop.tv_usec - this->_start.tv_usec) / 1000.0f);
}

double	handle_time_get_micro_elapsed(t_handle_time *this)
{
  gettimeofday(&this->_stop, NULL);
  return (((this->_stop.tv_sec - this->_start.tv_sec) * 1000000.0f)
	  + this->_stop.tv_usec - this->_start.tv_usec);
}

/*
** list_utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myirc/src/list
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat May 28 22:05:03 2016 
** Last update Sun Jun 19 16:30:31 2016 
*/

#include "list.h"

void	list_warning(__attribute__((unused))t_list *this,
		     const char *func,
		     const char *file,
		     int line)
{
  if (!DEBUG_LIST)
    return ;
  fprintf(stderr, "Warning: file: %s, line: %d, func: %s\n",
	  file,
	  line,
	  func);
}

void	list_error(t_list *this,
		   const char *func,
		   const char *file,
		   int line)
{
  if (!DEBUG_LIST)
    return ;
  fprintf(stderr, "Error: file: %s, line: %d, func: %s\n",
	  file,
	  line,
	  func);
  list_destroy(this);
  exit(EXIT_FAILURE);
}

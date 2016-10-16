/*
** elem_misc.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun Jun 19 16:33:12 2016 
** Last update Sun Jun 19 16:34:29 2016 
*/

#include "elem.h"

void	elem_warning(__attribute__((unused))t_elem *this,
		     const char *func,
		     const char *file,
		     int line)
{
  if (!DEBUG_ELEM)
    return ;
  fprintf(stderr, "Warning: file: %s, line: %d, func: %s\n",
	  file,
	  line,
	  func);
}

void	elem_error(t_elem *this,
		   const char *func,
		   const char *file,
		   int line)
{
  if (!DEBUG_ELEM)
    return ;
  fprintf(stderr, "Error: file: %s, line: %d, func: %s\n",
	  file,
	  line,
	  func);
  elem_destroy(this);
  exit(EXIT_FAILURE);
}

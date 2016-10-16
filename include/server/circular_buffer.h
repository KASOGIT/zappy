/*
** circular_buffer.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myirc
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue May 24 17:19:53 2016 
** Last update Mon Jun 20 18:38:24 2016 
*/

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "zappy_error.h"

#define SIZE_BUFF	512
#define ABS(x)		(x > 0 ? x : -x)

typedef struct	s_circular_buffer
{
  char		*_buff;
  char		*_idx_read;
  char		*_idx_write;
  char		*_idx_end;
  void		(*write)(struct s_circular_buffer *this, char *to_write);
  char		*(*read_cmd)(struct s_circular_buffer *this);
  void		(*warning)(struct s_circular_buffer *this,
			   const char *fun,
			   const char *file,
			   int line);
}		t_circular_buffer;

void	circular_buffer_init(t_circular_buffer *this);
void	circular_buffer_destroy(t_circular_buffer *this);
void	circular_buffer_warning(t_circular_buffer *this,
				const char *fun,
				const char *file,
				int line);
void	circular_buffer_write(t_circular_buffer *this, char *to_write);
char	*circular_buffer_read_cmd(t_circular_buffer *this);

#endif /* !CIRCULAR_BUFFER_H_ */

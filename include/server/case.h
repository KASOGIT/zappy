/*
** case.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/include/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed Jun  1 21:10:22 2016 
** Last update Thu Jun 23 15:18:25 2016 
*/

#ifndef CASE_H_
#define CASE_H_

#include <string.h>
#include "zappy_error.h"
#include "handle_random.h"
#include "object.h"
#include "list.h"

#define NB_OBJ	7

/*
** Object case
*/

typedef struct	s_case
{
  /*
  ** Attributs
  */
  t_handle_random	*_rand_gen;
  t_object		_data_obj[NB_OBJ];
  t_list		*_objects;
  /*
  ** Methods
  */
  void		(*add_object)(struct s_case *this, t_object obj);
  void		(*fill)(struct s_case *this);
  char		*(*see)(struct s_case *this);
}		t_case;

/*
** Core case object
*/

void	case_set_methods(t_case *this);
t_case	*case_create();
void	case_init(t_case *this);
void	case_destroy(t_case *this);

/*
** Methods
*/

void	case_add_object(t_case *this, t_object obj);
void	case_fill(t_case *this);
char	*case_see(t_case *this);

/*
** utils
*/

void	free_object(void *obj);

#endif /* !CASE_H_ */

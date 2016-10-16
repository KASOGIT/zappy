/*
** main.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/list
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jul 30 16:08:29 2016 
** Last update Sat Jul 30 16:17:06 2016 
*/

#include <stdio.h>
#include "list.h"

void	print_elem(void *elem)
{
  int	a = *(int *)elem;
  printf("value : %d\n", a);
}

void	print_elem2(void *elem, void *arg)
{
  int	a = *(int *)elem;
  int	ar = *(int *)elem;
  printf("res : %d\n", a + ar);
}

int	main(int ac, char**av)
{
  t_list	*list;
  int	a = 10, b = 5, c = 56;
  int	d = 10;

  list = list_create();
  list->push_back(list, &a);
  list->push_back(list, &b);
  list->push_back(list, &c);

  list->for_each(list, &print_elem);
  list->for_each_arg(list, &print_elem2, &d);
  
  list_destroy(list);
  return (0);
}

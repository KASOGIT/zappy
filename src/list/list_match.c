/*
** list_match.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/list
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue Jun 21 16:07:39 2016 
** Last update Sat Jul 30 16:13:16 2016 
*/

#include "list.h"

int		list_is_match_pred(t_list *this, int (*pred)(void *arg))
{
  t_elem	*it;
  t_elem	*end;

  it = this->begin(this);
  end = this->end(this);
  while (it != end)
    {
      if ((*pred)(it->data(it)))
	return (1);
      it = it->next(it);
    }
  if ((*pred)(it->data(it)))
    return (1);
  return (0);
}

int		list_count_match_pred(t_list *this, int (*pred)(void *arg))
{
  t_elem	*it;
  t_elem	*end;
  int		count;

  count = 0;
  it = this->begin(this);
  end = this->end(this);
  while (it != end)
  {
    if ((*pred)(it->data(it)))
      count++;
    it = it->next(it);
  }
  if ((*pred)(it->data(it)))
    count++;
  return (count);
}

int		list_count_match_pred_args(t_list *this,
					   int (*pred)(void *data, va_list ap),
					   ...)
{
  t_elem	*it;
  int		count;
  va_list	ap;
  va_list	copy;

  count = 0;
  it = this->begin(this);
  if (it == this->end(this))
    return (0);
  va_start(ap, pred);
  va_start(copy, pred);
  while (it != this->end(this))
    {
      va_copy(copy, ap);
      if ((*pred)(it->data(it), copy))
	count++;
      it = it->next(it);
    }
  va_copy(copy, ap);
  if ((*pred)(it->data(it), copy))
    count++;
  va_end(ap);
  va_end(copy);
  return (count);
}

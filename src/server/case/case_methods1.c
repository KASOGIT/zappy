/*
** case_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 13:35:32 2016 
** Last update Sun Jun 26 23:17:07 2016 
*/

#include "case.h"

void		case_add_object(t_case *this, t_object obj)
{
  t_object	*new;

  new = malloc(sizeof(t_object));
  *new = obj;
  this->_objects->push_back(this->_objects, new);
}

void	case_fill(t_case *this)
{
  int	i;
  int	rand;

  i = 0;
  if (this->_objects->size(this->_objects) >= 8)
    return ;
  this->add_object(this, FOOD);
  while (i < NB_OBJ)
    {
      if (this->_objects->size(this->_objects) >= 8)
	return ;
      rand = this->_rand_gen->int_range(this->_rand_gen,
					0, NB_OBJ + 1);
      if (rand != NB_OBJ)
	this->add_object(this, this->_data_obj[rand]);
      i++;
    }
}

static char	*routine(t_elem *it, char *str, int count)
{
  int		i;

  i = 0;
  while (g_assos_obj[i].obj != NONE)
    {
      if ((*(t_object *)it->data(it)) == g_assos_obj[i].obj)
	{
	  if (count)
	    str = strcat(str, " ");
	  str = strcat(str, g_assos_obj[i].obj_str);
	}
      i++;
    }
  return (str);
}

char		*case_see(t_case *this)
{
  t_elem	*it;
  t_elem	*end;
  char		*str;
  int		count;

  count = 0;
  if (this->_objects->size(this->_objects) == 0)
    return ("");
  str = malloc(sizeof(char) * 4096);
  str[0] = '\0';
  if (str == NULL)
    zappy_error("malloc case see");
  it = this->_objects->begin(this->_objects);
  end = this->_objects->end(this->_objects);
  while (it != end)
    {
      str = routine(it, str, count);
      it = it->next(it);
      count++;
    }
  str = routine(it, str, count);
  return (str);
}

/*
** parse_arg.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 22:08:30 2016 
** Last update Sat Jun 25 01:38:35 2016 
*/

#include "parse_arg.h"

void	init_arg(t_arg *arg)
{
  arg->port = -1;
  arg->s_x = -1;
  arg->s_y = -1;
  arg->max_client = -1;
  arg->speed = -1;
  arg->name_team = NULL;
}

void	parse_int_arg(t_arg *arg, char **av)
{
  int	i;

  i = 0;
  while (av[i])
    {
      if (av[i + 1] && strcmp(av[i], PORT_ARG) == 0)
	arg->port = atoi(av[i + 1]);
      else if (av[i + 1] && strcmp(av[i], X_ARG) == 0)
	arg->s_x = atoi(av[i + 1]);
      else if (av[i + 1] && strcmp(av[i], Y_ARG) == 0)
	arg->s_y = atoi(av[i + 1]);
      else if (av[i + 1] && strcmp(av[i], MAX_CLIENT_ARG) == 0)
	arg->max_client = atoi(av[i + 1]);
      else if (av[i + 1] && strcmp(av[i], SPEED_ARG) == 0)
	arg->speed = atoi(av[i + 1]);
      i++;
    }
}

void	parse_name_team(t_arg *arg, char **av)
{
  int	i;
  int	j;

  i = 0;
  while (av[i])
    {
      if (av[i + 1] && strcmp(av[i], NAME_TEAM_ARG) == 0)
	{
	  j = i + 1;
	  while (av[j] && av[j][0] != '-')
	    j++;
	  arg->name_team = malloc(sizeof(char *) * (j - i + 1));
	  if (arg->name_team == NULL)
	    zappy_error("parse name team malloc");
	  i++;
	  j = 0;
	  while (av[i] && av[i][0] != '-')
	    arg->name_team[j++] = strdup(av[i++]);
	  arg->name_team[j] = NULL;
	  return ;
	}
      i++;
    }
}

void	check_arg(t_arg *arg)
{
  if (arg->port == -1)
    zappy_error("bad port");
  else if (arg->s_x <= 0)
    zappy_error("bad world x");
  else if (arg->s_y <= 0)
    zappy_error("bad world y");
  else if (arg->max_client <= 0)
    zappy_error("max client");
  else if (arg->speed <= 0)
    zappy_error("speed");
  else if (arg->name_team == NULL)
    zappy_error("bad name team");
}

void	parse_arg(t_arg *arg, char **av)
{
  init_arg(arg);
  parse_int_arg(arg, av);
  parse_name_team(arg, av);
  check_arg(arg);
}

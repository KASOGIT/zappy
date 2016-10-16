/*
** parse_arg.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 22:03:01 2016 
** Last update Mon Jun 20 18:45:52 2016 
*/

#ifndef PARSE_ARG_H_
#define PARSE_ARG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_error.h"

#define PORT_ARG	"-p"
#define X_ARG		"-x"
#define Y_ARG		"-y"
#define MAX_CLIENT_ARG	"-c"
#define SPEED_ARG	"-t"
#define NAME_TEAM_ARG	"-n"

typedef struct	s_arg
{
  int		port;
  int		s_x;
  int		s_y;
  int		max_client;
  int		speed;
  char		**name_team;
}		t_arg;

void	init_arg(t_arg *arg);
void	parse_int_arg(t_arg *arg, char **av);
void	parse_arg(t_arg *arg, char **av);
void	check_arg(t_arg *arg);
void	parse_name_team(t_arg *arg, char **av);

#endif /* !PARSE_ARG_H_ */

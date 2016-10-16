/*
** main.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myirc/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May 19 19:54:31 2016 
** Last update Sun Jun 26 21:46:11 2016 
*/

#include "server.h"

static void	usage()
{
  fprintf(stderr, "Usage: ./zappy_server [-p port]");
  fprintf(stderr, "[-x world_x] [-y wolrd_y]");
  fprintf(stderr, "[-c max_client] [-t speed]");
  fprintf(stderr, "-n team_name_1 team_name_2 ...\n");
  exit(EXIT_FAILURE);
}

static void	signal_callback_handler(int signal)
{
  (void)signal;
}

int		main(int ac, char **av)
{
  t_server	server;
  t_arg		arg;

  if (ac < 13)
    usage();
  signal(SIGPIPE, &signal_callback_handler);
  parse_arg(&arg, av + 1);
  server_init(&server, &arg);
  server.server_handle_client(&server);
  server_destroy(&server);
  return (0);
}

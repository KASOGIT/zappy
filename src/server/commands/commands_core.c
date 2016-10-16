/*
** commands_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 17 15:35:45 2016 
** Last update Sun Jun 26 18:53:56 2016 
*/

#include "commands.h"

t_cmd	g_cmd[NB_CMD] =
  {
    {"avance", &cmd_avance, TO_MILL(7)},
    {"droite", &cmd_droite, TO_MILL(7)},
    {"gauche", &cmd_gauche, TO_MILL(7)},
    {"voir", &cmd_voir, TO_MILL(7)},
    {"inventaire", &cmd_inventaire, TO_MILL(1)},
    {"prend", &cmd_prend, TO_MILL(7)},
    {"pose", &cmd_pose, TO_MILL(7)},
    {"expulse", &cmd_expulse, TO_MILL(7)},
    {"broadcast", &cmd_broadcast, TO_MILL(7)},
    {"incantation", &cmd_incantation, TO_MILL(300)},
    {"fork", &cmd_fork, TO_MILL(42)},
    {"connect_nbr", &cmd_connect_nbr, 0},
    {NULL, NULL, 0}
  };

t_graph_cmd	g_cmd_graph[NB_CMD_GRAPH] =
  {
    {"msz", &cmd_msz},
    {"bct", &cmd_bct},
    {"mct", &cmd_mct},
    {"tna", &cmd_tna},
    {"ppo", &cmd_ppo},
    {"plv", &cmd_plv},
    {"pin", &cmd_pin},
    {"sgt", &cmd_sgt},
    {"sst", &cmd_sst},
    {NULL, NULL}
  };

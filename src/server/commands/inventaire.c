/*
** inventaire.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 20:29:30 2016 
** Last update Sun Jun 26 16:15:11 2016 Kévin Julien
*/

#include "commands.h"

t_inventaire	g_inventaire[8] =
  {
    {FOOD,      0},
    {LINEMATE,  0},
    {DERAUMERE, 0},
    {SIBUR,     0},
    {MENDIANE,  0},
    {PHIRAS,    0},
    {THYSTAME,  0},
    {NONE,      0}
  };

inline void	reset_inventaire()
{
  int		i;

  for (i = 0; g_inventaire[i].obj != NONE; ++i)
    g_inventaire[i].nbr = 0;
}

void		inventaire(void *data)
{
  t_object	objectFromData;
  int		i;

  objectFromData = *((t_object *)data);
  for (i = 0; g_inventaire[i].obj != NONE; ++i)
    {
      if (g_inventaire[i].obj == objectFromData)
        {
	  g_inventaire[i].nbr++;
	  break ;
        }
    }
}

void	PROTO_CMD(cmd_inventaire)
{
  char	msg[1024];
  int	i;

  (void)arg;
  (void)server;
  reset_inventaire();
  memset(msg, '\0', 1024);
  sprintf(msg, "{");
  if (!this->_player->_inventory)
    return ;
  this->_player->_inventory->for_each(this->_player->_inventory, &inventaire);
  for (i = 0; g_inventaire[i].obj != NONE; i++)
    {
      sprintf(msg + strlen(msg), "%s ",
	      get_raw_object_type(g_inventaire[i].obj));
      if (g_inventaire[i].obj == FOOD)
        sprintf(msg + strlen(msg), "%d,",
                (int)(((this->_player->_unit_time / 1000.0f)
		       / (1.0f / (double)g_time_delay)) / 126.0f));
      else
        sprintf(msg + strlen(msg), "%d,",
                g_inventaire[i].nbr);
    }
  sprintf(msg + strlen(msg) - 1, "}\n");
  this->send_msg(this, msg);
}

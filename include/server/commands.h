/*
** commands.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:17:32 2016 
** Last update Sun Jun 26 23:11:29 2016 
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include "handle_client.h"
#include "server.h"
#include "way.h"
#include "object.h"
#include "utils.h"
#include "list.h"

#define NB_CMD	13
#define NB_CMD_GRAPH	10
#define MAX_ORIENTATION 8
#define PROTO_AVANCE(name)  name(t_handle_client *this, t_server *server)
#define PROTO_CMD(name)     name(t_handle_client *this,	\
				 t_server *server,	\
				 char **arg)
#define PROTO_CMD_GRAPH(name)	name(t_handle_client *this,	\
				     enum WHOSE_SEND_MSG whose)
#define UNUSED              __attribute__((unused))

typedef struct s_handle_client	t_handle_client;
typedef struct s_server		t_server;

typedef struct	s_cmd
{
  char		*cmd;
  void		(*func_cmd)(t_handle_client *this,
			    t_server *server,
			    char **arg);
  int		duration;
}		t_cmd;

typedef struct	s_graph_cmd
{
  char		*cmd;
  void		(*func_cmd)(t_handle_client *this, enum WHOSE_SEND_MSG);
}		t_graph_cmd;

/* AVANCE */
typedef struct	s_avance_cmd
{
  t_way		WAY;
  void		(*func_avance)(t_handle_client *this, t_server *server);
}               t_avance_cmd;

/* DROITE - GAUCHE */
typedef struct  s_way_cmd
{
  t_way		WAY_ORIG;
  t_way		NEW_WAY;
}               t_way_cmd;

/*  PREND - POSE  */
typedef struct	s_object_converter
{
  const char	*raw_object;
  t_object	object;
}               t_object_converter;

/*
** INVENTAIRE
*/

typedef struct	s_inventaire
{
  t_object	obj;
  int		nbr;
}		t_inventaire;

/*
** INCANTATION
*/
typedef struct	s_incantation_rules
{
  int		LEVEL;
  int		NB_REQUIRED_PLAYERS;
  int		NB_LINEMATE;
  int		NB_DERAUMERE;
  int		NB_SIBUR;
  int		NB_MENDIANE;
  int		NB_PHIRAS;
  int		NB_THYSTAME;
}		t_incantation_rules;

/*
** BROADCAST
*/
typedef struct	s_vector2d
{
  double	x;
  double	y;
  double	distance;
}		t_vector2d;

extern struct s_cmd			g_cmd[NB_CMD];
extern struct s_graph_cmd		g_cmd_graph[NB_CMD_GRAPH];
extern struct s_avance_cmd		g_avance_cmd[5];
extern struct s_way_cmd			g_droite_cmd[4];
extern struct s_way_cmd			g_gauche_cmd[4];
extern struct s_object_converter	g_object_converter[9];
extern struct s_inventaire		g_inventaire[8];
/*
** CMD AI
*/

void            PROTO_CMD(cmd_droite);
void            PROTO_CMD(cmd_avance);
void            PROTO_CMD(cmd_voir);
void            PROTO_CMD(cmd_inventaire);
void            PROTO_CMD(cmd_incantation);
void            PROTO_CMD(cmd_gauche);
void            PROTO_CMD(cmd_pose);
void            PROTO_CMD(cmd_expulse);
void            PROTO_CMD(cmd_broadcast);
void            PROTO_CMD(cmd_fork);
void            PROTO_CMD(cmd_connect_nbr);

/*
** CMD GRAPH
*/
void		PROTO_CMD_GRAPH(cmd_msz);
void		PROTO_CMD_GRAPH(cmd_bct);
void		PROTO_CMD_GRAPH(cmd_mct);
void		PROTO_CMD_GRAPH(cmd_tna);
void		PROTO_CMD_GRAPH(cmd_ppo);
void		PROTO_CMD_GRAPH(cmd_plv);
void		PROTO_CMD_GRAPH(cmd_pin);
void		PROTO_CMD_GRAPH(cmd_sgt);
void		PROTO_CMD_GRAPH(cmd_sst);

/*
** AVANCE
*/
void            PROTO_AVANCE(avance_sud);
void            PROTO_AVANCE(avance_nord);
void            PROTO_AVANCE(avance_est);
void            PROTO_AVANCE(avance_ouest);
void            PROTO_AVANCE(send_pos_to_graphics);

/*
** PREND
*/
void            PROTO_CMD(cmd_prend);

/*
** POSE
*/
void            PROTO_CMD(cmd_pose);
void            send_prend_pose_to_graphics(t_handle_client *this,
					    t_server *server,
					    t_object object,
					    enum WHICH_PREND_POSE which);

/*
** UTILS CMD
*/
int             is_object_type(void *data, void *args);
t_object        get_object_type(char *str);
const char      *get_raw_object_type(t_object obj);
void            inventaire(void *data);
void            reset_inventaire();
int             check_args_bct(t_handle_client *this,
			       int *pos_x,
			       int *pos_y);
void            prepare_bct_message(t_handle_client *this,
				    int pos_x,
				    int pos_y,
				    char *msg);
void            cmd_bct_with_pos(t_handle_client *this,
                                 int pos_x,
                                 int pos_y);
void            cmd_bct_with_pos_graphics(t_handle_client *this,
					  int pos_x,
					  int pos_y);
int             get_nb_players_incantation(void *data, va_list ap);

int             check_for_incantation(t_handle_client *this,
				      int nb_players);
void		begin_incantation(int *nb_players,
				  t_handle_client *this,
				  char *msg,
				  t_list *list_players);
void            incantation_end(t_handle_client *current,
				t_list *list_players,
				char *msg);
double          calc_distance(const double x,
                              const double y,
                              const double x2,
                              const double y2);
void            broadcast(void *data, void *args);
int				get_user_by_id(void *data, void *arg);
void            pin_send_msg(t_handle_client *player,
			     enum WHOSE_SEND_MSG whose,
			     char *msg,
			     t_handle_client *this);
#endif /* !COMMANDS_H_ */

##
## Makefile for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_philo
## 
## Made by adam soto
## Login   <soto_a@epitech.net>
## 
## Started on  Wed Mar  2 12:54:44 2016 
## Last update Mon Oct 17 00:27:09 2016 
##

ZAPPY_SERVER	= zappy_server

ZAPPY_AI	= zappy_ai

CFLAGS	= -I./include -I./include/client_ai -I./include/server -I./src/list/ -O2 -pipe
LDFLAGS	= -lm

CC	= gcc

SRC_UTILS	= utils.c \

SRC_LIST	= elem.c \
		  elem_misc.c \
		  elem_getters.c \
		  list.c \
		  list_match.c \
		  list_adding.c \
		  list_get.c \
		  list_iter.c \
		  list_loop.c \
		  list_misc.c \
		  list_rm.c \
		  list_rm2.c \
		  list_utils.c \

SRC_SOCKET	= socket.c \
		  socket_manage.c \

SRC_SERVER	= main.c \
		  object/object.c \
		  utils/zappy_error.c \
		  utils/math_functions.c \
		  handle_random/handle_random_core.c \
		  handle_random/handle_random_methods1.c \
		  handle_time/handle_time_methods1.c \
		  handle_time/handle_time_core.c \
		  action/action_core.c \
		  action/action_methods1.c \
		  commands/commands_core.c \
		  commands/commands_methods1.c \
		  commands/commands_methods2.c \
		  commands/avance.c \
		  commands/droite_gauche.c \
		  commands/prend_pose.c \
		  commands/inventaire.c \
		  commands/broadcast.c \
		  commands/incantation.c \
		  commands/bct.c    \
		  commands/commands_fork.c \
		  commands/commands_incant.c \
		  commands/commands_methods3.c \
		  commands/commands_prend_pose.c \
		  commands/commands_pin.c \
		  case/case_core.c \
		  case/case_methods1.c \
		  case/case_utils1.c \
		  handle_client/handle_client_core.c \
		  handle_client/handle_client_methods1.c \
		  handle_client/handle_client_methods2.c \
		  handle_client/handle_client_methods3.c \
		  parse/parse_arg.c \
		  player/player_core.c \
		  player/player_methods1.c \
		  server/server_core.c \
		  server/server_methods1.c \
		  server/server_methods2.c \
		  server/server_methods3.c \
		  server/server_methods4.c \
		  server/server_methods5.c \
		  server/server_utils1.c \
		  server/server_utils2.c \
		  server/server_utils3.c \
		  server/server_utils4.c \
		  team/team_core.c \
		  team/team_methods1.c \
		  circular_buffer/circular_buffer.c \
		  circular_buffer/circular_buffer_io.c \
		  world/world_core.c \
		  world/world_methods1.c \
		  world/world_methods2.c \
		  world/world_utils3.c \
		  world/world_utils2.c \
		  world/world_utils1.c \

OBJ_UTILS	= $(addprefix src/utils/, $(SRC_UTILS:.c=.o))

OBJ_LIST	= $(addprefix src/list/, $(SRC_LIST:.c=.o))

OBJ_SOCKET	= $(addprefix src/socket/, $(SRC_SOCKET:.c=.o))

OBJ_SERVER	= $(addprefix src/server/, $(SRC_SERVER:.c=.o))

# FLAGS MAC OS X
ifeq ($(shell uname), Darwin)
        CFLAGS += -arch x86_64
        LDFLAGS += -arch x86_64
    endif

all:		$(ZAPPY_AI) $(ZAPPY_SERVER)

$(ZAPPY_SERVER):	$(OBJ_SERVER) $(OBJ_SOCKET) $(OBJ_LIST) $(OBJ_UTILS)
			$(CC) $(OBJ_SERVER) $(OBJ_SOCKET) $(OBJ_LIST) $(OBJ_UTILS) $(LDFLAGS) -o $(ZAPPY_SERVER)

$(ZAPPY_AI):
	$(shell echo './src/client_ai/zappy_ai.py $$*' > $(ZAPPY_AI))
	$(shell chmod 755 $(ZAPPY_AI))

clean:
	rm -rf $(OBJ_SERVER)
	rm -rf $(OBJ_LIST)
	rm -rf $(OBJ_SOCKET)
	rm -rf $(OBJ_UTILS)

fclean: clean
	rm -rf $(ZAPPY_SERVER)
	rm -rf $(ZAPPY_AI)

re: fclean all

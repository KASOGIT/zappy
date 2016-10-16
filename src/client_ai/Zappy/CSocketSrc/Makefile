##
## Makefile for Zappy_CSocket in /home/oliva/_workspace_zappy/ai_client/Zappy/CSocket
## 
## Made by Clement Oliva
## Login   <oliva@epitech.net>
## 
## Started on  Fri Jun 17 14:04:57 2016 Clement Oliva
## Last update Sat Jun 25 23:31:14 2016 Clement Oliva
##

NAME	=	../CSocket.so

SOCKSRC	=	socket/socket.c		\
		socket/socket_manage.c

SRC	=	CSocket.c		\
		CSocketBase.c		\
		CSocketWrapper.c	\
		$(SOCKSRC)

OBJ	=	$(addprefix src/, $(SRC:.c=.o))

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-W -Wall -Wextra -Werror
CFLAGS  +=	-Iinclude
CFLAGS	+=	-fPIC

LDFLAGS	=	-lpython3.4m -Llib

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) -shared $(LDFLAGS) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

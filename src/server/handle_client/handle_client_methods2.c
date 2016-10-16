/*
** handle_client_utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 11:04:46 2016 
** Last update Sun Jun 26 20:16:50 2016 
*/

#include "handle_client.h"

void		handle_client_send_msg(t_handle_client *this,
				       const char *msg)
{
  ssize_t	ret;

  ret = write(this->_fd, msg, strlen(msg));
  if (ret == -1)
    {
      if (this->_team != NULL)
	this->_team->_client->erase_by_elem(this->_team->_client, this);
      this->_parent->_users->erase_by_elem(this->_parent->_users, this);
    }
}

char	**handle_client_cpy_arg(t_handle_client *this)
{
  char	**arg;
  int	i;

  if (this->_args == NULL)
    return (NULL);
  arg = malloc(sizeof(char *) * (size_wordtab(this->_args) + 1));
  if (arg == NULL)
    perror("malloc cpy arg");
  i = 0;
  while (this->_args[i])
    {
      arg[i] = strdup(this->_args[i]);
      i++;
    }
  arg[i] = NULL;
  return (arg);
}

int	handle_client_get_cmd_id(t_handle_client *this)
{
  int	i;

  i = 0;
  if (this->_cmd)
    {
      while (g_cmd[i].cmd != NULL)
	{
	  if (strncmp(this->_cmd, g_cmd[i].cmd,
		      strlen(g_cmd[i].cmd)) == 0)
	    {
	      return (i);
	    }
	  i++;
	}
      if (i == NB_CMD)
	printf("unknow cmd\n");
    }
  return (-1);
}

int	handle_client_get_cmd_graph_id(t_handle_client *this)
{
  int	i;

  i = 0;
  if (this->_cmd)
    {
      while (g_cmd_graph[i].cmd != NULL)
	{
	  if (strncmp(this->_cmd, g_cmd_graph[i].cmd,
		      strlen(g_cmd_graph[i].cmd)) == 0)
	    {
	      return (i);
	    }
	  i++;
	}
      if (i == NB_CMD_GRAPH)
	printf("unknow cmd\n");
    }
  return (-1);
}

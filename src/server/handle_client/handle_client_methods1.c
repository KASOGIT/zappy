/*
** handle_client_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/handle_client
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun  4 00:21:37 2016 
** Last update Sun Jun 26 22:32:12 2016 
*/

#include "handle_client.h"

void	handle_client_fill_buff(t_handle_client *this,
				__attribute__((unused))t_server *server)
{
  char	buff[512];
  int	rd;

  signal(SIGPIPE, SIG_IGN);
  memset(buff, 0, 512);
  rd = read(this->_fd, buff, 512);
  if (rd == -1)
    perror("read");
  else if (rd == 0 && this)
    {
      sprintf(buff, "pdi #%d\n", this->_id);
      this->_parent->send_msg_to_client_graph(this->_parent, buff);
      if (this->_type == CLIENT_AI)
	this->_team->_client->erase_by_elem(this->_team->_client, this);
      this->_parent->_users->erase_by_elem(this->_parent->_users, this);
      this->send_msg(this, "mort\n");
      handle_client_destroy(this);
    }
  else
    {
      buff[rd] = '\0';
      this->_buffer.write(&this->_buffer, buff);
    }
}

void	handle_client_read_cmd(t_handle_client *this)
{
  char	*cmd;
  char	**split_cmd;

  cmd = this->_buffer.read_cmd(&this->_buffer);
  if (cmd && strlen(cmd) >= 3)
    {
      split_cmd = str_to_wordtab(strdup(cmd));
      this->_cmd = split_cmd[0];
      this->_args = split_cmd + 1;
      free(cmd);
    }
  else
    {
      this->_cmd = NULL;
      this->_args = NULL;
    }
}

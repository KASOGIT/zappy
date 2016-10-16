/*
** commands_prend_pose.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 17:37:22 2016 
** Last update Sun Jun 26 05:30:22 2016 
*/

#include "commands.h"

void		PROTO_CMD(cmd_prend)
{
  void		*elem;
  t_list	*list_objects;
  t_object	object;

  if (ASSERT_ARGS_CMD(arg))
    {
      this->send_msg(this, "ko\n");
      return ;
    }
  object = get_object_type(arg[0]);
  list_objects = server->_world->_map[this->_player->_pos_y]
    [this->_player->_pos_x]->_objects;
  elem = list_objects->get_elem_by_pred_arg(list_objects, &is_object_type,
					    &object);
  if (!elem)
    this->send_msg(this, "ko\n");
  else
    {
      if (*((t_object *) elem) == FOOD)
	this->_player->eat(this->_player);
      else
	this->_player->_inventory->push_back(this->_player->_inventory, elem);
      list_objects->erase_by_elem(list_objects, elem);
      send_prend_pose_to_graphics(this, server, object, PREND);
    }
}

void		PROTO_CMD(cmd_pose)
{
  t_list	*list_objects;
  t_object	object;
  void		*elem;

  if (ASSERT_ARGS_CMD(arg))
    {
      this->send_msg(this, "ko\n");
      return ;
    }
  list_objects = this->_player->_inventory;
  object = get_object_type(arg[0]);
  elem = list_objects->get_elem_by_pred_arg(list_objects,
					    &is_object_type,
					    &object);
  if (!elem)
    this->send_msg(this, "ko\n");
  else
    {
      server->_world->_map[this->_player->_pos_y][this->_player->_pos_x]
	->add_object(server->_world->_map[this->_player->_pos_y]
		     [this->_player->_pos_x], object);
      list_objects->erase_by_elem(list_objects, elem);
      send_prend_pose_to_graphics(this, server, object, POSE);
    }
}

/*
** Map.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph
** 
** Made by Kévin Julien
** Login   <julien_k@epitech.net>
** 
** Started on  Wed Jun 15 15:50:24 2016 Kévin Julien
// Last update Wed Jun 15 17:21:27 2016 Kévin Julien
*/

#ifndef MAP_HPP
#define MAP_HPP

#include <irrlicht.h>
#include <vector>

class Map
{
public:
  Map(int x, int y);
  ~Map();

public:
  void		addGround(irr::scene::ISceneManager *, irr::video::ITexture *);

private:
  int	_x;
  int	_y;

private:
  std::vector<std::vector<irr::scene::IMeshSceneNode	*> *>	_ground;
};

#endif /* !MAP_HPP */

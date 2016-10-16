//
// Map.cpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Wed Jun 15 15:52:04 2016 Kévin Julien
// Last update Wed Jun 15 17:26:08 2016 Kévin Julien
//

#include "Map.hpp"

Map::Map(int x, int y) :
  _x(x),
  _y(y)
{
}


Map::~Map()
{
}

void		Map::addGround(irr::scene::ISceneManager *manager,
			       irr::video::ITexture *texture)
{
  irr::core::vector3df	pos;

  for (int i = 0; i <= _x; i++) {
    std::vector < irr::scene::IMeshSceneNode * > *column = new std::vector<irr::scene::IMeshSceneNode *>(_y);
    _ground.push_back(column);
  }
  for (int x = 0; x <= _x; x++) {
    for (int y = 0; y < _y; y++) {
      pos.X = x;
      pos.Y = 0;
      pos.Z = y;
      (*_ground[x])[y] = manager->addCubeSceneNode(1, 0, -1, pos);
      (*_ground[x])[y]->setMaterialTexture(0, texture);
      (*_ground[x])[y]->setScale(irr::core::vector3df(1, 0.01, 1));
      (*_ground[x])[y]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      (*_ground[x])[y]->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, true);
    }
  }
}

//
// Egg.cpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:22:09 2016 Kévin Julien
// Last update Fri Jun 24 16:16:34 2016 Kévin Julien
//

#include "Egg.hpp"

Egg::Egg(int x, int z,
	     irr::scene::ISceneManager *sceneManager,
	     irr::video::IVideoDriver *driver) :
  _x(x),
  _z(z)
{
  _mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../../../asset/Egg/egg.obj"));
  _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _mesh->setMaterialTexture(0, driver->getTexture("../../../asset/Egg/BlueSteelEgg.png"));
  _mesh->setScale(irr::core::vector3df(0.15, 0.15, 0.15));
  _mesh->setPosition(irr::core::vector3df(x, 0.2, z));
}

Egg::~Egg()
{
}

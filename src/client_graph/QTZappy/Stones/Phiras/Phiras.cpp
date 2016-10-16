//
// Phiras.cpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:22:09 2016 Kévin Julien
// Last update Fri Jun 24 15:57:18 2016 Kévin Julien
//

#include "Phiras.hpp"

Phiras::Phiras(int x, int z,
	     irr::scene::ISceneManager *sceneManager,
	     irr::video::IVideoDriver *driver) :
  IStone(4, x, z)
{
  _mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../../../asset/Red Orb/Red Orb.obj"));
  _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _mesh->setMaterialTexture(0, driver->getTexture("../../../asset/Red Orb/Textures/grey.jpeg"));
  _mesh->setScale(irr::core::vector3df(1, 1, 1));
  _mesh->setPosition(irr::core::vector3df(x, 0.02, z - 0.25));
}

Phiras::~Phiras()
{
}

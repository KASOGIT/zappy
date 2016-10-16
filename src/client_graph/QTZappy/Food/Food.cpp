//
// Food.cpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:22:09 2016 Kévin Julien
// Last update Sun Jun 26 10:41:28 2016 Kévin Julien
//

#include "Food.hpp"

Food::Food(int x, int z,
	     irr::scene::ISceneManager *sceneManager,
	     irr::video::IVideoDriver *driver) :
  _x(x),
  _z(z)
{
  _mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../../../asset/Apple/apple.obj"));
  _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _mesh->setMaterialTexture(0, driver->getTexture("../../../asset/Apple/skin.jpg"));
  _mesh->setScale(irr::core::vector3df(0.005, 0.005, 0.005));
  _mesh->setPosition(irr::core::vector3df(x, 0.2, z));
}

Food::~Food()
{
}

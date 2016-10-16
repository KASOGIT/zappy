//
// Character.cpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 17 16:29:23 2016 Kévin Julien
// Last update Sun Jun 26 02:26:43 2016 Kévin Julien
//

#include "Character.hpp"

Character::Character(int pos_x, int pos_z, int id,
             irr::scene::ISceneManager *sceneManager,
		     irr::video::IVideoDriver *driver) :
  _x(pos_x),
  _z(pos_z),
  _id(id),
  _move(false)
{
  _mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../../../asset/mesh/Droid.md2"));
  _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _mesh->setMaterialTexture(0, driver->getTexture("../../../asset/texture/Droid.jpg"));
  _mesh->setScale(irr::core::vector3df(0.025, 0.025, 0.025));
  _mesh->setRotation(irr::core::vector3df(0, 90, 0));
  _mesh->setPosition(irr::core::vector3df(pos_x, 0.5, pos_z));
}


Character::~Character()
{
}

int		Character::getId() const
{
  return (_id);
}

void		Character::move(int x, int z, int o, irr::scene::ISceneManager *sceneManager)
{
  irr::scene::ISceneNodeAnimator *anim;
  int				move_x = (x > _x) ? x - _x : _x - x;
  int				move_z = (z > _z) ? z - _z : _z - z;

  anim = sceneManager->createFlyStraightAnimator(_mesh->getPosition(), irr::core::vector3df(x, 0.5, z),
						 (move_x + move_z) * 500, true);

  if (anim) {
    _mesh->addAnimator(anim);
    _mesh->setMD2Animation(irr::scene::EMAT_RUN);
    anim->drop();
    _x = x;
    _z = z;
    _mesh->setPosition(irr::core::vector3df(x, 0.5, z));
    _move = true;
  }
  if (o == 1) {
    _mesh->setRotation(irr::core::vector3df(0, 90, 0));
  }
  else if (o == 2) {
    _mesh->setRotation(irr::core::vector3df(0, 0, 0));
  }
  else if (o == 3) {
    _mesh->setRotation(irr::core::vector3df(0, 270, 0));
  }
  else if (o == 4) {
    _mesh->setRotation(irr::core::vector3df(0, 180, 0));
  }
}

irr::scene::IAnimatedMeshSceneNode	*Character::getMesh() const
{
  return (_mesh);
}

bool					Character::getMove() const
{
  return (_move);
}

int					Character::getX() const
{
  return (_x);
}

int					Character::getZ() const
{
  return (_z);
}

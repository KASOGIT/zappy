//
// IStone.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:07:39 2016 Kévin Julien
// Last update Fri Jun 24 16:20:37 2016 Kévin Julien
//

#ifndef STONE_HPP_
#define STONE_HPP_

#include <irrlicht.h>

class IStone
{
public:
  IStone(int type, int x, int z) :
    _type(type),
    _x(x),
    _z(z) {};
  virtual ~IStone() {};

public:
  irr::scene::IAnimatedMeshSceneNode    *getMesh() const {
      return (_mesh);
  }
  int		getType() const
  {
    return (_type);
  }
  int		getX() const {
    return (_x);
  }
  int		getZ() const {
    return (_z);
  }
protected:
  int					_type;
  int					_x;
  int					_z;
  irr::scene::IAnimatedMeshSceneNode	*_mesh;
};

#endif 

//
// Food.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Sun Jun 26 10:28:53 2016 Kévin Julien
//

#ifndef FOOD_HPP_
#define FOOD_HPP_

#include <irrlicht.h>

class	Food
{
public:
  Food(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  ~Food();

public:
   irr::scene::IAnimatedMeshSceneNode	*getMesh() const {
       return (_mesh);
   }
  int		getX() const {
    return (_x);
  }
  int		getZ() const {
    return (_z);
  }
private:
  int					_x;
  int					_z;
  irr::scene::IAnimatedMeshSceneNode	*_mesh;

};

#endif /* !FOOD_HPP_ */

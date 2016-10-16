//
// Character.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 17 16:26:14 2016 Kévin Julien
// Last update Sun Jun 26 02:23:09 2016 Kévin Julien
//

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <irrlicht.h>

class Character
{
public:
  Character(int, int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  ~Character();

public:
  int					getId() const;
  int					getX() const;
  int					getZ() const;
  bool					getMove() const;
  irr::scene::IAnimatedMeshSceneNode	*getMesh() const;

public:
  void		move(int, int, int, irr::scene::ISceneManager *);

private:
  int					_x;
  int					_z;
  int					_id;
  bool					_move;
  irr::scene::IAnimatedMeshSceneNode	*_mesh;
};


#endif /* !CHARACTER_HPP_ */

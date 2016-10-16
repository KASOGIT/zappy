//
// Thystame.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Fri Jun 24 15:58:46 2016 Kévin Julien
//

#ifndef THYSTAME_HPP_
#define THYSTAME_HPP_

#include "IStone.hpp"

class	Thystame : public IStone
{
public:
  Thystame(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  virtual ~Thystame();
};

#endif /* !THYSTAME_HPP_ */

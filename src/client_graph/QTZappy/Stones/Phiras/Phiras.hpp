//
// Phiras.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Fri Jun 24 15:45:16 2016 Kévin Julien
//

#ifndef PHIRAS_HPP_
#define PHIRAS_HPP_

#include "IStone.hpp"

class	Phiras : public IStone
{
public:
  Phiras(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  virtual ~Phiras();
};

#endif /* !PHIRAS_HPP_ */

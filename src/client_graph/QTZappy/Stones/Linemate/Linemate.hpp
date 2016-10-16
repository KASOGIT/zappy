//
// Linemate.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Fri Jun 24 14:59:34 2016 Kévin Julien
//

#ifndef LINEMATE_HPP_
#define LINEMATE_HPP_

#include "IStone.hpp"

class	Linemate : public IStone
{
public:
  Linemate(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  virtual ~Linemate();
};

#endif /* !LINEMATE_HPP_ */

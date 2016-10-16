//
// Mendiane.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Fri Jun 24 15:38:37 2016 Kévin Julien
//

#ifndef MENDIANE_HPP_
#define MENDIANE_HPP_

#include "IStone.hpp"

class	Mendiane : public IStone
{
public:
  Mendiane(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  virtual ~Mendiane();
};

#endif /* !MENDIANE_HPP_ */

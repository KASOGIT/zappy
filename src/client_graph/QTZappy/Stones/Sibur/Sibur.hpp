//
// Sibur.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Fri Jun 24 14:44:39 2016 Kévin Julien
//

#ifndef SIBUR_HPP_
#define SIBUR_HPP_

#include "IStone.hpp"

class	Sibur : public IStone
{
public:
  Sibur(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  virtual ~Sibur();
};

#endif /* !SIBUR_HPP_ */

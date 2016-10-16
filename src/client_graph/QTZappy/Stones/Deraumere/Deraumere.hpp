//
// Deraumere.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph/Stones
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Fri Jun 24 14:06:09 2016 Kévin Julien
// Last update Fri Jun 24 15:26:51 2016 Kévin Julien
//

#ifndef DERAUMERE_HPP_
#define DERAUMERE_HPP_

#include "IStone.hpp"

class	Deraumere : public IStone
{
public:
  Deraumere(int, int, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
  virtual ~Deraumere();
};

#endif /* !DERAUMERE_HPP_ */

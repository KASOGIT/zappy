/*
** Graph.hpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph
** 
** Made by Kévin Julien
** Login   <julien_k@epitech.net>
** 
** Started on  Wed Jun 15 15:50:24 2016 Kévin Julien
// Last update Sun Jun 26 10:42:34 2016 Kévin Julien
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <sstream>
#include <iostream>
#include <irrlicht.h>
#include <chrono>
#include <thread>
#include <vector>
#include <QWidget>
#include "Map.hpp"
#include "Character.hpp"
#include "IStone.hpp"
#include "Linemate.hpp"
#include "Deraumere.hpp"
#include "Sibur.hpp"
#include "Mendiane.hpp"
#include "Phiras.hpp"
#include "Thystame.hpp"
#include "Egg.hpp"
#include "Food.hpp"

class Graph : public QWidget
{
  typedef void (Graph::*fctStone)(int, int);
public:
  Graph(int x, int y, QWidget*);
  ~Graph();

public:
  void       installEventFilter(QMouseEvent *filterObj);
  void		print();
  void		addCharacter(int, int, int);
  void		moveCharacter(int, int, int, int);
  void		rotateCharacter(int, int);
  void		checkMoveAllCharacters();

public:
  void		addStone(int, int, int);
  void		addLinemate(int, int);
  void		addDeraumere(int, int);
  void		addSibur(int, int);
  void		addMendiane(int, int);
  void		addPhiras(int, int);
  void		addThystame(int, int);
  void		deleteStone(int, int, int);

public:
  void		addEgg(int, int);
  void		deleteEgg(int, int);
  void		addFood(int, int);
  void		deleteFood(int, int);

public:
  void             deleteCharacter(int id);
  Map				*getMap() const;
  irr::IrrlichtDevice		*getDevice() const;
  irr::video::IVideoDriver	*getDriver() const;
  irr::scene::ISceneManager	*getSceneManager() const;
  irr::gui::IGUIEnvironment	*getGUI() const;
  irr::scene::ICameraSceneNode	*getCamera() const;
  Character			*getCharacter(int) const;

private:
  irr::SKeyMap keyMap[5];
  irr::IrrlichtDevice			*_device;
  irr::video::IVideoDriver		*_driver;
  irr::scene::ISceneManager		*_sceneManager;
  irr::gui::IGUIEnvironment		*_gui;
  irr::scene::ICameraSceneNode		*_camera;

private:
  int					_wigth = 1280;
  int					_height = 720;
  Map					*_map;
  std::map<int, fctStone>		_funcStone;
  std::vector<Character *>		_characters;
  std::vector<IStone *>			_stones;
  std::vector<Egg *>			_eggs;
  std::vector<Food *>			_foods;
};

#endif /* !GRAPH_HPP */

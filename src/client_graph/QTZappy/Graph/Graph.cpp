//
// Map.cpp for zappy in /home/julien_k/PSU_2015_zappy/src/client_graph
// 
// Made by Kévin Julien
// Login   <julien_k@epitech.net>
// 
// Started on  Wed Jun 15 16:07:34 2016 Kévin Julien
// Last update Sun Jun 26 10:43:33 2016 Kévin Julien
//

#include <QDebug>
#include "Graph.hpp"

Graph::Graph(int x, int y, QWidget *parent)
    :   QWidget(parent)
{
    //irr::SKeyMap keyMap[5];

    irr::SIrrlichtCreationParameters    parameters;

    parameters.WindowId = reinterpret_cast<void*>(parent->winId());
    parameters.DriverType = irr::video::EDT_OPENGL;

   _device = irr::createDeviceEx(parameters);
  _driver = _device->getVideoDriver();
  _sceneManager = _device->getSceneManager();
    _map = new Map(x - 1, y);
  _funcStone[0] = &Graph::addLinemate;
  _funcStone[1] = &Graph::addDeraumere;
  _funcStone[2] = &Graph::addSibur;
  _funcStone[3] = &Graph::addMendiane;
  _funcStone[4] = &Graph::addPhiras;
  _funcStone[5] = &Graph::addThystame;
  setFocusPolicy(Qt::TabFocus);
  keyMap[0].Action = irr::EKA_MOVE_FORWARD;
  keyMap[0].KeyCode = irr::KEY_KEY_Z;
  keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
  keyMap[1].KeyCode = irr::KEY_KEY_S;
  keyMap[2].Action = irr::EKA_STRAFE_LEFT;
  keyMap[2].KeyCode = irr::KEY_KEY_Q;
  keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
  keyMap[3].KeyCode = irr::KEY_KEY_D;
  _camera = _sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.01f, -1, keyMap, 5);
  _camera->setPosition(irr::core::vector3df(x / 2, y / 2 + 10, -6.));
  _camera->setTarget(irr::core::vector3df(x / 2, 0., y / 2));
  _camera->setFarValue(50000);
  _map->addGround(_sceneManager, _driver->getTexture("../../../asset/texture/grass.png"));
}

Graph::~Graph()
{
}

void      Graph::installEventFilter(QMouseEvent *filterObj) {
    static int i = 0;
    i += 1;
}

void		Graph::print()
{
    if (_device->run()) {
        setFocusPolicy(Qt::TabFocus);
        _driver->beginScene(true, true, irr::video::SColor(0, 255, 255, 255));
        checkMoveAllCharacters();
        _sceneManager->drawAll();
        _driver->endScene();
    }
}

void				Graph::addCharacter(int x, int z, int id)
{
    Character *test = new Character(x, z, id, _sceneManager, _driver);
    _characters.push_back(test);
}

void				Graph::moveCharacter(int id, int x, int z, int o)
{
    int             i = 0;
  for (auto it = _characters.begin(); it != _characters.end(); ++it)
    {
      if ((*it)->getId() == id) {
        _characters.at(i)->move(x, z, o, _sceneManager);
      }
      i += 1;
    }
}

void				Graph::checkMoveAllCharacters()
{
  for (auto it = _characters.begin(); it != _characters.end(); ++it)
    {
      if ((*it)->getMove() == true) {
        irr::core::vector3df	pos = (*it)->getMesh()->getPosition();
	
	if (fabs(pos.X - (*it)->getX()) < 0.1 && fabs(pos.Z - (*it)->getZ()) < 0.1) {
	  (*it)->getMesh()->removeAnimators(); 
	  (*it)->getMesh()->setMD2Animation(irr::scene::EMAT_STAND);
	}
      }
    }

}

void             Graph::deleteCharacter(int id)
{
    for (auto it = _characters.begin(); it != _characters.end(); ++it) {
       if ((*it)->getId() == id) {
            (*it)->getMesh()->remove();
           _characters.erase(it);
           break;
       }
     }
}

void				Graph::deleteStone(int type, int x, int z)
{
  for (auto it = _stones.begin(); it != _stones.end(); ++it)
    {
      if ((*it)->getX() == x && (*it)->getZ() == z && (*it)->getType() == type) {
         (*it)->getMesh()->remove();
        _stones.erase(it);
      }
    }
}

void				Graph::addStone(int type, int x, int z)
{
  fctStone	_func = _funcStone[type];
  if (_func) {
    (this->*_func)(x, z);
  }
}

void				Graph::addLinemate(int x, int z)
{
  _stones.push_back(new Linemate(x, z, _sceneManager, _driver));
}

void				Graph::addDeraumere(int x, int z)
{
  _stones.push_back(new Deraumere(x, z, _sceneManager, _driver));
}

void				Graph::addSibur(int x, int z)
{
  _stones.push_back(new Sibur(x, z, _sceneManager, _driver));
}

void				Graph::addMendiane(int x, int z)
{
  _stones.push_back(new Mendiane(x, z, _sceneManager, _driver));
}

void				Graph::addPhiras(int x, int z)
{
  _stones.push_back(new Phiras(x, z, _sceneManager, _driver));
}

void				Graph::addThystame(int x, int z)
{
  _stones.push_back(new Thystame(x, z, _sceneManager, _driver));
}

void				Graph::addEgg(int x, int z)
{
  _eggs.push_back(new Egg(x, z, _sceneManager, _driver));
}

void				Graph::deleteEgg(int x, int z)
{
  for (auto it = _eggs.begin(); it != _eggs.end(); ++it)
    {
      if ((*it)->getX() == x && (*it)->getZ() == z) {
          (*it)->getMesh()->remove();
        _eggs.erase(it);
        return;
      }
    }
}

void				Graph::addFood(int x, int z)
{
  _foods.push_back(new Food(x, z, _sceneManager, _driver));
}

void				Graph::deleteFood(int x, int z)
{
  for (auto it = _foods.begin(); it != _foods.end(); ++it)
    {
      if ((*it)->getX() == x && (*it)->getZ() == z) {
	(*it)->getMesh()->remove();
        _foods.erase(it);
        return;
      }
    }
}

Map				*Graph::getMap() const
{
  return (_map);
}

irr::IrrlichtDevice		*Graph::getDevice() const
{
  return (_device);
}

irr::video::IVideoDriver	*Graph::getDriver() const
{
  return (_driver);
}

irr::scene::ISceneManager	*Graph::getSceneManager() const
{
  return (_sceneManager);
}

irr::gui::IGUIEnvironment	*Graph::getGUI() const
{
  return (_gui);
}

irr::scene::ICameraSceneNode	*Graph::getCamera() const
{
  return (_camera);
}

Character			*Graph::getCharacter(int pos) const
{
  return (_characters.at(pos));
}

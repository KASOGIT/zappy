/*
** mytcpsocket.c for mytcpsocket in /home/vives_j/PSU_2015_zappy/src/client_graph/untitled
** 
** Made by Julian Vives
** Login   <vives_j@pc-vives_j>
** 
** Started on  Sat Jun 18 16:22:38 2016 Julian Vives
** Last update Sat Jun 18 16:22:43 2016 Julian Vives
*/

#include "mainwindow.h"
#include "qtcharacter.hpp"
#include "qtegg.hpp"
#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(MainWindow *win, QObject *parent)
    : QObject(parent)
{
    _command["pic"] = &MyTcpSocket::startIncantation;
    _command["msz"] = &MyTcpSocket::getSizeMap;
    _command["bct"] = &MyTcpSocket::initMap;
    _command["sst"] = &MyTcpSocket::getTimer;
    _command["pnw"] = &MyTcpSocket::addPlayer;
    _command["enw"] = &MyTcpSocket::createEgg;
    _command["eht"] = &MyTcpSocket::hatchingEgg;
    _command["pdr"] = &MyTcpSocket::throwResource;
    _command["pgt"] = &MyTcpSocket::getResource;
    _command["ppo"] = &MyTcpSocket::movePlayer;
    _command["pdi"] = &MyTcpSocket::playerDeath;
    _command["edi"] = &MyTcpSocket::playerDeath;
    _command["pie"] = &MyTcpSocket::incantationUp;
    _command["pin"] = &MyTcpSocket::showInventory;
    socket = NULL;
    _win = win;
}

void    MyTcpSocket::doConnect(QString ip, QString port, MainWindow *window)
{
    QMessageBox *popup = new QMessageBox;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "connecting...";

    qDebug() << ip;
    socket->connectToHost(ip, port.toInt());

    if (!socket->waitForConnected(5000)) {
        popup->information(window, tr("Zappy"), tr("Connection failed"));
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    popup->information(window, tr("Zappy"), tr("Connection success"));
    socket->write("GRAPHIC\n");
    socket->write("msz\n");
    socket->write("mct\n");
}

QTcpSocket  *MyTcpSocket::getSocket() const
{
    return (socket);
}

void    MyTcpSocket::startIncantation(char *str) {
    std::string s(str + 4);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int             *data = new int[3];
    int             i = 0;

    while ((i <= 4)&& (pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (token[0] != '#')
            data[i] = atoi(token.c_str());
        else
            data[i] = atoi(token.c_str() + 1);
        s.erase(0, pos + delimiter.length());
        i += 1;
    }
    s[strlen(s.c_str())] = '\0';
    _win->updateCommand(str, data[3]);
}

void    MyTcpSocket::playerDeath(char *str) {
    int   id = atoi(str + 5);

    _win->killPlayer(id);
}

void    MyTcpSocket::incantationUp(char *command) {
    std::string s(command + 4);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int             *data = new int[2];
    int             i = 0;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        data[i] = atoi(token.c_str());
        s.erase(0, pos + delimiter.length());
        i += 1;
    }
    s[strlen(s.c_str())] = '\0';
   if (std::stoi(s) == 1) {
        _win->upLvl(data[0], data[1], command);
   }
}

void    MyTcpSocket::movePlayer(char *newPos)
{
    std::string s(newPos + 5);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int             *data = new int[4];
    int             i = 0;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        data[i] = atoi(token.c_str());
        s.erase(0, pos + delimiter.length());
        i += 1;
    }
    s[strlen(s.c_str())] = '\0';
    data[3] = std::stoi(s);
    _win->getCharacterFromId(data[0]).updatePos(data[1], data[2], data[3]);
    _win->getGraph()->moveCharacter(data[0], data[1], data[2], data[3]);
    _win->updateCommand(newPos, data[0]);
}

void    MyTcpSocket::throwResource(char *resource)
{
    std::string info(resource + 5);
    std::string res;
    std::stringstream   input(info);
    int     *infoInt = new int[2];

    while (getline(input, res)) {
        std::string s(res);
        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            infoInt[0] = atoi(token.c_str());
        }
    s[strlen(s.c_str())] = '\0';
    infoInt[1] = atoi(s.c_str());
    }
    _win->getCharacterFromId(infoInt[0]).setResource(infoInt[1],
                                                                             _win->getCharacterFromId(infoInt[0]).getResource(infoInt[1] + 1));
    _win->getResource(infoInt[0] - 1, infoInt[1]);
    _win->getGraph()->addStone(infoInt[1] - 1, _win->getCharacterFromId(infoInt[0]).getX(), _win->getCharacterFromId(infoInt[0]).getZ());
    _win->updateCommand(resource, infoInt[0]);
    _win->showInventoryFromGetOrThrow(infoInt[0]);
}

void    MyTcpSocket::getResource(char *resource)
{
    std::string info(resource + 5);
    std::string res;
    std::stringstream   input(info);
    int     *infoInt = new int[2];

    while (getline(input, res)) {
        std::string s(res);
        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            infoInt[0] = atoi(token.c_str());
        }
    s[strlen(s.c_str())] = '\0';
    infoInt[1] = atoi(s.c_str());
    }
    _win->getCharacterFromId(infoInt[0]).setResource(infoInt[1],
                                                                             _win->getCharacterFromId(infoInt[0]).getResource(infoInt[1] + 1));
    _win->removeResource(infoInt[0] - 1, infoInt[1]);
    _win->getGraph()->deleteStone(infoInt[1] - 1, _win->getCharacterFromId(infoInt[0]).getX(), _win->getCharacterFromId(infoInt[0]).getZ());
    _win->updateCommand(resource, infoInt[0]);
    _win->showInventoryFromGetOrThrow(infoInt[0]);
}

void    MyTcpSocket::createEgg(char *str)
{
    std::string info(str + 5);
    std::string res;
    std::stringstream   input(info);
    int     nb = 0;
    int     *infoInt = new int[4];

    std::string tmpId(str + 5);
    std::string resId;
    for (size_t i = 0; i < tmpId.size() && tmpId[i] != ' '; i += 1) {
        resId += tmpId[i];
    }
    while (getline(input, res)) {
        std::string s(res);
        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            infoInt[nb] = atoi(token.c_str());
            nb += 1;
        }
     s[strlen(s.c_str())] = '\0';
     infoInt[3] = atoi(s.c_str());
    }
    QTEgg     newEgg(infoInt[2], infoInt[3], std::stoi(resId));
    _win->addEgg(newEgg);
    _win->updateCommand(str, infoInt[1] + 1);
}

void    MyTcpSocket::hatchingEgg(char *str)
{
       char *tmp = strdup(str + 5);

       _win->removeEgg(atoi(tmp));
}

void    MyTcpSocket::addPlayer(char *playerInfo)
{
    std::string playerInfoString(playerInfo + 5);
    std::string res;
    std::stringstream   input(playerInfoString);
    int     nb = 0;
    int     *info = new int[6];
    std::string name;

    while (getline(input, res)) {
        std::string s(res);
        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            info[nb] = std::stoi(token);
            nb += 1;
        }
    s[strlen(s.c_str())] = '\0';
    name = s;
    }
    QTCharacter   newCharacter(info[1], info[2], info[3], info[0], name);
    _win->addPlayerToVector(newCharacter);
    _win->addTeam(newCharacter);
    _win->getGraph()->addCharacter(newCharacter.getX(), newCharacter.getZ(), newCharacter.getId());
}

void    MyTcpSocket::writeOnSocket(const char *str, MainWindow *window)
{
    if (socket) {
        socket->write(str);
    }
    else {
        QMessageBox *popup = new QMessageBox;

        popup->information(window, tr("Zappy"), tr("You have to connect before changing time"));
    }
}

void    MyTcpSocket::connected()
{
    qDebug() << "connected...";
}

void    MyTcpSocket::disconnected()
{
    QMessageBox *popup = new QMessageBox;

    popup->information(_win, tr("Zappy"), tr("Disconnected"));
    _win->endGame();
    qDebug() << "Disconnected";
}

void    MyTcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << "Bytes written";
}

void    MyTcpSocket::getSizeMap(char *size)
{
    size[strlen(size)] = '\0';
    char *tmp = new char[strlen(size)];
    size_t i;

    for (i = 4; i < strlen(size) && size[i] != ' '; i += 1) {
        tmp[i - 4] = size[i];
    }
    tmp[i - 4] = '\0';
    _win->setX(atoi(tmp));
    char    *tmpY;
    tmpY = new char[strlen(size)];
    int e = 0;
    for (i = i; i < strlen(size); i += 1) {
        tmpY[e] = size[i];
        e += 1;
    }
    tmpY[e] = '\0';
    _win->setY(atoi(tmpY));
   if (_win->getGraph() == NULL) {
        _win->initIrrlicht();
        _win->setTimerPrint();
    }
}

char    *getCommand(const char *str)
{
    char    *toRet = new char[strlen(str)];

    size_t  i;
    for (i = 0; i < strlen(str) && str[i] != ' '; i += 1) {
        toRet[i] = str[i];
    }
    toRet[i] = '\0';
    return (toRet);
}

void    MyTcpSocket::initMap(char *map)
{
    size_t  size = _win->getX() * _win->getY();
    if (_win->getMap()->size() < size) {
        std::string mapString(map);
        std::string res;
        std::stringstream   input(mapString);

        while (getline(input, res)) {
            std::string s(res);
            std::string delimiter = "{";

            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());
            }
            s[strlen(s.c_str()) - 1] = '\0';

            caseMap *newItem = new caseMap;
            delimiter = ", ";
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                if (token.find("nourriture") != std::string::npos) {
                   newItem->resource[0] = atoi(token.c_str() + 11);
                }
                else if (token.find("linemate") != std::string::npos) {
                    newItem->resource[1] = atoi(token.c_str() + 9);
                }
                else if (token.find("deraumere") != std::string::npos) {
                    newItem->resource[2] = atoi(token.c_str() + 10);
                }
                else if (token.find("sibur") != std::string::npos) {
                    newItem->resource[3] = atoi(token.c_str() + 6);
                }
                else if (token.find("mendiane") != std::string::npos) {
                    newItem->resource[4] = atoi(token.c_str() + 9);
                }
                else if (token.find("phiras") != std::string::npos) {
                    newItem->resource[5] = atoi(token.c_str() + 7);
                }
                s.erase(0, pos + delimiter.length());
            }
            int         x;
            int         z;

            size_t       i = 0;
            std::string after;
            int loop = 0;
            newItem->resource[6] = atoi(s.c_str() + 9);
            while ((i = res.find(" ")) != std::string::npos) {
                after = res.substr(0, i);
                if (loop == 1) {
                    x = atoi(after.c_str());
                }
                else if (loop == 2) {
                    z = atoi(after.c_str());
                }
                res.erase(0, i + 1);
                loop += 1;
            }
            _win->setMapCase(newItem, x, z);
        }
    }
}

void    MyTcpSocket::getTimer(char *time)
{
    qDebug() << time;
}

void    MyTcpSocket::showInventory(char *str) {
    std::map<const char*, int>    info;
    std::string mapString(str);
    std::string res;
    std::stringstream   input(mapString);
    int nb = 1;

    std::string tmpId(str + 5);
    std::string resId;
    for (size_t i = 0; i < tmpId.size() && tmpId[i] != ' '; i += 1) {
        resId += tmpId[i];
    }

    info["Id"] = atoi(resId.c_str());
    while (getline(input, res)) {
        std::string s(res);
        std::string delimiter = "{";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
        }

        delimiter = ",";
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if (token.find("linemate") != std::string::npos) {
                info["Linemate"] = atoi(token.c_str() + 9);
            }
            else if (token.find("deraumere") != std::string::npos) {
                info["Deraumere"] = atoi(token.c_str() + 10);
            }
            else if (token.find("sibur") != std::string::npos) {
                info["Sibur"] = atoi(token.c_str() + 6);
            }
            else if (token.find("mendiane") != std::string::npos) {
                info["Mendiane"] = atoi(token.c_str() + 9);
            }
            else if (token.find("phiras") != std::string::npos) {
                info["Phiras"] = atoi(token.c_str() + 7);
            }
            else if (token.find("thystame") != std::string::npos) {
                info["Thystame"] = atoi(token.c_str() + 9);
            }
            else if (token.find("nourriture") != std::string::npos) {
                info["Nourriture"] = atoi(token.c_str() + 11);
            }
            s.erase(0, pos + delimiter.length());
            nb += 1;
        }
    }

    if (info["Id"] == _win->getCurrentIdSelected()) {
        QStringList listItem;

        listItem << "Nourriture : " << std::to_string(info["Nourriture"]).c_str()
                    << "Linemate : " << std::to_string(info["Linemate"]).c_str()
                    << "Deraumere : " << std::to_string(info["Deraumere"]).c_str()
                    << "Sibur : " << std::to_string(info["Sibur"]).c_str()
                    << "Mendiane : " << std::to_string(info["Mendiane"]).c_str()
                    << "Phiras : " << std::to_string(info["Phiras"]).c_str()
                    << "Thystame : " << std::to_string(info["Thystame"]).c_str();
         _win->setStringList(listItem);
    }
}

void    MyTcpSocket::readyRead()
{
    int     i = 0;

    QByteArray  strRead(socket->readAll());
    char    *str;

    str = new char[strRead.size() + 1];
    for (i = 0; i < strRead.size(); i += 1) {
        str[i] = strRead.at(i);
    }
    str[i] = '\0';
    std::string res;
    std::stringstream input(str);

    while (getline(input, res)) {
        std::string tmp(getCommand(res.c_str()));

        _win->updateLastCommand(res.c_str());
        fctExec exec =  _command[tmp];
        if (exec) {
            char    *final = strdup(res.c_str());
            (this->*exec)(final);
        }
    }
}

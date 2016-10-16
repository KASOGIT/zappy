#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <iostream>

class MainWindow;
class QTCharacter;
class QTEgg;

class MyTcpSocket : public QObject
{
    Q_OBJECT
    typedef void (MyTcpSocket::*fctExec)(char*);
public:
    explicit MyTcpSocket(MainWindow *win, QObject *parent = 0);

    QTcpSocket *getSocket() const;
    void    showInventory(char*);
    void    startIncantation(char*);
    void    incantationUp(char *);
    void    eggDeath(char*);
    void    playerDeath(char*);
    void    movePlayer(char*);
    void    throwResource(char *);
    void    getResource(char *resource);
    void    addPlayer(char *playerInfo);
    void    doConnect(QString, QString, MainWindow*);
    void    getName(char*);
    void    writeOnSocket(const char*, MainWindow*);
    void    getSizeMap(char*);
    void    getPosPlayer(char *player);
    void    getLevelPlayer(char *player);
    void    getInventory(char *player);
    void    getTimer(char *time);
    void    setTimer(char *timer);
    void    initMap(char *);
    void    createEgg(char *);
    void    hatchingEgg(char*);

signals:

public slots:
    void    connected();
    void    disconnected();
    void    bytesWritten(qint64 bytes);
    void    readyRead();

private:
    MainWindow  *_win;
    std::map<std::string, fctExec>    _command;
    QTcpSocket  *socket;
    QString         *_ip;
    QString         *_port;
};

#endif // MYTCPSOCKET_H

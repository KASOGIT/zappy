#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <vector>
#include <QComboBox>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QToolBar>
#include <QListView>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QTimer>
#include "mytcpsocket.h"
#include "Graph.hpp"

class MyThread;
class QTEgg;
class QTCharacter;

enum idResource {
    NOURITURE = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6
};

struct caseMap {
    std::map<int, int>   resource;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow();
    ~MainWindow();

public:
       void    setFocusIrrlicht();
       int       getCurrentIdSelected();
       void    showInventoryFromGetOrThrow(int);
       void    setStringList(QStringList);
       void    createInventoryDock();
       void    updateCommand(char *str, int id);
       void    upLvl(int, int, char*);
       QTCharacter  getCharacterFromId(int) const;
       void    endGame();
       void    updateLastCommand(const char *);
       void    setTimerPrint();
       void    getResource(int idPerso, int idResource);
       void    removeResource(int idPerso, int idResource);
       void    killEgg(int);
       void    killPlayer(int id);
       void    addEgg(QTEgg);
       void    removeEgg(int);
       void    setMapCase(caseMap*, int, int);
       void    setY(int);
       void    setX(int);
       int       getX() const;
       int       getY() const;
       std::vector<QTCharacter>  *getCharacterList() const;
       std::vector<QTEgg>  *getEggList() const;
       std::vector<caseMap*> *getMap() const;
       void    setTeamName(QString*);
       QString  *getTeamName() const;
       void         addPlayerToVector(QTCharacter);
       void    addTeam(QTCharacter);
       Graph    *getGraph() const;
       void    initIrrlicht();

public slots:
       void    showInventory(int);

private slots:
    void    printIrrlicht();
    void    connectToAdress();
    void    setTime();


private:
    void    configureGeometry();
    void    createToolBar();
    void    createActions();
    void    createIcons();
    void    createDockTools();

private:
    QDockWidget *inventoryDock;
    QStringListModel        *model;
    QListView          *viewInventory;
    QLineEdit          *lastCommand;
    QDockWidget    *screenGame;
    QTimer              *timerPrint;
    MyThread         *thread;
    MyThread         *thread2;
    QMessageBox  *popup;
    QHBoxLayout    *layout;
    MyTcpSocket     *socket;
    QWidget            *irrlichtScreen;
    QLineEdit          *ip;
    QLineEdit          *port;
    QLineEdit          *time;
    QPushButton    *addButton;
    QPushButton     *okButton;
    QPushButton     *okTime;
    QWidget            *screen;
    QDockWidget    *dockTools;
    QStringList        horizontalHeader;
    QTableWidget   *table;
    QStringList        tableHeader;
    QToolBar          *fileToolBar;
    QIcon               exitIcon;
    QComboBox   *boxPlayer;
    std::vector<QTCharacter>  *_characterList;
    std::vector<QTEgg>            *_eggList;
    int                     _x;
    int                     _y;
    int                     currentIdSelected;
    std::vector<std::string>  *_name;
    std::vector<caseMap*>   *_map;
    Graph                               *irrlichtGraph;
    QString                             *teamName;
};

#endif // MAINWINDOW_H

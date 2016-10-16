#include "mainwindow.h"
#include "qtcharacter.hpp"
#include "qtegg.hpp"
#include "mythread.h"

MainWindow::MainWindow()
{
    setWindowTitle("Zappy");
    configureGeometry();
    irrlichtGraph = NULL;
    lastCommand = new QLineEdit;
    _characterList = new std::vector<QTCharacter>;
    screenGame = new QDockWidget;
    _eggList = new std::vector<QTEgg>;
    popup = new QMessageBox;
    socket = new MyTcpSocket(this, this);
    _name = new std::vector<std::string>;
    _map = new std::vector<caseMap*>;
    timerPrint = new QTimer(this);
    timerPrint->setInterval(500);

    currentIdSelected = 0;
    lastCommand->setReadOnly(true);
    screen = irrlichtGraph;
    setCentralWidget(screenGame);
    createInventoryDock();
    createActions();
    createIcons();
    createToolBar();
    createDockTools();
 }

MainWindow::~MainWindow()
{

}

void    MainWindow::printIrrlicht()
{
    irrlichtGraph->print();
    timerPrint->start();
}

void    MainWindow::endGame() {
    irrlichtGraph = NULL;
    timerPrint->stop();
    socket->disconnect();
    this->close();
}

void    MainWindow::updateLastCommand(const char *command)
{
    lastCommand->setText(QString(command));
}

void    MainWindow::killEgg(int id)
{
    int i = 0;
    for (std::vector<QTEgg>::iterator it = _eggList->begin(); it < _eggList->end(); ++it) {
        if (id == i) {
            _eggList->erase(it);
        }
        i += 1;
    }
}

void        MainWindow::setTimerPrint() {
    timerPrint->start();
}

Graph   *MainWindow::getGraph() const {
    return (irrlichtGraph);
}

void    MainWindow::initIrrlicht()
{
    irrlichtGraph = new Graph(_x, _y, screenGame);
}

void    MainWindow::killPlayer(int id)
{
    for (std::vector<QTCharacter>::iterator it = _characterList->begin(); it < _characterList->end(); ++it) {
        if (id == (*it).getId()) {
            QTableWidgetItem *lvlItem = new QTableWidgetItem("DEAD");
            table->setItem((*it).getId() - 1, 2, lvlItem);
            boxPlayer->removeItem(id - 1);
            _characterList->erase(it);
            irrlichtGraph->deleteCharacter(id);
            return ;
        }
    }
}

void    MainWindow::updateCommand(char *str, int id) {

    QTableWidgetItem *updateLine = new QTableWidgetItem(str);

    table->setItem(id - 1, 3, updateLine);
}

void    MainWindow::getResource(int idPerso, int idResource)
{
    int     xPerso = getCharacterFromId(idPerso).getX();
    int     zPerso = getCharacterFromId(idPerso).getZ();

    _map->at(xPerso + zPerso * (_x + 1))->resource[idResource] += 1;
}

void    MainWindow::removeResource(int idPerso, int idResource)
{
    int     xPerso = getCharacterFromId(idPerso).getX();
    int     zPerso = getCharacterFromId(idPerso).getZ();

    _map->at(xPerso + zPerso * _x)->resource[idResource] -= 1;
}

void    MainWindow::setStringList(QStringList listItem) {
    model->setStringList(listItem);
    viewInventory->setModel(model);
}

int       MainWindow::getCurrentIdSelected() {
    return (currentIdSelected);
}

void    MainWindow::showInventoryFromGetOrThrow(int id)
{
        std::string toWrite("pin #" + std::to_string(id) + "\n");
        socket->writeOnSocket(toWrite.c_str(), this);
}

void    MainWindow::showInventory(int id)
{
       currentIdSelected = id + 1;
       for (int i = 0; model->rowCount() > i; i += 1) {
             model->removeRows(i, 1);
        }
        std::string toWrite("pin #" + std::to_string(id + 1) + "\n");
        socket->writeOnSocket(toWrite.c_str(), this);
}

std::vector<QTCharacter>  *MainWindow::getCharacterList() const
{
    return (_characterList);
}

QTCharacter             MainWindow::getCharacterFromId(int id) const {
    for (auto it = _characterList->begin(); it != _characterList->end(); ++it) {
        if ((*it).getId() == id) {
            return (*it);
        }
    }
    return (_characterList->at(0));
}

std::vector<QTEgg>  *MainWindow::getEggList() const
{
    return (_eggList);
}

void    MainWindow::connectToAdress()
{
    if (ip->displayText().isEmpty() == false
            && ip->hasAcceptableInput() == true
            && port->displayText().isEmpty() == false) {
        if (socket && socket->getSocket() && socket->getSocket()->isOpen() == true)
            popup->information(this, tr("Zappy"), tr("You are already connected"));
        else
             socket->doConnect(ip->displayText(), port->displayText(), this);
    }
    else {
        popup->information(this, tr("Zappy"), tr("Please fill the IP and the Port before trying to connect"));
    }
}

void    MainWindow::upLvl(int x, int z, char *command) {
    for (auto it = _characterList->begin(); it != _characterList->end(); ++it) {
        if ((*it).getX() == x && (*it).getZ() == z) {
            (*it).updateLvl();
            QTableWidgetItem *lvlItem = new QTableWidgetItem(QString::number((*it).getLvl()));
            QTableWidgetItem *commandItem = new QTableWidgetItem(QString(command));


            table->setItem((*it).getId() - 1, 2, lvlItem);
            table->setItem((*it).getId() - 1, 3, commandItem);
          }
     }
}
void    MainWindow::addEgg(QTEgg newEgg)
{
    _eggList->push_back(newEgg);
    irrlichtGraph->addEgg(newEgg.getX(), newEgg.getZ());
}

void    MainWindow::removeEgg(int id)
{
    for (std::vector<QTEgg>::iterator it = _eggList->begin(); it != _eggList->end(); ++it) {
        if (id == (*it).getId()) {
            irrlichtGraph->deleteEgg((*it).getX(), (*it).getZ());
            _eggList->erase(it);
            return;
        }
    }
}

void    MainWindow::setY(int y)
{
    _y = y;
}

void    MainWindow::setX(int x)
{
    _x = x;
}

void    MainWindow::setFocusIrrlicht() {

}

void    MainWindow::setMapCase(caseMap *newCase, int x, int y)
{
    _map->push_back(newCase);
    for (int i = 0; i < newCase->resource[1]; i += 1) {
        irrlichtGraph->addLinemate(x, y);
    }
    for (int i = 0; i < newCase->resource[2]; i += 1) {
        irrlichtGraph->addDeraumere(x, y);
    }
    for (int i = 0; i < newCase->resource[3]; i += 1) {
        irrlichtGraph->addSibur(x, y);
    }
    for (int i = 0; i < newCase->resource[4]; i += 1) {
        irrlichtGraph->addMendiane(x, y);
    }
    for (int i = 0; i < newCase->resource[5]; i += 1) {
        irrlichtGraph->addPhiras(x, y);
    }
    for (int i = 0; i < newCase->resource[6]; i += 1) {
        irrlichtGraph->addThystame(x, y);
    }
    for (int i = 0; i < newCase->resource[0]; i += 1) {
        irrlichtGraph->addFood(x, y);
    }
}

void    MainWindow::setTeamName(QString *newTeamName)
{
    teamName = newTeamName;
}

void         MainWindow::addPlayerToVector(QTCharacter newCharact)
{
    _characterList->push_back(newCharact);
}

QString *MainWindow::getTeamName() const
{
    return (teamName);
}

std::vector<caseMap*>    *MainWindow::getMap() const
{
    return (_map);
}

int       MainWindow::getY() const
{
    return (_y);
}

int       MainWindow::getX() const
{
    return (_x);
}

bool    isDigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

void    MainWindow::setTime()
{
    if (socket && time->displayText().isEmpty() == false && isDigits(time->displayText().toStdString())) {
       char    *tmp = new char;
       size_t         i;

       tmp[0] = 's';
       tmp[1] = 's';
       tmp[2] = 't';
       tmp[3] = ' ';
       for (i = 4; i < time->displayText().toStdString().size() + 4; i += 1) {
          tmp[i] = time->displayText().toStdString().c_str()[i - 4];
        }
      tmp[i] = '\n';
      tmp[i + 1] = '\0';
      QByteArray     test(tmp);
      socket->writeOnSocket(test.toStdString().c_str(), this);
    }
    else {
        popup->information(this, tr("Zappy"), tr("Fill correctly the Ip"));
    }
}

void    MainWindow::addTeam(QTCharacter newCharact)
{
      QString   teamNumber = QString::number(newCharact.getId());
      QString   lvl = QString::number(newCharact.getLvl());
      QTableWidgetItem *teamNumberItem = new QTableWidgetItem(teamNumber.toStdString().c_str());
      QTableWidgetItem *teamNameItem = new QTableWidgetItem(newCharact.getTeamName().c_str());
      QTableWidgetItem *lvlItem = new QTableWidgetItem(lvl);

      table->setItem(newCharact.getId() - 1, 0, teamNumberItem);
      table->setItem(newCharact.getId() - 1, 1, teamNameItem);
      table->setItem(newCharact.getId() - 1, 2, lvlItem);

      QString   layer = QString("Player ");
      layer += QString::number(newCharact.getId());
      boxPlayer->addItem(layer);
      if (currentIdSelected == 0) {
          currentIdSelected = 1;
      }
}

void    MainWindow::createActions()
{
    ip = new QLineEdit();
    port = new QLineEdit();
    time = new QLineEdit();
    okButton = new QPushButton(tr("Connect"));
    okTime = new QPushButton(tr("Change time"));

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(connectToAdress()));
    connect(okTime, SIGNAL(clicked(bool)), this, SLOT(setTime()));
    connect(timerPrint, SIGNAL(timeout()), this, SLOT(printIrrlicht()));
    connect(boxPlayer, SIGNAL(currentIndexChanged(int)), this, SLOT(showInventory(int)));
}

void    MainWindow::configureGeometry()
{
    QDesktopWidget  *deskWidget;
    int widthScreen, heightScreen;

    deskWidget = QApplication::desktop();
    widthScreen = deskWidget->width();
    heightScreen = deskWidget->height();
    resize(widthScreen, heightScreen);
    move(0, 0);
}

void    MainWindow::createIcons()
{
}

void    MainWindow::createToolBar()
{
    QSize   iconSize(35, 35);

    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setIconSize(iconSize);
    fileToolBar->addWidget(ip);
    fileToolBar->addWidget(port);
    fileToolBar->addWidget(okButton);
    fileToolBar->addWidget(time);
    fileToolBar->addWidget(okTime);
}

void    MainWindow::createInventoryDock() {
    inventoryDock = new QDockWidget;

    inventoryDock = new QDockWidget(tr("List player"), this);
    inventoryDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    inventoryDock->setFeatures(QDockWidget::DockWidgetMovable);
    inventoryDock->setWindowTitle(tr("List player"));

    QHBoxLayout  *layoutInventory = new QHBoxLayout();

    layoutInventory->addWidget(inventoryDock);

    boxPlayer = new QComboBox(inventoryDock);
    viewInventory = new QListView();
    model = new QStringListModel(viewInventory);

    boxPlayer->setMinimumWidth(470);
    inventoryDock->setMinimumWidth(470);
    inventoryDock->setWidget(viewInventory);
}

void    MainWindow::createDockTools()
{
    QDockWidget *dockCommand = new QDockWidget;
    QWidget         *tmpWidget = new QWidget;
    QWidget         *tmpWidgetCommand = new QWidget;
    table =             new QTableWidget(1024, 4);

    tableHeader << "ID" << "Team" << "Level" << "Command";
    table->setVerticalHeaderLabels(horizontalHeader);
    table->setHorizontalHeaderLabels(tableHeader);
    table->setStyleSheet("QTableView {selection-background-color: red;}");
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    dockTools = new QDockWidget(tr("Graph actions"), this);
    dockTools->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockTools->setFeatures(QDockWidget::DockWidgetMovable);


    dockCommand = new QDockWidget(tr("Last command"), this);
    dockCommand->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockCommand->setFeatures(QDockWidget::DockWidgetMovable);
    dockCommand->setWindowTitle(tr("Last command"));

    QHBoxLayout  *layoutCommand = new QHBoxLayout();
    QVBoxLayout  *layoutDock = new QVBoxLayout();

    layoutDock->addWidget(table);
    layoutCommand->addWidget(lastCommand);
    tmpWidget->setLayout(layoutDock);
    tmpWidgetCommand->setLayout(layoutCommand);
    dockTools->setWidget(tmpWidget);
    dockCommand->setWidget(tmpWidgetCommand);
    addDockWidget(Qt::LeftDockWidgetArea, dockCommand);
    addDockWidget(Qt::LeftDockWidgetArea, dockTools);
    addDockWidget(Qt::LeftDockWidgetArea, inventoryDock);
    dockTools->setMinimumWidth(470);
    dockTools->setMaximumHeight(700);
    dockCommand->setMaximumHeight(100);
}

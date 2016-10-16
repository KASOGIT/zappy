#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T16:34:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTZappy
TEMPLATE = app


SOURCES += main.cpp\
                        mainwindow.cpp \
                        mytcpsocket.cpp \
                        Graph/Graph.cpp \
                        Map/Map.cpp \
                        Character/Character.cpp \
                        Stones/Sibur/Sibur.cpp \
                        Stones/Linemate/Linemate.cpp \
                        Stones/Deraumere/Deraumere.cpp \
                        Stones/Mendiane/Mendiane.cpp \
                        Stones/Phiras/Phiras.cpp \
                        Stones/Thystame/Thystame.cpp \
                        Egg/Egg.cpp \
                        Food/Food.cpp \


HEADERS  += mainwindow.h \
                        mytcpsocket.h \
                        Graph/Graph.hpp \
                        Map/Map.hpp \
                        Character/Character.hpp \
                        Stones/IStone/IStone.hpp \
                        Stones/Sibur/Sibur.hpp \
                        Stones/Linemate/Linemate.hpp \
                        Stones/Deraumere/Deraumere.hpp \
                        Stones/Mendiane/Mendiane.hpp \
                        Stones/Phiras/Phiras.hpp \
                        Stones/Thystame/Thystame.hpp \
                        Egg/Egg.hpp \
                        Food/Food.hpp \
    qtcharacter.hpp \
    qtegg.hpp


INCLUDEPATH +=  ../../../lib/irrlicht-1.8.3/include/
INCLUDEPATH += Map/
INCLUDEPATH += Graph/
INCLUDEPATH += Character/
INCLUDEPATH += Stones/Sibur/
INCLUDEPATH += Stones/Linemate/
INCLUDEPATH += Stones/Deraumere/
INCLUDEPATH += Stones/Mendiane/
INCLUDEPATH += Stones/Phiras/
INCLUDEPATH += Stones/Thystame/
INCLUDEPATH += Food/
INCLUDEPATH += Stones/IStone/
INCLUDEPATH += Egg/
INCLUDEPATH += ../../../lib/irrlicht-1.8.3/
INCLUDEPATH += ../../../lib/irrlicht-1.8.3/lib/Linux/

LIBS += -L../../../lib/irrlicht-1.8.3/lib/Linux/ -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor

QT       += core
QT       += network
QT       -= gui

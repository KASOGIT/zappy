#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include "Graph.hpp"

class Graph;
class MainWindow;

class MyThread : QThread
{
    Q_OBJECT

public:
    MyThread();
    void    run(Graph*);
    void    run(MainWindow*);
protected:
};

#endif // MYTHREAD_H

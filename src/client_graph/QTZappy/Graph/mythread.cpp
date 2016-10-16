#include "mythread.h"
#include "mainwindow.h"
 #include "Graph.hpp"

MyThread::MyThread()
{

}

void   MyThread::run(Graph *graph)
{
    qDebug() << "JE PASSE PAR LA";
    graph->print();
}

void    MyThread::run(MainWindow *w) {
    w->show();
}

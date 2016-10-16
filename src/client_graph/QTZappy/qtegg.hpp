#ifndef QTEGG_HPP
#define QTEGG_HPP

#include "mainwindow.h"

class QTEgg {
public:
    QTEgg(int x, int z, int id) {
        _x = x;
        _z = z;
        _id = id;
    }

    ~QTEgg() {}
    int getX() const {
        return _x;
    }
    int getZ() const {
        return _z;
    }
    int getId() const {
        return (_id);
    }
private:
    int     _id;
    int     _x;
    int     _z;
};

#endif // QTEGG_HPP

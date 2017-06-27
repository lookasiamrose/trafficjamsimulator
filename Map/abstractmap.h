#ifndef ABSTRACTMAP_H
#define ABSTRACTMAP_H

#include "types.h"
#include <QWidget>

class AbstractMap : public QWidget
{
public:
    virtual void drawWays(QList<Street> ways) = 0;
    virtual void drawNodes(QList<Crossing> nodes) = 0;
    virtual void drawCars(QList<Car> cars) = 0;
    virtual void drawAll() = 0;
    virtual void refresh() = 0;

signals:

public slots:
};

#endif // ABSTRACTMAP_H

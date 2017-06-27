#ifndef ABSTRACTTRAFFIC_H
#define ABSTRACTTRAFFIC_H

#include "types.h"
#include <QObject>

class AbstractTraffic : public QObject
{
public:
    virtual void addWays(QList<Street>) = 0;
    virtual void addNodes(QList<Crossing>) = 0;
    virtual void addCars(QList<Car>) = 0;
    virtual void startSimulation() = 0;
    virtual void stopSimulation() = 0;
    virtual void pauseSimulation() = 0;

signals:

public slots:
};

#endif // ABSTRACTTRAFFIC_H

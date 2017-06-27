#ifndef MAP_H
#define MAP_H

#include "abstractmap.h"
#include <QWidget>

class Map : public AbstractMap
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = 0);
    void drawWays(QList<Street> ways);
    void drawNodes(QList<Crossing> nodes);
    void drawCars(QList<Car> cars);
    void drawAll();
    void refresh();
private:
    QList<Street> ways;
    QList<Crossing> nodes;
    QList<Car> cars;
signals:
    void sgnNodeClick(int iNodeId);
    void sgnWayClick(int iWayId);
public slots:
    void slReloadMap();
};

#endif // MAP_H

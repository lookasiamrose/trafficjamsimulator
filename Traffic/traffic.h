#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "abstracttraffic.h"
#include "types.h"
#include <QObject>

enum class SimulationStatus{
    Stopped = 0,
    Running = 1,
    Finished = 2,
};

class Traffic : AbstractTraffic
{
    Q_OBJECT
public:
    explicit Traffic();
    void addWays(QList<Street>);
    void addNodes(QList<Crossing>);
    void addCars(QList<Car>);
    void startSimulation();
    void stopSimulation();
    void pauseSimulation();

private:
    SimulationStatus status;
    QList<Crossing> nodes;
    QList<Car> cars;
    QList<Street> ways;

signals:
    void sgnSimulationFinished();
    void sgnSimulationStarted();
    void sgnSimulationPaused();
public slots:
};

#endif // TRAFFIC_H

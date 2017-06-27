#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QVariant>

struct Street{
    int gid;
    int classId;
    double length;
    QString name;
    double startX;
    double startY;
    double endX;
    double endY;
    double reverse_cost;
    int maxSpeedForward;
    int maxSpeedBackWard;
    int sourceId;
    int targetId;
};

struct Crossing{
    int nodeId;
    double lon;
    double lat;
    int numofuse;
    QList<Street*> directions;
};

struct Car{
    Street* actualStreet;
    double position;
};

struct PathElement{

};

struct NodeSettings{

};

enum class Configration{

};

struct ConfigElem{
    int paramId;
    QVariant value;
};


/* Nowe struktory */
enum class LightStatus{
    Red = 0,
    Green = 1
};

struct RuleLightStruct{
    int streetId; /**< ID ulicy */
    int value; /**< Wartość w sekundach - długość */
    int order; /**< Kolejność wpisów */
    LightStatus light; /**< Typ światła */
};

struct RuleStruct{
    int streetId; /**< ID ulicy */
    int order; /**< Kolejność przejazdu */
};

struct StreetStruct{
    int streetId; /**< ID drogi */
    qreal length; /**< Długość drogi */
    unsigned int maxSpeed; /**< Maksymalna prędkość */
    QString name; /**< Nazwa drogi */
    qreal startX; /**< Punkt X startowy */
    qreal startY; /**< Punkt Y startowy */
    qreal endX; /**< Punkt X końcowy */
    qreal endY; /**< Punkt Y końcowy */
    int lanes; /**< Ilość pasów */
    int prevCrossing; /**< ID poprzedniego skrzyżowania */
    int nextCrossing; /**< ID następnego skrzyżowania */
};

struct CrossingStruct{
    int crossingId; /**< ID Skrzyżowania */
    QList<int> streetId; /**< Lista dróg dołączonyhch do skrzyżowania - w kolejności wskazówek zegara */
    QList<RuleLightStruct> lightsRules; /**< Lista reguł świateł */
    QList<RuleStruct> orderRules; /**< Lista reguł kolejności */

};




#endif // TYPES_H

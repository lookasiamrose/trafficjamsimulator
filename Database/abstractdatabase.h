#ifndef ABSTRACTDATABASE_H
#define ABSTRACTDATABASE_H

#include "types.h"

#include <QObject>
#include <QList>

class AbstractDatabase : public QObject
{
    Q_OBJECT
public:
    virtual QList<StreetStruct> getAllWays() = 0;
    virtual QList<CrossingStruct> getAllNodes() = 0;

    virtual QList<int> getPath(int sourceId, int destId) = 0;
    virtual QList<int> getPath() = 0;

    virtual QList<RuleLightStruct> getLightRules(int crossingId) = 0;
    virtual QList<RuleStruct> getRules(int crossingId) = 0;

    virtual bool saveLightRule(QList<RuleLightStruct> & lightRules, int crossingId) = 0;
    virtual bool saveOrderRule(QList<RuleStruct> & rules, int crossingId) = 0;

protected:
    virtual bool openConnection() = 0;
};

#endif // ABSTRACTDATABASE_H

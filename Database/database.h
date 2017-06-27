#ifndef DATABASE_H
#define DATABASE_H

#include "abstractdatabase.h"

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>



class Database : public AbstractDatabase
{
    Q_OBJECT
public:
    explicit Database(QString sDbType, QString sIP, QString sDbName, QString sDbUser, QString sDbPass, int iDbPort);
    QList<StreetStruct> getAllWays();
    QList<CrossingStruct> getAllNodes();

    QList<int> getPath(int sourceId, int destId);
    QList<int> getPath();

    QList<RuleLightStruct> getLightRules(int crossingId);
    QList<RuleStruct> getRules(int crossingId);

    bool saveLightRule(QList<RuleLightStruct> & lightRules, int crossingId);
    bool saveOrderRule(QList<RuleStruct> & rules, int crossingId);
private:
    bool getConnectionStatus();
    bool openConnection();
    QString sDatabaseHost;
    QString sDatabaseName;
    QString sDatabaseUser;
    QString sDatabasePass;
    QSqlDatabase db;
    int iDatabasePort;
signals:

public slots:
};

#endif // DATABASE_H

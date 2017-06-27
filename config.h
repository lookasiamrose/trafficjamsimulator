#ifndef CONFIG_H
#define CONFIG_H

#include "database.h"
#include <QObject>

class Config : public QObject
{
    Q_OBJECT
public:
    Database * getDbConnection();
    static Config & getSingleton()
    {
        static Config singleton;
        return singleton;
    }
private:
    Config();
    Config(const Config&);
    Database *db;


};

#endif // CONFIG_H

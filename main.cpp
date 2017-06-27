#include "mainwindow.h"
#include <QApplication>

#include "database.h"
#include "editor.h"
#include "map.h"
#include "traffic.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor editor;
    Map map;
    Traffic traf;

    Config::getSingleton();
    Config::getSingleton().getDbConnection();

    QList<StreetStruct> test = Config::getSingleton().getDbConnection()->getAllWays();
    QList<CrossingStruct> test2 = Config::getSingleton().getDbConnection()->getAllNodes();

    QList<RuleLightStruct> abc = test2.at(1).lightsRules;

    Config::getSingleton().getDbConnection()->saveLightRule(abc, 2);

    QList<RuleStruct> tmp;
    tmp = test2.at(2).orderRules;

    Config::getSingleton().getDbConnection()->saveOrderRule(tmp, 3);

    MainWindow w;
    w.show();

    return a.exec();
}

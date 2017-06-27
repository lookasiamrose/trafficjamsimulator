#include "database.h"

Database::Database(QString sDbType, QString sIP, QString sDbName, QString sDbUser, QString sDbPass, int iDbPort)
{
    db = QSqlDatabase::addDatabase(sDbType);
    db.setHostName(sIP);
    db.setDatabaseName(sDbName);
    db.setUserName(sDbUser);
    db.setPassword(sDbPass);
    db.setPort(iDbPort);
}

/**
 * @brief Database::openConnection
 * @return
 */
bool Database::openConnection(){
    if(getConnectionStatus()){
        return true;
    }
    else{
        db.open();
        if(getConnectionStatus()){
            return true;
        }
        else{
            return false;
        }
    }
}

/**
 * @brief Database::getConnectionStatus
 * @return
 */
bool Database::getConnectionStatus(){
    if(db.isOpen()){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Pobieranie wszystkich dróg z bazy danych
 * @brief Database::getAllWays
 * @return
 */
QList<StreetStruct> Database::getAllWays(){
    QList<StreetStruct> streetList;
    if(openConnection()){
        QSqlQuery query(db);
        query.prepare("SELECT gid, class_id, length, name, x1, y1, x2, y2, maxspeed_forward, source, target, lanes FROM public.ways");
        if(query.exec()){
            StreetStruct tmp;
            while(query.next()){
                tmp.streetId = query.value("gid").toInt();
                tmp.length = query.value("length").toReal();
                tmp.name = query.value("name").toString();
                tmp.startX = query.value("x1").toReal();
                tmp.startY = query.value("y1").toReal();
                tmp.endX = query.value("x2").toReal();
                tmp.endY = query.value("y2").toReal();
                tmp.maxSpeed = query.value("maxspeed_forward").toInt();
                tmp.prevCrossing = query.value("source").toInt();
                tmp.nextCrossing = query.value("target").toInt();
                tmp.lanes = query.value("lanes").toInt();
                streetList.append(tmp);
            }
        }
        else{
            QString funcName = __FUNCTION__;
            qCritical() << funcName << query.lastError().text();
        }
    }
    return streetList;
}

/**
 * Pobieranie wszystkich węzłów z bazy danych
 * @brief Database::getAllNodes
 * @return
 */
QList<CrossingStruct> Database::getAllNodes(){
    QList<CrossingStruct> crossingList;
    if(openConnection()){
        QSqlQuery query(db);
        query.prepare("SELECT crossing_id, string_agg(id::text, ',') as ids FROM ( \
                      ( \
                       SELECT source as crossing_id, gid as id, x1,y1,x2,y2 FROM ways \
                      ) \
                      UNION \
                      ( \
                       SELECT target as crossing_id ,gid as id, x1,y1,x2,y2 FROM ways \
                      ) \
                       ORDER BY crossing_id, id \
                   ) query1 \
                   GROUP BY crossing_id");
        if(query.exec()){
            CrossingStruct tmp;
            while(query.next()){
                tmp.crossingId = query.value("crossing_id").toInt();
                QStringList tmpList = query.value("ids").toString().split(",");
                foreach(QString str, tmpList){
                    int strToInt = str.toInt();
                    tmp.streetId.append(strToInt);
                }
                tmp.lightsRules = getLightRules(tmp.crossingId);
                tmp.orderRules = getRules(tmp.crossingId);

                crossingList.append(tmp);
                tmp.streetId.clear();
            }
        }
        else{
            QString funcName = __FUNCTION__;
            qCritical() << funcName << query.lastError().text();
        }
    }
    return crossingList;
}

QList<int> Database::getPath(int sourceId, int destId){
    Q_UNUSED(sourceId);
    Q_UNUSED(destId);
    QList<int> tmp;
    return tmp;
}

QList<int> Database::getPath(){
    QList<int> tmp;
    return tmp;
}

/**
 * Pobieranie ustawień świateł dla skrzyżowania
 * @brief Database::getLightRules
 * @param crossingId
 * @return
 */
QList<RuleLightStruct> Database::getLightRules(int crossingId){
    QList<RuleLightStruct> tmp;
    if(openConnection()){
        QSqlQuery query(db);
        query.prepare("SELECT street_id, value, type, order_time FROM lights WHERE crossing_id = :crossing_id ORDER BY street_id, order_time");
        query.bindValue(":crossing_id", crossingId);
        if(query.exec()){
            if(query.size() > 0){
                RuleLightStruct tmpStruct;
                while(query.next()){
                    tmpStruct.streetId = query.value("street_id").toInt();
                    tmpStruct.value = query.value("value").toInt();
                    tmpStruct.light = query.value("type").toInt() == 1 ? LightStatus::Green : LightStatus::Red;
                    tmpStruct.order = query.value("order_time").toInt();
                    tmp.append(tmpStruct);
                }
            }
        }
        else{
            QString funcName = __FUNCTION__;
            qCritical() << funcName << query.lastError().text();
        }
    }

    return tmp;
}

/**
 * Pobieranie kolejności przejazdu dla skrzyżowania
 * @brief Database::getRules
 * @param crossingId
 * @return
 */

QList<RuleStruct> Database::getRules(int crossingId){
    QList<RuleStruct> tmpList;
    if(openConnection()){
        QSqlQuery query(db);
        query.prepare("SELECT street_id, order_of FROM crossing_order WHERE crossing_id = :crossing_id");
        query.bindValue(":crossing_id", crossingId);
        if(query.exec()){
            if(query.size() > 0 ){
                RuleStruct tmp;
                while(query.next()){
                    tmp.streetId = query.value("street_id").toInt();
                    tmp.order = query.value("order_of").toInt();
                    tmpList.append(tmp);
                }
            }
        }
        else{
            QString funcName = __FUNCTION__;
            qCritical() << funcName << query.lastError().text();
        }

    }
    return tmpList;
}

/**
 * @brief Database::saveLightRule
 * @param lightRules
 * @param crossingId
 * @return
 */
bool Database::saveLightRule(QList<RuleLightStruct> &lightRules, int crossingId){
    QString funcName = __FUNCTION__;
    if(openConnection()){
        if(db.transaction()){
            QSqlQuery deleteQuery(db);
            deleteQuery.prepare("DELETE FROM lights WHERE crossing_id = :crossing_id");
            deleteQuery.bindValue(":crossing_id", crossingId);
            if(deleteQuery.exec()){
                QSqlQuery insertQuery(db);
                insertQuery.prepare("INSERT INTO lights( \
                                        crossing_id, street_id, value, type, order_time) \
                                VALUES (:crossing_id, :street_id, :value, :type, :order_time)");
                insertQuery.bindValue(":crossing_id", crossingId);
                foreach(RuleLightStruct tmp, lightRules){
                    insertQuery.bindValue(":street_id", tmp.streetId);
                    insertQuery.bindValue(":value", tmp.value);
                    insertQuery.bindValue(":type", tmp.light == LightStatus::Red ? 0 : 1);
                    insertQuery.bindValue(":order_time", tmp.order);
                    if(!insertQuery.exec()){
                        qCritical() << funcName << insertQuery.lastError().text();
                        if(!db.rollback()){
                            qCritical() << funcName << db.lastError().text();
                        }
                        break;
                    }
                }
                if(!db.commit()){
                    qCritical() << funcName << db.lastError().text();
                }
                return true;
            }
            else{
                qCritical() << funcName << deleteQuery.lastError().text();
            }
        }
        else{
            qCritical() << funcName << db.lastError().text();
        }
    }
    return false;
}

/**
 * @brief Database::saveOrderRule
 * @param rules
 * @param crossingId
 * @return
 */
bool Database::saveOrderRule(QList<RuleStruct> &rules, int crossingId){
    QString funcName = __FUNCTION__;
    if(openConnection()){
        if(db.transaction()){
            QSqlQuery deleteQuery(db);
            deleteQuery.prepare("DELETE FROM crossing_order WHERE crossing_id = :crossing_id");
            deleteQuery.bindValue(":crossing_id", crossingId);
            if(deleteQuery.exec()){
                QSqlQuery insertQuery(db);
                insertQuery.prepare("INSERT INTO crossing_order( \
                                        crossing_id, street_id, order_of) \
                                VALUES (:crossing_id, :street_id, :order_of)");
                insertQuery.bindValue(":crossing_id", crossingId);
                foreach(RuleStruct tmp, rules){
                    insertQuery.bindValue(":street_id", tmp.streetId);
                    insertQuery.bindValue(":order_of", tmp.order);
                    if(!insertQuery.exec()){
                        qCritical() << funcName << insertQuery.lastError().text();
                        if(!db.rollback()){
                            qCritical() << funcName << db.lastError().text();
                        }
                        break;
                    }
                }
                if(!db.commit()){
                    qCritical() << funcName << db.lastError().text();
                }
                return true;
            }
            else{
                qCritical() << funcName << deleteQuery.lastError().text();
            }
        }
        else{
            qCritical() << funcName << db.lastError().text();
        }
    }
    return false;
}

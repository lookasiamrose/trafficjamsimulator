#include "config.h"

Config::Config(){
    db = new Database("QPSQL", "192.168.1.249", "routing", "postgres", "postgres", 5432);
}

Database * Config::getDbConnection(){
    return db;
}

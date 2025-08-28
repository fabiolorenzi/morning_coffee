#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class DatabaseManager {
    public:
        static DatabaseManager& instance();
        bool addSource(QString name, QString url, QString type);
    
    private:
        DatabaseManager();
        QSqlDatabase db;
};
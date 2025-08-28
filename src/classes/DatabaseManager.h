#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QVariantMap>
#include <QVector>

class DatabaseManager {
    public:
        static DatabaseManager& instance();
        bool addSource(QString name, QString url, QString type);
        QVector<QVariantMap> getAllSources();
        QVariantMap getSourceById(int id);
        bool updateSource(int id, QString name, QString url, QString type);
        bool removeSource(int id);
    
    private:
        DatabaseManager();
        QSqlDatabase db;
};
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

#include "types/Content.h"
#include "types/Source.h"

class DatabaseManager {
    public:
        static DatabaseManager& instance();
        bool addSource(QString name, QString url, QString type);
        QVector<QVariantMap> getAllSources();
        QVariantMap getSourceById(int id);
        QList<Source> getSourcesByType(QString type);
        bool updateSource(int id, QString name, QString url, QString type);
        bool removeSource(int id);
        Content getLastContent(int sourceId);
        bool updateLastContent(int sourceId, QString title, QString url, QString fingerprint);
    
    private:
        DatabaseManager();
        QSqlDatabase db;
};
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    QString dbPath = QCoreApplication::applicationDirPath() + "/data";
    QDir().mkpath(dbPath);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath + "/sources.db");

    if (!db.open()) {
        qDebug() << "Error: cannot open database - " << db.lastError().text();
    }

    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS sources("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT, "
        "url TEXT UNIQUE, "
        "type TEXT)"
    );
}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::addSource(QString name, QString url, QString type) {
    QSqlQuery query;
    query.prepare("INSERT INTO sources (name, url, type) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(url);
    query.addBindValue(type);
    if (!query.exec()) {
        qDebug() << "Insert failed: " << query.lastError().text();
        return false;
    }
    return true;
}

QVector<QVariantMap> DatabaseManager::getAllSources() {
    QVector<QVariantMap> results;
    QSqlQuery query("SELECT id, name, url, type FROM sources");
    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value("id");
        row["name"] = query.value("name");
        row["url"] = query.value("url");
        row["type"] = query.value("type");
        results.append(row);
    }

    return results;
}

QVariantMap DatabaseManager::getSourceById(int id) {
    QSqlQuery query;
    query.prepare("SELECT id, name, url, type, type FROM sources WHERE id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()) {
        QVariantMap row;
        row["id"] = query.value("id");
        row["name"] = query.value("name");
        row["url"] = query.value("url");
        row["type"] = query.value("type");
        return row;
    }

    return {};
}

bool DatabaseManager::updateSource(int id, QString name, QString url, QString type) {
    QSqlQuery query;
    query.prepare("UPDATE sources SET name = ?, url = ?, type = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(url);
    query.addBindValue(type);
    query.addBindValue(id);
    return query.exec();
}

bool DatabaseManager::removeSource(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM sources WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}
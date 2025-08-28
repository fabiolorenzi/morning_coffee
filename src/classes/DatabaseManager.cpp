#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    QString dbPath = QCoreApplication::applicationDirPath() + "/sources.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

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
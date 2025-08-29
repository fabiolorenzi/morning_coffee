#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
    QString dbPath = QCoreApplication::applicationDirPath() + "/data";
    QDir().mkpath(dbPath);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath + "/data.db");

    if (!db.open()) {
        qDebug() << "Error: cannot open database - " << db.lastError().text();
    }

    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS sources ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT, "
        "url TEXT UNIQUE, "
        "type TEXT)"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS contents ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "sourceId INTEGER NOT NULL UNIQUE, "
        "title TEXT, "
        "url TEXT, "
        "FOREIGN KEY(sourceId) REFERENCES sources(id) ON DELETE CASCADE)"
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

QList<Source> DatabaseManager::getSourcesByType(QString type) {
    QList<Source> sources;
    QSqlQuery query;
    query.prepare("SELECT id, name, url, type FROM sources WHERE type = :type");
    query.bindValue(":type", type);

    if (query.exec()) {
        while (query.next()) {
            Source source;
            source.id = query.value("id").toInt();
            source.name = query.value("name").toString();
            source.url = query.value("url").toString();
            source.type = query.value("type").toString();
            sources.append(source);
        }
    }

    return sources;
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

Content DatabaseManager::getLastContent(int sourceId) {
    Content content {-1, sourceId, "", ""};

    QSqlQuery query;
    query.prepare("SELECT id, title, url FROM contents WHERE sourceId = ?");
    query.addBindValue(sourceId);
    if (!query.exec() && query.next()) {
        content.id = query.value(0).toInt();
        content.title = query.value(1).toString();
        content.url = query.value(2).toString();
    }

    return content;
}

bool DatabaseManager::updateLastContent(int sourceId, QString title, QString url) {
    QSqlQuery query;
    query.prepare("SELECT id from contents WHERE sourceId = ?");
    query.addBindValue(sourceId);
    if (!query.exec()) {
        qDebug() << "Failed to query contents: " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE contents SET title = ?, url = ? WHERE sourceId = ?");
        updateQuery.addBindValue(title);
        updateQuery.addBindValue(url);
        updateQuery.addBindValue(sourceId);
        if (!updateQuery.exec()) {
            qDebug() << "Failed to update contents: " << updateQuery.lastError().text();
            return false;
        }
    } else {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO contents (sourceId, title, url) VALUES (?, ?, ?)");
        insertQuery.addBindValue(sourceId);
        insertQuery.addBindValue(title);
        insertQuery.addBindValue(url);
        if (!insertQuery.exec()) {
            qDebug() << "Failed to insert content: " << insertQuery.lastError().text();
            return false;
        }
    }

    return true;
}
#pragma once

#include <QCryptographicHash>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QXmlStreamReader>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

#include "DatabaseManager.h"

class ViewNewPatreonsWidget : public QWidget {
    Q_OBJECT

public:
    explicit ViewNewPatreonsWidget(QWidget* parent = nullptr);
    void refreshPosts();
    bool hasUpdates();

private:
    QVBoxLayout* layout;
    QListWidget* postList;
    QNetworkAccessManager* manager;

    Content fetchLatestPost(QString& rssUrl);
};
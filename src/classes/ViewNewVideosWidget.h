#pragma once

#include <QDesktopServices>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "classes/DatabaseManager.h"
#include "types/Content.h"
#include "types/Source.h"

class ViewNewVideosWidget : public QWidget {
    Q_OBJECT

    public:
        explicit ViewNewVideosWidget(QWidget* parent = nullptr);
        void refreshVideos();
    
    private:
        QVBoxLayout* layout;
        QListWidget* videoList;
        QNetworkAccessManager* manager;

        Content fetchLatestVideo(QString& channelUrl);
        QString fetchChannelIdFromApi(QString& identifier, const QString& type);
        QString resolveChannelId(QString& url);
};
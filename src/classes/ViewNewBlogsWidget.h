#pragma once

#include <QCryptographicHash>
#include <QDesktopServices>
#include <QEventLoop>
#include <QListWidget>
#include <QListWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "classes/DatabaseManager.h"
#include "types/Content.h"
#include "types/Source.h"

class ViewNewBlogsWidget : public QWidget {
    Q_OBJECT

    public:
        explicit ViewNewBlogsWidget(QWidget* parent = nullptr);
        void refreshBlogs();

    private:
        QVBoxLayout* layout;
        QListWidget* blogList;
        
        Content fetchLatestBlogPost(QString url);
        QString hashHtml(QByteArray& html);
};
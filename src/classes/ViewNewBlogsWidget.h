#pragma once

#include <QDesktopServices>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "DatabaseManager.h"
#include "../types/Content.h"
#include "../types/Source.h"

class ViewNewBlogsWidget : public QWidget {
    Q_OBJECT

    public:
        explicit ViewNewBlogsWidget(QWidget* parent = nullptr);
        void refreshBlogs();

    private:
        QVBoxLayout* layout;
        QListWidget* blogList;
        
        Content fetchLatestBlogPost(QString url);
};
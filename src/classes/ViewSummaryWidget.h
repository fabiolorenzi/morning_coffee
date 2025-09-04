#pragma once

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QDesktopServices>
#include <QUrl>

#include "classes/ViewNewBlogsWidget.h"
#include "classes/ViewNewVideosWidget.h"
#include "classes/ViewNewPatreonsWidget.h"

class ViewSummaryWidget : public QWidget {
    Q_OBJECT

    public:
        explicit ViewSummaryWidget(QWidget* parent = nullptr);
        void refresh();

    signals:
        void openWidget(const QString& type);

    private:
        QVBoxLayout* layout;
        QListWidget* summaryList;

        void addItem(const QString& text, const QString& type);
};
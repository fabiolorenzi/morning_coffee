#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPointer>
#include <QThreadPool>

#include "classes/ClickableLabel.h"
#include "classes/LambdaWorker.h"
#include "classes/ViewNewBlogsWidget.h"
#include "classes/ViewNewVideosWidget.h"
#include "classes/ViewNewPatreonsWidget.h"

class ViewSummaryWidget : public QWidget {
    Q_OBJECT

    public:
        explicit ViewSummaryWidget(QWidget* parent = nullptr);
        void refresh();

    private:
        QVBoxLayout* layout;
        ClickableLabel* blogsLabel;
        ClickableLabel* videosLabel;
        ClickableLabel* patreonsLabel;

        QPointer<ViewNewBlogsWidget> blogsWidget;
        QPointer<ViewNewVideosWidget> videosWidget;
        QPointer<ViewNewPatreonsWidget> patreonsWidget;
        QThreadPool* threadPool;

        void checkBlogs();
        void checkVideos();
        void checkPatreons();

    signals:
        void updateLabel(ClickableLabel* label, const QString& text);
};
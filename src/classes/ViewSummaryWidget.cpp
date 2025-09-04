#include "ViewSummaryWidget.h"

ViewSummaryWidget::ViewSummaryWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    summaryList = new QListWidget(this);

    layout->addWidget(summaryList);
    setLayout(layout);

    connect(summaryList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        if (!item) return;
        QString type = item->data(Qt::UserRole).toString();
        emit openWidget(type);
    });
}

void ViewSummaryWidget::refresh() {
    summaryList->clear();

    addItem("Checking blogs...", "blogs");
    addItem("Checking videos...", "videos");
    addItem("Checking patreons...", "patreons");

    QFuture<bool> blogsFuture = QtConcurrent::run([] {
        ViewNewBlogsWidget blogsCheck;
        return blogsCheck.hasUpdates();
    });

    QFuture<bool> videosFuture = QtConcurrent::run([] {
        ViewNewVideosWidget videosCheck;
        return videosCheck.hasUpdates();
    });

    QFuture<bool> patreonsFuture = QtConcurrent::run([] {
        ViewNewPatreonsWidget patreonsCheck;
        return patreonsCheck.hasUpdates();
    });

    auto blogsWatcher = new QFutureWatcher<bool>(this);
    auto videosWatcher = new QFutureWatcher<bool>(this);
    auto patreonsWatcher = new QFutureWatcher<bool>(this);

    connect(blogsWatcher, &QFutureWatcher<bool>::finished, this, [=]() {
        bool result = blogsWatcher->result();
        for (int i = 0; i < summaryList->count(); ++i) {
            auto* item = summaryList->item(i);
            if (item->data(Qt::UserRole).toString() == "blogs") {
                item->setText(result ? "New blogs available" : "No blog updates");
            }
        }
        blogsWatcher->deleteLater();
    });

    connect(videosWatcher, &QFutureWatcher<bool>::finished, this, [=]() {
        bool result = videosWatcher->result();
        for (int i = 0; i < summaryList->count(); ++i) {
            auto* item = summaryList->item(i);
            if (item->data(Qt::UserRole).toString() == "videos") {
                item->setText(result ? "New videos available" : "No video updates");
            }
        }
        videosWatcher->deleteLater();
    });

    connect(patreonsWatcher, &QFutureWatcher<bool>::finished, this, [=]() {
        bool result = patreonsWatcher->result();
        for (int i = 0; i < summaryList->count(); ++i) {
            auto* item = summaryList->item(i);
            if (item->data(Qt::UserRole).toString() == "patreons") {
                item->setText(result ? "New Patreon posts available" : "No Patreon updates");
            }
        }
        patreonsWatcher->deleteLater();
    });

    blogsWatcher->setFuture(blogsFuture);
    videosWatcher->setFuture(videosFuture);
    patreonsWatcher->setFuture(patreonsFuture);
}

void ViewSummaryWidget::addItem(const QString& text, const QString& type) {
    auto* item = new QListWidgetItem(text, summaryList);
    item->setData(Qt::UserRole, type);
    summaryList->addItem(item);
}
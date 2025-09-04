#include "ViewSummaryWidget.h"

ViewSummaryWidget::ViewSummaryWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    blogsLabel = new ClickableLabel("Checking for new blogs...");
    videosLabel = new ClickableLabel("Checking for new videos...");
    patreonsLabel = new ClickableLabel("Checking for new posts...");

    layout->addWidget(blogsLabel);
    layout->addWidget(videosLabel);
    layout->addWidget(patreonsLabel);

    setLayout(layout);

    videosWidget = new ViewNewVideosWidget();
    blogsWidget = new ViewNewBlogsWidget();
    patreonsWidget = new ViewNewPatreonsWidget();

    threadPool = QThreadPool::globalInstance();

    connect(videosLabel, &ClickableLabel::clicked, this, [this]() { videosWidget->show(); });
    connect(blogsLabel, &ClickableLabel::clicked, this, [this]() { blogsWidget->show(); });
    connect(patreonsLabel, &ClickableLabel::clicked, this, [this]() { patreonsWidget->show(); });

    connect(this, &ViewSummaryWidget::updateLabel, this, [this](ClickableLabel* label, const QString& text) {
        label->setText(text);
    });
}

void ViewSummaryWidget::refresh() {
    checkBlogs();
    checkVideos();
    checkPatreons();
}

void ViewSummaryWidget::checkBlogs() {
    auto worker = new LambdaWorker([this]() {
        bool updates = blogsWidget->hasUpdates();
        QString text = updates > 0 ? "New blogs available" : "No blog updates";
        emit updateLabel(blogsLabel, text);
    });
    threadPool->start(worker);
}

void ViewSummaryWidget::checkVideos() {
    auto worker = new LambdaWorker([this]() {
        bool updates = videosWidget->hasUpdates();
        QString text = updates > 0 ? "New videos available" : "No video updates";
        emit updateLabel(videosLabel, text);
    });
    threadPool->start(worker);
}

void ViewSummaryWidget::checkPatreons() {
    auto worker = new LambdaWorker([this]() {
        bool updates = patreonsWidget->hasUpdates();
        QString text = updates > 0 ? "New Patreon posts available" : "No Patreon updates";
        emit updateLabel(patreonsLabel, text);
    });
    threadPool->start(worker);
}
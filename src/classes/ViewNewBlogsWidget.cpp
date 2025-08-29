#include "ViewNewBlogsWidget.h"

ViewNewBlogsWidget::ViewNewBlogsWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    blogList = new QListWidget(this);

    layout->addWidget(blogList);
    setLayout(layout);
}

void ViewNewBlogsWidget::refreshBlogs() {
    blogList->clear();

    QList<Source> sources = DatabaseManager::instance().getSourcesByType("Blog");
    for (Source& source : sources) {
        int sourceId = source.id;
        QString name = source.name;
        QString url = source.url;

        Content latestContent = fetchLatestBlogPost(url);
        Content lastContent = DatabaseManager::instance().getLastContent(sourceId);

        if (latestContent != lastContent) {
            DatabaseManager::instance().updateLastContent(sourceId, latestContent.title, latestContent.url);
            QListWidgetItem* item = new QListWidgetItem(
                QString("%1 - New blog post: %2").arg(name, latestContent.title),
                blogList
            );
            item->setData(Qt::UserRole, latestContent.url);
            blogList->addItem(item);
        }
    }

    connect(blogList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        if (item) {
            QString url = item->data(Qt::UserRole).toString();
            QDesktopServices::openUrl(QUrl(url));
        }
    });
}

Content ViewNewBlogsWidget::fetchLatestBlogPost(QString url) {
    Content c;
    c.id = -1;
    c.sourceId = -1;
    c.title = "test_title";
    c.url = url;
    return c;
}
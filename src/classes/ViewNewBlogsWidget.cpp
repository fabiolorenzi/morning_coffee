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

        if (latestContent.fingerprint != lastContent.fingerprint) {
            DatabaseManager::instance().updateLastContent(
                sourceId, latestContent.title, latestContent.url, latestContent.fingerprint
            );

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
    QNetworkAccessManager manager;
    QNetworkRequest request{QUrl(url)};

    QEventLoop loop;
    QNetworkReply* reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    Content c;
    c.id = -1;
    c.sourceId = -1;
    c.url = url;
    c.title = "New content detected";

    if (reply->error() == QNetworkReply::NoError) {
        QString html = QString::fromUtf8(reply->readAll());

        // Remove scripts and styles
        html.remove(QRegularExpression("<script[^>]*>.*?</script>", QRegularExpression::DotMatchesEverythingOption));
        html.remove(QRegularExpression("<style[^>]*>.*?</style>", QRegularExpression::DotMatchesEverythingOption));

        QByteArray hash = QCryptographicHash::hash(html.toUtf8(), QCryptographicHash::Sha256);
        c.fingerprint = QString(hash.toHex());
    } else {
        c.title = "Error fetching";
        c.fingerprint = "error";
    }

    reply->deleteLater();
    return c;
}

QString ViewNewBlogsWidget::hashHtml(QByteArray& html) {
    QByteArray hash = QCryptographicHash::hash(html, QCryptographicHash::Sha256);
    return QString(hash.toHex());
}
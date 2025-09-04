#include "ViewNewPatreonsWidget.h"

ViewNewPatreonsWidget::ViewNewPatreonsWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    postList = new QListWidget(this);
    manager = new QNetworkAccessManager(this);

    layout->addWidget(postList);
    setLayout(layout);
}

void ViewNewPatreonsWidget::refreshPosts() {
    postList->clear();

    QList<Source> sources = DatabaseManager::instance().getSourcesByType("Patreon");

    for (Source& source : sources) {
        int sourceId = source.id;
        QString name = source.name;
        QString url = source.url;

        Content latestContent = fetchLatestPost(url);
        Content lastContent = DatabaseManager::instance().getLastContent(sourceId);

        bool firstRun = lastContent.fingerprint.isEmpty() || lastContent.fingerprint == "none";

        if (firstRun || latestContent.fingerprint != lastContent.fingerprint) {
            QString displayTitle = firstRun ? "New posts available" : latestContent.title;

            QListWidgetItem* item = new QListWidgetItem(
                QString("%1 - %2").arg(name, displayTitle),
                postList
            );
            item->setData(Qt::UserRole, latestContent.url);
            postList->addItem(item);

            DatabaseManager::instance().updateLastContent(
                sourceId, displayTitle, latestContent.url, latestContent.fingerprint
            );
        }
    }

    if (postList->count() == 0) {
        QListWidgetItem* item = new QListWidgetItem("No updates available", postList);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        postList->addItem(item);
    }

    connect(postList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        if (item) {
            QString url = item->data(Qt::UserRole).toString();
            if (!url.isEmpty()) {
                QDesktopServices::openUrl(QUrl(url));
            }
        }
    });
}

Content ViewNewPatreonsWidget::fetchLatestPost(QString& pageUrl) {
    Content c;
    c.id = -1;
    c.sourceId = -1;
    c.url = pageUrl;

    QNetworkRequest request{QUrl(pageUrl)};
    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error fetching Patreon page:" << reply->errorString();
        c.title = "Network error";
        c.fingerprint = "error";
        reply->deleteLater();
        return c;
    }

    QByteArray data = reply->readAll();
    reply->deleteLater();

    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    QString fingerprint = QString(hash.toHex());

    c.title = "New posts available";
    c.url = pageUrl;
    c.fingerprint = fingerprint;

    return c;
}
#include "ViewNewVideosWidget.h"

static const QString YOUTUBE_API_KEY = qEnvironmentVariable("YOUTUBE_API_KEY");

ViewNewVideosWidget::ViewNewVideosWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    videoList = new QListWidget(this);
    manager = new QNetworkAccessManager(this);

    layout->addWidget(videoList);
    setLayout(layout);
}

void ViewNewVideosWidget::refreshVideos() {
    videoList->clear();

    QList<Source> sources = DatabaseManager::instance().getSourcesByType("YouTube channel");

    for (Source& source : sources) {
        int sourceId = source.id;
        QString name = source.name;
        QString url = source.url;

        Content latestContent = fetchLatestVideo(url);
        Content lastContent = DatabaseManager::instance().getLastContent(sourceId);

        qDebug() << "Source:" << name << "Latest video fingerprint:" << latestContent.fingerprint
                 << "Last fingerprint:" << lastContent.fingerprint;

        if (latestContent.fingerprint != lastContent.fingerprint) {
            DatabaseManager::instance().updateLastContent(
                sourceId, latestContent.title, latestContent.url, latestContent.fingerprint
            );

            QListWidgetItem* item = new QListWidgetItem(
                QString("%1 - New video: %2").arg(name, latestContent.title),
                videoList
            );
            item->setData(Qt::UserRole, latestContent.url);
            videoList->addItem(item);
        }
    }

    if (videoList->count() == 0) {
        QListWidgetItem* item = new QListWidgetItem("No updates available", videoList);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        videoList->addItem(item);
    }

    connect(videoList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        if (item) {
            QString url = item->data(Qt::UserRole).toString();
            if (!url.isEmpty()) {
                QDesktopServices::openUrl(QUrl(url));
            }
        }
    });
}

Content ViewNewVideosWidget::fetchLatestVideo(QString& channelUrl) {
    Content c;
    c.id = -1;
    c.sourceId = -1;
    c.url = channelUrl;

    QString channelId = resolveChannelId(channelUrl);
    qDebug() << "Resolved channel ID for URL" << channelUrl << ":" << channelId;

    if (channelId.isEmpty()) {
        c.title = "Error: could not resolve channel";
        c.fingerprint = "error";
        return c;
    }

    QString apiUrl = QString(
        "https://www.googleapis.com/youtube/v3/search?key=%1&channelId=%2&part=snippet&order=date&maxResults=1"
    ).arg(YOUTUBE_API_KEY, channelId);

    QNetworkRequest request{QUrl(apiUrl)};
    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);

        if (!doc.isNull() && doc.isObject()) {
            QJsonArray items = doc.object()["items"].toArray();
            if (!items.isEmpty()) {
                QJsonObject video = items[0].toObject();
                QJsonObject snippet = video["snippet"].toObject();
                QString videoTitle = snippet["title"].toString();
                QString videoId = video["id"].toObject()["videoId"].toString();

                if (videoId.isEmpty()) {
                    c.title = "No videos found";
                    c.fingerprint = "none";
                } else {
                    c.title = videoTitle;
                    c.url = "https://www.youtube.com/watch?v=" + videoId;
                    c.fingerprint = videoId;
                }
            } else {
                c.title = "No videos found";
                c.fingerprint = "none";
            }
        } else {
            c.title = "Error parsing response";
            c.fingerprint = "error";
        }
    } else {
        c.title = "Network error";
        c.fingerprint = "error";
        qDebug() << "Network error fetching latest video:" << reply->errorString();
    }

    reply->deleteLater();
    return c;
}

QString ViewNewVideosWidget::resolveChannelId(QString& url)
{
    QRegularExpression reChannel("https?://(www\\.)?youtube\\.com/channel/([a-zA-Z0-9_-]+)");
    QRegularExpressionMatch match = reChannel.match(url);
    if (match.hasMatch()) return match.captured(2);

    QRegularExpression reCustom("https?://(www\\.)?youtube\\.com/c/([a-zA-Z0-9_-]+)");
    match = reCustom.match(url);
    if (match.hasMatch()) {
        QString customName = match.captured(2);
        return fetchChannelIdFromApi(customName, "forUsername");
    }

    QRegularExpression reHandle("https?://(www\\.)?youtube\\.com/@([a-zA-Z0-9_-]+)");
    match = reHandle.match(url);
    if (match.hasMatch()) {
        QString handle = match.captured(2);
        return fetchChannelIdFromApi(handle, "handle");
    }

    return "";
}

QString ViewNewVideosWidget::fetchChannelIdFromApi(QString& identifier, const QString& type) {
    QString apiUrl = QString(
        "https://www.googleapis.com/youtube/v3/channels?key=%1&%2=%3&part=id"
    ).arg(YOUTUBE_API_KEY, type, identifier);

    QNetworkRequest request{QUrl(apiUrl)};
    QNetworkReply* reply = manager->get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();
        if (!doc.isNull() && doc.isObject()) {
            QJsonArray items = doc.object()["items"].toArray();
            if (!items.isEmpty()) {
                return items[0].toObject()["id"].toString();
            }
        }
    } else {
        qDebug() << "Error resolving channel ID from API:" << reply->errorString();
        reply->deleteLater();
    }

    return "";
}
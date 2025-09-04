#include "SecurityHelper.h"

void SecurityHelper::loadDotEnv(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.startsWith("#") || line.isEmpty())
            continue;

        QStringList parts = line.split("=", Qt::KeepEmptyParts);
        if (parts.size() == 2) {
            qputenv(parts[0].toUtf8(), parts[1].toUtf8());
        }
    }
}
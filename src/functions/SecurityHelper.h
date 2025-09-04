#pragma once

#include <QFile>
#include <QTextStream>
#include <QProcessEnvironment>

namespace SecurityHelper {
    void loadDotEnv(const QString& path = ".env");
};
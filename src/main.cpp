#include <QApplication>
#include <QIcon>
#include "classes/MainWindow.h"

#include "functions/SecurityHelper.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    SecurityHelper::loadDotEnv();
    QString apiKey = qEnvironmentVariable("YOUTUBE_API_KEY");

    app.setWindowIcon(QIcon(":/icons/icon.png"));

    MainWindow window;
    window.show();

    return app.exec();
}
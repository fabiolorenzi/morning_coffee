#include <QApplication>
#include <QIcon>
#include "classes/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/icon.png"));

    MainWindow window;
    window.show();

    return app.exec();
}
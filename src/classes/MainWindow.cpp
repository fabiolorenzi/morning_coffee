#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowFlags(Qt::Window);
    setMinimumSize(Sizes::minWidth, Sizes::minHeight);
    resize(Sizes::minWidth, Sizes::minHeight);

    setWindowTitle("Morning Coffee");

    defaultWidget = new DefaultWidget(this);
    setCentralWidget(defaultWidget);
}
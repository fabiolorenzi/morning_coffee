#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowFlags(Qt::Window);
    setMinimumSize(500, 400);
    resize(500, 400);

    setWindowTitle("Morning Coffee");

    defaultWidget = new DefaultWidget(this);
    setCentralWidget(defaultWidget);
}
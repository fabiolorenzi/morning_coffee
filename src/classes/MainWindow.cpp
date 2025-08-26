#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Morning Coffee");

    QLabel* label = new QLabel("Hello world", this);
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);

    resize(500, 400);
}
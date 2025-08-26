#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);

    setWindowFlags(Qt::Window);
    setMinimumSize(Sizes::minWidth, Sizes::minHeight);
    resize(Sizes::minWidth, Sizes::minHeight);

    setWindowTitle("Morning Coffee");
    menuBar = new MenuBar(this);
    setMenuBar(menuBar);

    defaultWidget = new DefaultWidget(this);
    addSourceWidget = new AddSourceWidget(this);

    stackedWidget->addWidget(defaultWidget);
    stackedWidget->addWidget(addSourceWidget);

    setCentralWidget(stackedWidget);

    connect(menuBar->findChild<QAction*>("addNewSource"), &QAction::triggered, this, &MainWindow::showAddSourceWidget);
    
    showDefaultWidget();
}

void MainWindow::showDefaultWidget() {
    stackedWidget->setCurrentWidget(defaultWidget);
}

void MainWindow::showAddSourceWidget() {
    stackedWidget->setCurrentWidget(addSourceWidget);
}
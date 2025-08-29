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
    manageSourcesWidget = new ManageSourcesWidget(this);
    viewNewBlogsWidget = new ViewNewBlogsWidget(this);

    stackedWidget->addWidget(defaultWidget);
    stackedWidget->addWidget(addSourceWidget);
    stackedWidget->addWidget(manageSourcesWidget);
    stackedWidget->addWidget(viewNewBlogsWidget);

    setCentralWidget(stackedWidget);

    connect(menuBar->findChild<QAction*>("addNewSource"), &QAction::triggered, this, &MainWindow::showAddSourceWidget);
    connect(menuBar->findChild<QAction*>("manageSources"), &QAction::triggered, this, &MainWindow::showManageSourcesWidget);
    connect(menuBar->findChild<QAction*>("viewNewBlogs"), &QAction::triggered, this, &MainWindow::showViewNewBlogsWidget);
    
    showDefaultWidget();
}

void MainWindow::showDefaultWidget() {
    stackedWidget->setCurrentWidget(defaultWidget);
}

void MainWindow::showAddSourceWidget() {
    stackedWidget->setCurrentWidget(addSourceWidget);
    addSourceWidget->refreshInputs();
}

void MainWindow::showManageSourcesWidget() {
    stackedWidget->setCurrentWidget(manageSourcesWidget);
    manageSourcesWidget->refreshSources();
}

void MainWindow::showViewNewBlogsWidget() {
    stackedWidget->setCurrentWidget(viewNewBlogsWidget);
    viewNewBlogsWidget->refreshBlogs();
}
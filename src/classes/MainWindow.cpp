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
    viewSummaryWidget = new ViewSummaryWidget(this);
    viewNewBlogsWidget = new ViewNewBlogsWidget(this);
    viewNewVideosWidget = new ViewNewVideosWidget(this);
    viewNewPatreonsWidget = new ViewNewPatreonsWidget(this);

    stackedWidget->addWidget(defaultWidget);
    stackedWidget->addWidget(addSourceWidget);
    stackedWidget->addWidget(manageSourcesWidget);
    stackedWidget->addWidget(viewSummaryWidget);
    stackedWidget->addWidget(viewNewBlogsWidget);
    stackedWidget->addWidget(viewNewVideosWidget);
    stackedWidget->addWidget(viewNewPatreonsWidget);

    setCentralWidget(stackedWidget);

    connect(menuBar->findChild<QAction*>("addNewSource"), &QAction::triggered, this, &MainWindow::showAddSourceWidget);
    connect(menuBar->findChild<QAction*>("manageSources"), &QAction::triggered, this, &MainWindow::showManageSourcesWidget);
    connect(menuBar->findChild<QAction*>("viewSummary"), &QAction::triggered, this, &MainWindow::showViewSummaryWidget);
    connect(menuBar->findChild<QAction*>("viewNewBlogs"), &QAction::triggered, this, &MainWindow::showViewNewBlogsWidget);
    connect(menuBar->findChild<QAction*>("viewNewVideos"), &QAction::triggered, this, &MainWindow::showViewNewVideosWidget);
    connect(menuBar->findChild<QAction*>("viewNewPatreons"), &QAction::triggered, this, &MainWindow::showViewNewPatreonsWidget);

    connect(viewSummaryWidget, &ViewSummaryWidget::openWidget, this, [this](const QString& type) {
        if (type == "blogs") {
            showViewNewBlogsWidget();
        } else if (type == "videos") {
            showViewNewVideosWidget();
        } else if (type == "patreons") {
            showViewNewPatreonsWidget();
        }
    });
    
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

void MainWindow::showViewSummaryWidget() {
    stackedWidget->setCurrentWidget(viewSummaryWidget);
    viewSummaryWidget->refresh();
}

void MainWindow::showViewNewBlogsWidget() {
    stackedWidget->setCurrentWidget(viewNewBlogsWidget);
    viewNewBlogsWidget->refreshBlogs();
}

void MainWindow::showViewNewVideosWidget() {
    stackedWidget->setCurrentWidget(viewNewVideosWidget);
    viewNewVideosWidget->refreshVideos();
}

void MainWindow::showViewNewPatreonsWidget() {
    stackedWidget->setCurrentWidget(viewNewPatreonsWidget);
    viewNewPatreonsWidget->refreshPosts();
}
#include "MenuBar.h"

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    fileMenu = new QMenu("File", this);
    viewMenu = new QMenu("View", this);
    helpMenu = new QMenu("Help", this);

    addNewSourceAction = new QAction("Add new source", this);
    manageSourcesAction = new QAction("Manage sources", this);
    exitAction = new QAction("Exit", this);
    viewSummaryAction = new QAction("View summary", this);
    viewNewBlogsAction = new QAction("View new blogs", this);
    viewNewVideosAction = new QAction("View new videos", this);
    viewNewPatreonsAction = new QAction("View new patreons", this);
    aboutAction = new QAction("About", this);
    tutorialAction = new QAction("Tutorial", this);
    githubAction = new QAction("Visit GitHub page", this);

    addNewSourceAction->setObjectName("addNewSource");
    manageSourcesAction->setObjectName("manageSources");
    connect(exitAction, &QAction::triggered, parent, &QWidget::close);
    connect(viewSummaryAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "viewSummaryAction", "function worked");
    });
    viewNewBlogsAction->setObjectName("viewNewBlogs");
    viewNewVideosAction->setObjectName("viewNewVideos");
    connect(viewNewPatreonsAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "viewNewPatreonAction", "function worked");
    });
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "aboutAction", "function worked");
    });
    connect(tutorialAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "tutorialAction", "function worked");
    });
    connect(githubAction, &QAction::triggered, this, &MenuBar::githubRedirect);

    fileMenu->addAction(addNewSourceAction);
    fileMenu->addAction(manageSourcesAction);
    fileMenu->addAction(exitAction);
    viewMenu->addAction(viewSummaryAction);
    viewMenu->addAction(viewNewBlogsAction);
    viewMenu->addAction(viewNewVideosAction);
    viewMenu->addAction(viewNewPatreonsAction);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(tutorialAction);
    helpMenu->addAction(githubAction);

    addMenu(fileMenu);
    addMenu(viewMenu);
    addMenu(helpMenu);
}

void MenuBar::githubRedirect() {
    QDesktopServices::openUrl(QUrl("https://github.com/fabiolorenzi/morning_coffee.git"));
}
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

    tutorial = new TutorialDialog(this);

    addNewSourceAction->setObjectName("addNewSource");
    manageSourcesAction->setObjectName("manageSources");
    connect(exitAction, &QAction::triggered, parent, &QWidget::close);
    viewSummaryAction->setObjectName("viewSummary");
    viewNewBlogsAction->setObjectName("viewNewBlogs");
    viewNewVideosAction->setObjectName("viewNewVideos");
    viewNewPatreonsAction->setObjectName("viewNewPatreons");
    connect(aboutAction, &QAction::triggered, this, [this]() {
    QString aboutText = QString(
        "This is a project made for testing purposes.\n"
        "It has been designed for improving my skills in C++, Qt, GitHub Actions and multithreading.\n"
        "Version 1.0.0"
    );

    QMessageBox::about(this, "About", aboutText);
});
    connect(tutorialAction, &QAction::triggered, this, [this]() {
        tutorial->exec();
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
#pragma once

#include <QAction>
#include <QDesktopServices>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QUrl>

class MenuBar : public QMenuBar {
    Q_OBJECT

    public:
        explicit MenuBar(QWidget* parent = nullptr);

    private:
        QMenu* fileMenu;
        QMenu* viewMenu;
        QMenu* helpMenu;

        QAction* addNewSourceAction;
        QAction* manageSourcesAction;
        QAction* exitAction;
        QAction* viewSummaryAction;
        QAction* viewNewBlogsAction;
        QAction* viewNewVideosAction;
        QAction* viewNewPatreonsAction;
        QAction* aboutAction;
        QAction* tutorialAction;
        QAction* githubAction;

        void githubRedirect();
};
#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "AddSourceWidget.h"
#include "DefaultWidget.h"
#include "ManageSourcesWidget.h"
#include "MenuBar.h"

#include "../constants/Sizes.h"

class MainWindow: public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);

    private:
        MenuBar* menuBar;
        QStackedWidget* stackedWidget;
        AddSourceWidget* addSourceWidget;
        ManageSourcesWidget* manageSourcesWidget;
        DefaultWidget* defaultWidget;

    private slots:
        void showDefaultWidget();
        void showAddSourceWidget();
        void showManageSourcesWidget();
};
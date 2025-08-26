#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "AddSourceWidget.h"
#include "DefaultWidget.h"
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
        DefaultWidget* defaultWidget;

    private slots:
        void showDefaultWidget();
        void showAddSourceWidget();
};
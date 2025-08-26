#pragma once

#include <QMainWindow>
#include "DefaultWidget.h"
#include "MenuBar.h"

#include "../constants/Sizes.h"

class MainWindow: public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
    private:
        MenuBar* menuBar;
        DefaultWidget* defaultWidget;
};
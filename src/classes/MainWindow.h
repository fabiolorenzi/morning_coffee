#pragma once

#include <QMainWindow>
#include <QLabel>
#include "DefaultWidget.h"

#include "../constants/Sizes.h"

class MainWindow: public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
    private:
        QLabel* frameLabel;
        DefaultWidget* defaultWidget;
};
#pragma once

#include <QMainWindow>
#include <QLabel>
#include "DefaultWidget.h"

class MainWindow: public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
    private:
        QLabel* frameLabel;
        DefaultWidget* defaultWidget;
};
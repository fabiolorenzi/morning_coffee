#pragma once

#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QWidget>

#include "../constants/Colours.h"
#include "../constants/FontSizes.h"

class Spinner : public QWidget {
    Q_OBJECT
    
    public:
        explicit Spinner(QWidget* parent = nullptr);
        void start();
        void stop();

    protected:
        void paintEvent(QPaintEvent* event) override;

    private slots:
        void rotate();

    private:
        QTimer timer;
        int size;
        int lineCount;
        int currentAngle;
};
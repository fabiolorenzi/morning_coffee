#pragma once

#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "constants/Colours.h"

enum ButtonType {
    Primary,
    Secondary
};

class Button: public QPushButton {
    Q_OBJECT

    public:
        explicit Button(const QString text, ButtonType type, QWidget* parent = nullptr);
};
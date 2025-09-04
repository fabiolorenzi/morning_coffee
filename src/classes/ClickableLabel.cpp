#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(const QString& text, QWidget* parent) : QLabel(text, parent) {
    setStyleSheet("color: blue; text-decoration: underline; cursor: pointer;");
}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
    QLabel::mousePressEvent(event);
}
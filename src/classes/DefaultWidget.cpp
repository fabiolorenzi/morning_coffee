#include "DefaultWidget.h"

DefaultWidget::DefaultWidget(QWidget* parent) : QWidget(parent), pixmap(":/images/neumorphed_logo.png") {
    layout = new QVBoxLayout(this);
    frameLabel = new QLabel(this);

    frameLabel->setAlignment(Qt::AlignCenter);
    frameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(frameLabel);

    ManageColours::SetBackgroundColour(*this);

    frameLabel->setPixmap(pixmap.scaled(frameLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void DefaultWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    frameLabel->setPixmap(pixmap.scaled(frameLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
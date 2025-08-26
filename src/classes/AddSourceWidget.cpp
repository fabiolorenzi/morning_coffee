#include "AddSourceWidget.h"

AddSourceWidget::AddSourceWidget(QWidget* parent) {
    layout = new QVBoxLayout(this);
    frameLabel = new QLabel(this);

    QLabel* label = new QLabel("this is a test", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    setLayout(layout);
}
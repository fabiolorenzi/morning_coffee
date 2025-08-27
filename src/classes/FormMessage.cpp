#include "FormMessage.h"

FormMessage::FormMessage(QWidget* parent) : QWidget(parent) {
    layout = new QHBoxLayout(this);

    message = new QLabel(this);
    spinner = new Spinner(this);
    spinner->hide();

    layout->addWidget(message, 1, Qt::AlignRight);
    layout->addWidget(spinner, 0, Qt::AlignVCenter);
    layout->setContentsMargins(0, 10, 0, 0);

    setLayout(layout);
    setVisible(false);
}

void FormMessage::setMessage(QString text, MessageType type) {
    message->setText(text);
    
    switch (type) {
        case MessageType::Success:
            message->setStyleSheet(QString("color: %1; font-weight: bold;").arg(Colours::successColour.name()));
            break;
        case MessageType::Fail:
            message->setStyleSheet(QString("color: %1; font-weight: bold;").arg(Colours::failureColour.name()));
            break;
    }

    setVisible(true);
};

void FormMessage::clearMessage() {
    message->clear();
    setVisible(false);
}

void FormMessage::manageSpinner(bool show) {
    setVisible(show);
    if (show) {
        spinner->start();
    } else {
        spinner->stop();
    }
}
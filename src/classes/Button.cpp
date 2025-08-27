#include "Button.h"

Button::Button(QString text, ButtonType type, QWidget* parent) : QPushButton(text, parent) {
    QString style;

    switch (type) {
        case ButtonType::Primary:
            style = QString(
                "QPushButton {"
                " background-color: %1;"
                " color: %2;"
                " border-radius: 4px;"
                " padding: 5px 15px;"
                "}"
                "QPushButton:hover {"
                " background-color: %3;"
                "}"
                "QPushButton:pressed {"
                " background-color: %4;"
                "}"
            ).arg(
                Colours::primaryButton.name(),
                Colours::buttonText.name(),
                Colours::primaryButtonHover.name(),
                Colours::primaryButtonPressed.name()
            );
            break;
        case ButtonType::Secondary:
            style = QString(
                "QPushButton {"
                " background-color: %1;"
                " color: %2;"
                " border-radius: 4px;"
                " padding: 5px 15px;"
                "}"
                "QPushButton:hover {"
                " background-color: %3;"
                "}"
                "QPushButton:pressed {"
                " background-color: %4;"
                "}"
            ).arg(
                Colours::secondaryButton.name(),
                Colours::buttonText.name(),
                Colours::secondaryButtonHover.name(),
                Colours::secondaryButtonPressed.name()
            );
            break;
    };

    setStyleSheet(style);

    setCursor(Qt::PointingHandCursor);
    auto* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(5);
    shadowEffect->setOffset(2, 2);
    shadowEffect->setColor(Colours::shadow);
    this->setGraphicsEffect(shadowEffect);
}
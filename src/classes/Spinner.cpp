#include "Spinner.h"

Spinner::Spinner(QWidget* parent) : QWidget(parent) {
    size = FontSizes::spinnerSize;
    lineCount = 12;
    currentAngle = 0;

    setFixedSize(size, size);
    connect(&timer, &QTimer::timeout, this, &Spinner::rotate);
};

void Spinner::start() {
    timer.start(50);
    show();
}

void Spinner::stop() {
    timer.stop();
    hide();
}

void Spinner::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int radius = size / 2;
    p.translate(radius, radius);

    for (int i = 0; i < lineCount; ++i) {
        QColor color = Colours::darkGrey;
        color.setAlphaF(1.0 - (i / (float)lineCount));
        p.setPen(Qt::NoPen);
        p.setBrush(color);

        p.save();
        p.rotate(currentAngle + i * (360 / lineCount));
        p.drawRoundedRect(-2, -radius + 2, 4, radius / 3, 2, 2);
        p.restore();
    }
}

void Spinner::rotate() {
    currentAngle = (currentAngle + 30) % 360;
    update();
}
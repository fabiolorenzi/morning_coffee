#include "WidgetHelper.h"

void WidgetHelper::SetBackgroundColour(QWidget& widget) {
    QPalette pal = widget.palette();
    pal.setColor(QPalette::Window, Colours::background);
    widget.setAutoFillBackground(true);
    widget.setPalette(pal);
}
#pragma once

#include <QLabel>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QWidget>

#include "functions/WidgetHelper.h"

class DefaultWidget : public QWidget {
    Q_OBJECT

    public:
        explicit DefaultWidget(QWidget* parent = nullptr);

    protected:
        void resizeEvent(QResizeEvent* event) override;

    private:
        QVBoxLayout* layout;
        QLabel* frameLabel;
        QPixmap pixmap;
};
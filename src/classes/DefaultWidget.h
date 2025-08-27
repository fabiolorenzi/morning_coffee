#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>

#include "../functions/ManageColours.h"

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
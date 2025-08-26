#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>

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
        QPalette pal;
};
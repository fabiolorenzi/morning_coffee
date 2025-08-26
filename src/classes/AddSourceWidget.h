#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class AddSourceWidget : public QWidget {
    Q_OBJECT

    public:
        explicit AddSourceWidget(QWidget* parent = nullptr);

    private:
        QVBoxLayout* layout;
        QLabel* frameLabel;
};
#pragma once

#include <QWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "../classes/Button.h"
#include "../functions/ManageColours.h"

class AddSourceWidget : public QWidget {
    Q_OBJECT

    public:
        explicit AddSourceWidget(QWidget* parent = nullptr);

    private slots:
        void clearForm();
        void submitForm();

    private:
        QVBoxLayout* mainLayout;
        QFormLayout* formLayout;
        QLineEdit* nameInput;
        QLineEdit* urlInput;
        QComboBox* typeSelect;
        QHBoxLayout* buttonLine;
        Button* clearButton;
        Button* submitButton;
};
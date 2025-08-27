#pragma once

#include <QWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

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
        QPushButton* clearButton;
        QPushButton* submitButton;
};
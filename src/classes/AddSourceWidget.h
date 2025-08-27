#pragma once

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "Button.h"
#include "FormMessage.h"
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
        FormMessage* formMessage;
        QHBoxLayout* buttonLine;
        Button* clearButton;
        Button* submitButton;

        void manageButton(bool disable);
};
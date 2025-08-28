#pragma once

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "Button.h"
#include "DatabaseManager.h"
#include "FormMessage.h"
#include "../functions/WidgetHelper.h"

class AddSourceWidget : public QWidget {
    Q_OBJECT

    public:
        explicit AddSourceWidget(QWidget* parent = nullptr);
        void refreshInputs();

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
        QNetworkAccessManager* manager;

        void disableInputs(bool disable);
};
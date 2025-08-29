#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QWidget>

#include "classes/Spinner.h"
#include "constants/Colours.h"

enum MessageType {
    Success,
    Fail
};

class FormMessage : public QWidget {
    Q_OBJECT

    public:
        explicit FormMessage(QWidget* parent = nullptr);
        void setMessage(QString text, MessageType type);
        void clearMessage();
        void manageSpinner(bool show);

    private:
        QHBoxLayout* layout;
        QLabel* message;
        Spinner* spinner;
};
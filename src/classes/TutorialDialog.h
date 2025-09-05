#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class TutorialDialog : public QDialog {
    Q_OBJECT
    
    public:
        explicit TutorialDialog(QWidget *parent = nullptr);
};
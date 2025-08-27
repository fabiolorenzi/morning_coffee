#include "AddSourceWidget.h"

AddSourceWidget::AddSourceWidget(QWidget* parent) {
    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout;
    buttonLine = new QHBoxLayout;

    nameInput = new QLineEdit(this);
    urlInput = new QLineEdit(this);
    typeSelect = new QComboBox(this);
    formMessage = new FormMessage(this);
    clearButton = new Button("Cancel", ButtonType::Secondary, this);
    submitButton = new Button("Add", ButtonType::Primary, this);

    typeSelect->addItems({"-----", "Blog", "Youtube channel", "Patreon"});

    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("URL:", urlInput);
    formLayout->addRow("Type:", typeSelect);
    buttonLine->addWidget(clearButton);
    buttonLine->addWidget(submitButton);

    mainLayout->addLayout(formLayout, 0);
    mainLayout->addWidget(formMessage, 0, Qt::AlignTop);

    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLine, 0);

    setLayout(mainLayout);

    ManageColours::SetBackgroundColour(*this);

    connect(clearButton, &QPushButton::clicked, this, &AddSourceWidget::clearForm);
    connect(submitButton, &QPushButton::clicked, this, &AddSourceWidget::submitForm);
}

void AddSourceWidget::clearForm() {
    nameInput->clear();
    urlInput->clear();
    typeSelect->setCurrentIndex(0);
}

void AddSourceWidget::submitForm() {
    formMessage->clearMessage();
    manageButton(true);

    QString name = nameInput->text().trimmed();
    QString url = urlInput->text().trimmed();
    QString type = typeSelect->currentText();

    if (name.isEmpty() || url.isEmpty() || type == "-----") {
        formMessage->setMessage("Please compile all the inputs", MessageType::Fail);
        manageButton(false);
        return;
    }

    if (!QUrl(url).isValid()) {
        formMessage->setMessage("The URL inserted is not valid", MessageType::Fail);
        manageButton(false);
        return;
    }

    formMessage->manageSpinner(true);
}

void AddSourceWidget::manageButton(bool disable) {
    clearButton->setDisabled(disable);
    submitButton->setDisabled(disable);
}
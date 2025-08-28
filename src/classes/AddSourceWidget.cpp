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

    WidgetHelper::SetBackgroundColour(*this);

    connect(clearButton, &QPushButton::clicked, this, &AddSourceWidget::clearForm);
    connect(submitButton, &QPushButton::clicked, this, &AddSourceWidget::submitForm);

    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() != QNetworkReply::NoError) {
            formMessage->manageSpinner(false);
            formMessage->setMessage("The source was not found", MessageType::Fail);
            disableInputs(false);
            reply->deleteLater();
            return;
        }

        bool success = DatabaseManager::instance().addSource(
            nameInput->text().trimmed(),
            urlInput->text().trimmed(),
            typeSelect->currentText()
        );
        formMessage->manageSpinner(false);
        if (success) {
            formMessage->setMessage("Source added successfully", MessageType::Success);
        } else {
            formMessage->setMessage("Failed to add source", MessageType::Fail);
        }

        disableInputs(false);
        reply->deleteLater();
    });
}

void AddSourceWidget::clearForm() {
    nameInput->clear();
    urlInput->clear();
    typeSelect->setCurrentIndex(0);
    formMessage->clearMessage();
}

void AddSourceWidget::submitForm() {
    formMessage->clearMessage();
    disableInputs(true);

    QString name = nameInput->text().trimmed();
    QString url = urlInput->text().trimmed();
    QString type = typeSelect->currentText();

    if (name.isEmpty() || url.isEmpty() || type == "-----") {
        formMessage->setMessage("Please compile all the inputs", MessageType::Fail);
        disableInputs(false);
        return;
    }

    QUrl urlValue(url.trimmed());

    if (!urlValue.isValid() || urlValue.scheme().isEmpty()) {
        formMessage->setMessage("The URL inserted is not valid", MessageType::Fail);
        disableInputs(false);
        return;
    }

    formMessage->manageSpinner(true);

    QNetworkRequest request(urlValue);
    manager->get(request);
}

void AddSourceWidget::disableInputs(bool disable) {
    nameInput->setDisabled(disable);
    urlInput->setDisabled(disable);
    typeSelect->setDisabled(disable);
    clearButton->setDisabled(disable);
    submitButton->setDisabled(disable);
}
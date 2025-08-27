#include "AddSourceWidget.h"

AddSourceWidget::AddSourceWidget(QWidget* parent) {
    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout;
    buttonLine = new QHBoxLayout;

    nameInput = new QLineEdit(this);
    urlInput = new QLineEdit(this);
    typeSelect = new QComboBox(this);
    clearButton = new QPushButton("Cancel", this);
    submitButton = new QPushButton("Add", this);

    typeSelect->addItems({"-----", "Blog", "Youtube channel", "Patreon"});

    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("URL:", urlInput);
    formLayout->addRow("Type:", typeSelect);
    buttonLine->addWidget(clearButton);
    buttonLine->addWidget(submitButton);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLine);
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
}
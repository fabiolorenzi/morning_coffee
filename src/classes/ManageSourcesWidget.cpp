#include "ManageSourcesWidget.h"

ManageSourcesWidget::ManageSourcesWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    table = new QTableWidget(this);

    setupTable();
    loadSources();

    layout->addWidget(table);
    setLayout(layout);
}

void ManageSourcesWidget::refreshSources() {
    loadSources();
}

void ManageSourcesWidget::setupTable() {
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID", "Name", "Type", "URL", "Actions"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setColumnHidden(0, true);
}

void ManageSourcesWidget::loadSources() {
    table->setRowCount(0);
    auto sources = DatabaseManager::instance().getAllSources();

    for (int i = 0; i < sources.size(); ++i) {
        table->insertRow(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(sources[i]["id"].toInt())));
        table->setItem(i, 1, new QTableWidgetItem(sources[i]["name"].toString()));
        table->setItem(i, 2, new QTableWidgetItem(sources[i]["type"].toString()));
        table->setItem(i, 3, new QTableWidgetItem(sources[i]["url"].toString()));

        QWidget* actionWidget = new QWidget();
        QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
        actionLayout->setContentsMargins(0, 0, 0, 0);
        Button* updateButton = new Button("Update", ButtonType::Primary, actionWidget);
        Button* removeButton = new Button("Remove", ButtonType::Secondary, actionWidget);

        actionLayout->addWidget(updateButton);
        actionLayout->addWidget(removeButton);
        actionWidget->setLayout(actionLayout);
        table->setCellWidget(i, 4, actionWidget);

        int id = sources[i]["id"].toInt();
        connect(updateButton, &Button::clicked, this, [=]() {handleUpdate(id);});
        connect(removeButton, &Button::clicked, this, [=]() {handleRemove(id);});
    }
}

void ManageSourcesWidget::handleUpdate(int id) {
    QVariantMap source = DatabaseManager::instance().getSourceById(id);
    if (source.isEmpty()) return;

    bool ok;
    QString newName = QInputDialog::getText(this, "Update source", "Enter new name:", QLineEdit::Normal, source["name"].toString(), &ok);
    if (!ok || newName.isEmpty()) return;
    QString newUrl = QInputDialog::getText(this, "Update source", "Enter new URL:", QLineEdit::Normal, source["url"].toString(), &ok);
    if (!ok || newUrl.isEmpty()) return;
    QString newType = QInputDialog::getItem(this, "Update source", "Select type:", {"Blog", "YouTube channel", "Patreon"}, 0, false, &ok);
    if (!ok || newType.isEmpty()) return;

    if (DatabaseManager::instance().updateSource(id, newName, newUrl, newType)) {
        QMessageBox::information(this, "Success", "Source updated");
        loadSources();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update source");
    }
}

void ManageSourcesWidget::handleRemove(int id) {
    auto reply = QMessageBox::question(this, "Remove source", "Are you sure?");
    if (reply == QMessageBox::Yes) {
        if (DatabaseManager::instance().removeSource(id)) {
            QMessageBox::information(this, "Removed", "Source removed successfully");
            loadSources();
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove source");
        }
    }
}
#pragma once

#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "Button.h"
#include "DatabaseManager.h"

class ManageSourcesWidget : public QWidget {
    Q_OBJECT

    public:
        explicit ManageSourcesWidget(QWidget* parent = nullptr);
        void refreshSources();

    private slots:
        void loadSources();
        void handleUpdate(int id);
        void handleRemove(int id);

    private:
        QVBoxLayout* layout;
        QTableWidget* table;

        void setupTable();
};
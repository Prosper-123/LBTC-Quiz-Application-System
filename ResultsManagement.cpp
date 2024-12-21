#include "ResultsManagement.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>

ResultsManagement::ResultsManagement(QWidget *parent) : QWidget(parent), score(0), totalQuestions(0)
{

    setScore(12, 20);

    // Initialize the UI
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    resultTable = new QTableWidget(5, 3, this);  // 5 rows, 3 columns
    resultTable->setHorizontalHeaderLabels({"Score", "Total Questions", "Percentage"});
    resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Adjust header
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resultTable->verticalHeader()->setVisible(false);

    // Populate the table with data for 5 quizzes
    populateTable();

    // Create buttons for adding, editing, and deleting results
    QPushButton *addButton = new QPushButton("Add Result", this);
    QPushButton *editButton = new QPushButton("Edit Result", this);
    QPushButton *deleteButton = new QPushButton("Delete Result", this);

    connect(addButton, &QPushButton::clicked, this, &ResultsManagement::addResult);
    connect(editButton, &QPushButton::clicked, this, &ResultsManagement::editResult);
    connect(deleteButton, &QPushButton::clicked, this, &ResultsManagement::deleteResult);

    // Layout for buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    // Add table and buttons to main layout
    mainLayout->addWidget(resultTable);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

ResultsManagement::~ResultsManagement()
{
}

void ResultsManagement::setScore(int score, int totalQuestions)
{
    this->score = score;
    this->totalQuestions = totalQuestions;
}

void ResultsManagement::populateTable()
{

    for (int i = 0; i < 5; ++i) {
        resultTable->setItem(i, 0, new QTableWidgetItem(QString::number(score + i)));  // Increment score for each row
        resultTable->setItem(i, 1, new QTableWidgetItem(QString::number(totalQuestions))); // Same total questions for each row
        resultTable->setItem(i, 2, new QTableWidgetItem(QString::number((static_cast<double>(score + i) / totalQuestions) * 100) + "%"));
    }
}

void ResultsManagement::addResult()
{
    // Ask for new score and total questions via input dialog
    bool ok;
    int newScore = QInputDialog::getInt(this, "Add Result", "Enter score:", 0, 0, totalQuestions, 1, &ok);
    if (!ok) return;

    int newTotalQuestions = QInputDialog::getInt(this, "Add Result", "Enter total questions:", totalQuestions, 1, 100, 1, &ok);
    if (!ok) return;

    // Add a new row to the table
    int row = resultTable->rowCount();
    resultTable->insertRow(row);

    resultTable->setItem(row, 0, new QTableWidgetItem(QString::number(newScore)));
    resultTable->setItem(row, 1, new QTableWidgetItem(QString::number(newTotalQuestions)));
    resultTable->setItem(row, 2, new QTableWidgetItem(QString::number((static_cast<double>(newScore) / newTotalQuestions) * 100) + "%"));
}

void ResultsManagement::editResult()
{
    // Get selected row
    int row = resultTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Edit Result", "Please select a result to edit.");
        return;
    }

    // Ask for new score and total questions via input dialog
    bool ok;
    int newScore = QInputDialog::getInt(this, "Edit Result", "Enter new score:", 0, 0, totalQuestions, 1, &ok);
    if (!ok) return;

    int newTotalQuestions = QInputDialog::getInt(this, "Edit Result", "Enter new total questions:", totalQuestions, 1, 100, 1, &ok);
    if (!ok) return;

    // Update the selected row with the new values
    resultTable->setItem(row, 0, new QTableWidgetItem(QString::number(newScore)));
    resultTable->setItem(row, 1, new QTableWidgetItem(QString::number(newTotalQuestions)));
    resultTable->setItem(row, 2, new QTableWidgetItem(QString::number((static_cast<double>(newScore) / newTotalQuestions) * 100) + "%"));
}

void ResultsManagement::deleteResult()
{
    // Get selected row
    int row = resultTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Delete Result", "Please select a result to delete.");
        return;
    }

    // Confirm deletion
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Result", "Are you sure you want to delete this result?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        resultTable->removeRow(row);  // Remove the selected row
    }
}

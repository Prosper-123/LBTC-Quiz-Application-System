#include "UserManagement.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QLabel>

UserManagement::UserManagement(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("User Management");
    resize(600, 400);

    // Setup UI components
    setupUI();

    // Adding some dummy users for testing
    users.append({"admin", "Administrator", "Active"});
    users.append({"lecturer1", "Lecturer", "Active"});
    users.append({"student1", "Student", "Active"});

    // Update table to display users
    updateTable();
}

UserManagement::~UserManagement()
{
}

void UserManagement::setupUI()
{
    // Title at the top of the window
    QLabel *titleLabel = new QLabel("User Management", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50; margin-bottom: 20px;");

    // Table setup
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"Username", "Role", "Status"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false); // Hide vertical header
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make table read-only
    tableWidget->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; background-color: #f9f9f9;");

    // Buttons setup
    addButton = new QPushButton("Add User", this);
    editButton = new QPushButton("Edit User", this);
    deleteButton = new QPushButton("Delete User", this);

    // Button style for better appearance
    addButton->setStyleSheet("background-color: #27AE60; color: white; padding: 8px 16px; border-radius: 5px;");
    editButton->setStyleSheet("background-color: #F39C12; color: white; padding: 8px 16px; border-radius: 5px;");
    deleteButton->setStyleSheet("background-color: #E74C3C; color: white; padding: 8px 16px; border-radius: 5px;");

    // Connect button actions to respective slots
    connect(addButton, &QPushButton::clicked, this, &UserManagement::addUser);
    connect(editButton, &QPushButton::clicked, this, &UserManagement::editUser);
    connect(deleteButton, &QPushButton::clicked, this, &UserManagement::deleteUser);

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);  // Add title at the top
    mainLayout->addWidget(tableWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    buttonLayout->setSpacing(20);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Additional styling for the dialog
    setStyleSheet("background-color: #ecf0f1; padding: 20px;");
}

void UserManagement::updateTable()
{
    tableWidget->setRowCount(users.size());
    for (int i = 0; i < users.size(); ++i) {
        const User &user = users[i];
        tableWidget->setItem(i, 0, new QTableWidgetItem(user.username));
        tableWidget->setItem(i, 1, new QTableWidgetItem(user.role));
        tableWidget->setItem(i, 2, new QTableWidgetItem(user.status));
    }
}

void UserManagement::addUser()
{
    // Get user details from the user
    bool ok;
    QString username = QInputDialog::getText(this, "Add User", "Enter Username:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) return;

    QString role = QInputDialog::getText(this, "Add User", "Enter Role (e.g., Student, Lecturer):", QLineEdit::Normal, "", &ok);
    if (!ok || role.isEmpty()) return;

    QString status = QInputDialog::getText(this, "Add User", "Enter Status (Active/Inactive):", QLineEdit::Normal, "", &ok);
    if (!ok || status.isEmpty()) return;

    // Add the new user to the list
    users.append({username, role, status});
    updateTable();  // Update the table to reflect changes
}

void UserManagement::editUser()
{
    // Get the selected row
    int row = tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Edit Error", "Please select a user to edit.");
        return;
    }

    // Get the current user details
    QString oldUsername = tableWidget->item(row, 0)->text();
    QString oldRole = tableWidget->item(row, 1)->text();
    QString oldStatus = tableWidget->item(row, 2)->text();

    // Get new details from the user
    bool ok;
    QString username = QInputDialog::getText(this, "Edit User", "Edit Username:", QLineEdit::Normal, oldUsername, &ok);
    if (!ok || username.isEmpty()) return;

    QString role = QInputDialog::getText(this, "Edit User", "Edit Role (e.g., Student, Lecturer):", QLineEdit::Normal, oldRole, &ok);
    if (!ok || role.isEmpty()) return;

    QString status = QInputDialog::getText(this, "Edit User", "Edit Status (Active/Inactive):", QLineEdit::Normal, oldStatus, &ok);
    if (!ok || status.isEmpty()) return;

    // Update the user in the list
    users[row] = {username, role, status};
    updateTable();
}

void UserManagement::deleteUser()
{
    // Get the selected row
    int row = tableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Delete Error", "Please select a user to delete.");
        return;
    }

    // Confirm deletion
    if (QMessageBox::question(this, "Delete User", "Are you sure you want to delete this user?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        // Remove the user from the list
        users.removeAt(row);
        updateTable();
    }
}

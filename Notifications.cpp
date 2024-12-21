#include "Notifications.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>

Notifications::Notifications(QWidget *parent) : QWidget(parent)
{
    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create the QListWidget to display notifications
    notificationListWidget = new QListWidget(this);
    layout->addWidget(notificationListWidget);

    // Create an input field for a new notification
    newNotificationLineEdit = new QLineEdit(this);
    newNotificationLineEdit->setPlaceholderText("Enter new notification...");
    layout->addWidget(newNotificationLineEdit);

    // Create the buttons
    addButton = new QPushButton("Add Notification", this);
    deleteButton = new QPushButton("Delete Notification", this);
    readButton = new QPushButton("Read Notification", this);

    // Add buttons to the layout
    layout->addWidget(addButton);
    layout->addWidget(deleteButton);
    layout->addWidget(readButton);

    // Connect the buttons to their slots
    connect(addButton, &QPushButton::clicked, this, &Notifications::addNotification);
    connect(deleteButton, &QPushButton::clicked, this, &Notifications::deleteNotification);
    connect(readButton, &QPushButton::clicked, this, &Notifications::readNotification);

    setLayout(layout);
}

Notifications::~Notifications()
{
}

void Notifications::showNotification()
{
    // Show a message box for the notification
    QMessageBox::information(this, "Notification", "This is a sample notification.");
}

void Notifications::addNotification()
{
    QString notificationText = newNotificationLineEdit->text();
    if (!notificationText.isEmpty()) {
        // Add notification to the list and clear the input field
        notifications.append(notificationText);
        notificationListWidget->addItem(notificationText);
        newNotificationLineEdit->clear();
    }
}

void Notifications::deleteNotification()
{
    // Get the selected item and delete it
    QListWidgetItem *selectedItem = notificationListWidget->currentItem();
    if (selectedItem) {
        delete selectedItem;
    }
}

void Notifications::readNotification()
{
    // Get the selected item and display its content
    QListWidgetItem *selectedItem = notificationListWidget->currentItem();
    if (selectedItem) {
        QMessageBox::information(this, "Read Notification", selectedItem->text());
    }
}

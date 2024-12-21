#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QStringList>

class Notifications : public QWidget
{
    Q_OBJECT

public:
    explicit Notifications(QWidget *parent = nullptr);
    ~Notifications();

private slots:
    void showNotification();
    void addNotification();
    void deleteNotification();
    void readNotification();

private:
    QPushButton *addButton;  // Button to add new notifications
    QPushButton *deleteButton;  // Button to delete selected notification
    QPushButton *readButton;  // Button to read selected notification
    QLineEdit *newNotificationLineEdit;  // Input for new notification text
    QListWidget *notificationListWidget;  // List to display notifications
    QStringList notifications; // To store the list of notifications
};

#endif // NOTIFICATIONS_H

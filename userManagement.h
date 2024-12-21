#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVector>

struct User {
    QString username;
    QString role;
    QString status;
};

class UserManagement : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagement(QWidget *parent = nullptr);
    ~UserManagement();

private slots:
    void addUser();
    void editUser();
    void deleteUser();

private:
    void setupUI();
    void updateTable();

    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QLineEdit *usernameLineEdit;
    QLineEdit *roleLineEdit;
    QLineEdit *statusLineEdit;

    QVector<User> users;  // List of users
};

#endif // USERMANAGEMENT_H

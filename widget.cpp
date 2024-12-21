#include "widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include <QSpacerItem>
#include <QStyle>

Widget::Widget(QWidget *parent)
    : QWidget(parent), dashboard(new Dashboard(this))
{
    setWindowTitle("Quiz Management System - Login");
    resize(800, 600);

    setStyleSheet("QWidget {"
                  "background-image: url(':/images/background.jpg');"
                  "background-repeat: no-repeat;"
                  "background-position: center;"
                  "background-size: cover;"
                  "font-family: Arial, sans-serif;"
                  "font-size: 14px;"
                  "color: #333;}"
                  "QLineEdit, QComboBox {"
                  "padding: 8px;"
                  "border: 1px solid #ccc;"
                  "border-radius: 4px;"
                  "background: #fff;}"
                  "QPushButton {"
                  "padding: 10px 15px;"
                  "background-color: #007bff;"
                  "color: white;"
                  "border: none;"
                  "border-radius: 4px;"
                  "font-weight: bold;}"
                  "QPushButton:hover {"
                  "background-color: #0056b3;}"
                  "QLabel {"
                  "margin-bottom: 10px;}"
                  ".form-container {"
                  "background-color: rgba(255, 255, 255, 0.8);"
                  "padding: 20px;"
                  "border-radius: 8px;"
                  "box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);}");

    // Main container for the login form
    QWidget *formContainer = new QWidget(this);
    formContainer->setObjectName("form-container");

    QLabel *welcomeLabel = new QLabel("Welcome to LBTC Educational Quiz System", formContainer);
    welcomeLabel->setStyleSheet("color: blue; font-size: 18px; font-weight: bold; text-align: center;");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setAlignment(Qt::AlignTop);

    // Add spacer to push the welcome label upwards
    QSpacerItem *topSpacer = new QSpacerItem(0, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Username field
    QLabel *usernameLabel = new QLabel("Username:", formContainer);
    usernameInput = new QLineEdit(formContainer);

    // Password field
    QLabel *passwordLabel = new QLabel("Password:", formContainer);
    passwordInput = new QLineEdit(formContainer);
    passwordInput->setEchoMode(QLineEdit::Password);

    // Role selection
    QLabel *roleLabel = new QLabel("Login as:", formContainer);
    roleComboBox = new QComboBox(formContainer);
    roleComboBox->addItem("Lecturer");
    roleComboBox->addItem("Student");

    // Login button
    loginButton = new QPushButton("Login", formContainer);
    connect(loginButton, &QPushButton::clicked, this, &Widget::handleLogin);

    // Layout for the form
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->setSpacing(10);
    formLayout->addItem(topSpacer);
    formLayout->addWidget(welcomeLabel);
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(usernameInput);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordInput);
    formLayout->addWidget(roleLabel);
    formLayout->addWidget(roleComboBox);
    formLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    formContainer->setLayout(formLayout);

    // Center the form on the screen
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(formContainer, 0, Qt::AlignCenter);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

Widget::~Widget()
{
    delete dashboard;
}

void Widget::handleLogin()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    QString role = roleComboBox->currentText();

    if (role == "Lecturer" && username == "Lecturer" && password == "Lecturer123") {
        dashboard->exec();
    } else if (role == "Student" && username == "Student" && password == "Student123") {
        QMessageBox::information(this, "Login Successful", "Welcome, Student!");
        dashboard->exec();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username, password, or role.");
    }
}

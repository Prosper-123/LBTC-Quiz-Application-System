#include "Dashboard.h"
#include "userManagement.h"
#include "QuizManagement.h"
#include "ResultsManagement.h"
#include "Notifications.h"

#include <QVBoxLayout>
#include <QLabel>

Dashboard::Dashboard(QWidget *parent)
    : QDialog(parent), menuList(new QListWidget(this)), contentArea(new QStackedWidget(this))
{
    setWindowTitle("Dashboard - Lusaka Business Quiz Management System ");
    resize(800, 600);

    // Set up side menu and content area
    setupMenu();
    setupContent();

    // Layout for the dashboard
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(menuList, 1);
    mainLayout->addWidget(contentArea, 3);

    setLayout(mainLayout);
}

void Dashboard::setupMenu()
{
    // Add features to the side menu
    menuList->addItem("User Management");
    menuList->addItem("Quiz Management");
    menuList->addItem("Results Management");
    menuList->addItem("Notifications");
    menuList->addItem("Theme and UI Customization");
    menuList->addItem("Language and Localization");
    menuList->addItem("Backup and Restore");

    // Connect menu selection to the content area
    connect(menuList, &QListWidget::currentRowChanged, contentArea, &QStackedWidget::setCurrentIndex);
}

void Dashboard::setupContent()
{
    // Add content widgets
    UserManagement *userManagementPage = new UserManagement(this);
    contentArea->addWidget(userManagementPage);

    QuizManagement *quizManagementPage = new QuizManagement(this);
    contentArea->addWidget(quizManagementPage);

    ResultsManagement *resultsManagementPage = new ResultsManagement(this);
    contentArea->addWidget(resultsManagementPage);

    Notifications *notificationPage = new Notifications(this);
    contentArea->addWidget(notificationPage);

}

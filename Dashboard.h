#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QStackedWidget>
#include <QListWidget>

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);

private:
    QListWidget *menuList;
    QStackedWidget *contentArea;

    void setupMenu();
    void setupContent();
};

#endif // DASHBOARD_H

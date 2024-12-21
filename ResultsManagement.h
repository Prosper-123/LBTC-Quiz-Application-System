#ifndef RESULTSMANAGEMENT_H
#define RESULTSMANAGEMENT_H

#include <QWidget>

class QTableWidget;
class QPushButton;

class ResultsManagement : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsManagement(QWidget *parent = nullptr);
    ~ResultsManagement();

    void setScore(int score, int totalQuestions);  // Setter for score and total questions
    void populateTable();  // Populate the table with results

private slots:
    void addResult();  // Slot to handle adding a new result
    void editResult();  // Slot to handle editing an existing result
    void deleteResult();  // Slot to handle deleting a result

private:
    QTableWidget *resultTable;  // Table to display results
    int score;  // Score for the quiz
    int totalQuestions;  // Total number of questions in the quiz
};

#endif // RESULTSMANAGEMENT_H

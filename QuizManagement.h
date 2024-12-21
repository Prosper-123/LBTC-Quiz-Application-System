#ifndef QUIZMANAGEMENT_H
#define QUIZMANAGEMENT_H

#include <QDialog>
#include <QTimer>
#include <QStringList>

class QVBoxLayout;
class QLabel;
class QRadioButton;
class QPushButton;

class QuizManagement : public QDialog
{
    Q_OBJECT

public:
    explicit QuizManagement(QWidget *parent = nullptr);
    ~QuizManagement();

private slots:
    void nextQuestion();
    void showResult();
    void updateTimer();

private:
    void setupUI();
    void setupQuestions();
    void loadQuestion();
    void checkAnswer();
    void resetQuiz();

    QLabel *titleLabel;
    QLabel *questionLabel;
    QRadioButton *option1Button;
    QRadioButton *option2Button;
    QRadioButton *option3Button;
    QRadioButton *option4Button;
    QPushButton *nextButton;
    QPushButton *submitButton;

    QTimer *timer;
    int currentQuestion;
    int correctAnswers;
    int totalTime;  // Timer duration in seconds

    QStringList questions;
    QStringList difficultyLevels;  // Difficulty levels for each question
    QList<QStringList> options;  // Options for each question
    QList<int> correctOptionIndexes;  // Index of correct options for each question
};

#endif // QUIZMANAGEMENT_H

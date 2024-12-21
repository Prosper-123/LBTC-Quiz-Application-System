#include "QuizManagement.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

QuizManagement::QuizManagement(QWidget *parent)
    : QDialog(parent), currentQuestion(0), correctAnswers(0), totalTime(120)  // 2 minutes timer
{
    setWindowTitle("Communication Quiz");
    resize(500, 350);

    // Setup UI components
    setupUI();
    setupQuestions();
    loadQuestion();

    // Timer setup
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QuizManagement::updateTimer);
    timer->start(1000);  // Update timer every second
}

QuizManagement::~QuizManagement()
{
    delete timer;
}

void QuizManagement::setupUI()
{
    // Title Label
    titleLabel = new QLabel("Communication Quiz", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #2e3b4e; padding: 20px;");

    // Question Label
    questionLabel = new QLabel("Question will appear here", this);
    questionLabel->setWordWrap(true);
    questionLabel->setStyleSheet("font-size: 16px; color: #333;");

    // Options Buttons
    option1Button = new QRadioButton("Option 1", this);
    option2Button = new QRadioButton("Option 2", this);
    option3Button = new QRadioButton("Option 3", this);
    option4Button = new QRadioButton("Option 4", this);

    // Buttons
    nextButton = new QPushButton("Next", this);
    submitButton = new QPushButton("Submit", this);
    submitButton->setEnabled(false); // Initially disabled, enabled after the last question

    // Connect signals to slots
    connect(nextButton, &QPushButton::clicked, this, &QuizManagement::nextQuestion);
    connect(submitButton, &QPushButton::clicked, this, &QuizManagement::showResult);

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(questionLabel);
    mainLayout->addWidget(option1Button);
    mainLayout->addWidget(option2Button);
    mainLayout->addWidget(option3Button);
    mainLayout->addWidget(option4Button);
    mainLayout->addWidget(nextButton);
    mainLayout->addWidget(submitButton);

    setLayout(mainLayout);
}

void QuizManagement::setupQuestions()
{
    // Add 20 questions, difficulty levels, and options
    questions << "What is the main purpose of communication?"
              << "Which type of communication involves face-to-face interaction?"
              << "Which one is an example of non-verbal communication?"
              << "How can effective communication impact relationships?"
              << "What is the role of body language in communication?"
              << "What is the importance of active listening?"
              << "How can feedback improve communication?"
              << "What is the difference between verbal and non-verbal communication?"
              << "What is the importance of tone in communication?"
              << "Why is it important to be clear and concise when communicating?"
              << "How does culture influence communication?"
              << "What is the difference between hearing and listening?"
              << "Why is empathy important in communication?"
              << "What are barriers to effective communication?"
              << "How can communication skills be improved?"
              << "What are the types of communication?"
              << "How does effective communication affect teamwork?"
              << "What role does trust play in communication?"
              << "What is the importance of open-ended questions in communication?"
              << "Why should communication be adapted to the audience?";

    // Difficulty levels for each question
    difficultyLevels << "Easy" << "Medium" << "Medium" << "Easy" << "Medium"
                     << "Medium" << "Medium" << "Hard" << "Medium" << "Hard"
                     << "Medium" << "Easy" << "Medium" << "Hard" << "Medium"
                     << "Easy" << "Medium" << "Hard" << "Hard" << "Easy";

    // Define options for each question
    options << QStringList{"To inform", "To persuade", "To entertain", "To communicate"}
            << QStringList{"Verbal communication", "Non-verbal communication", "Written communication", "Face-to-face communication"}
            << QStringList{"Speech", "Body language", "Texting", "Email"}
            << QStringList{"Improve understanding", "Increase conflict", "Create confusion", "Reduce clarity"}
            << QStringList{"Makes communication unclear", "Enhances the message", "Has no effect", "Distracts from communication"}
            << QStringList{"Listening without judgment", "Speaking while listening", "Ignoring the speaker", "Talking over the speaker"}
            << QStringList{"Clarifies understanding", "Increases misunderstanding", "Interrupts conversation", "Decreases clarity"}
            << QStringList{"Verbal is spoken; non-verbal is physical", "Verbal involves text", "Non-verbal involves audio", "They are the same"}
            << QStringList{"It emphasizes the message", "It has no effect", "It confuses the message", "It distracts the listener"}
            << QStringList{"Helps to explain ideas", "Makes the message vague", "Confuses the receiver", "Creates misunderstanding"}
            << QStringList{"Affects verbal communication", "Makes no difference", "Improves relationships", "None of the above"}
            << QStringList{"Hearing involves sound; listening involves understanding", "They are the same", "Hearing is voluntary", "Listening is involuntary"}
            << QStringList{"It helps understand others' feelings", "It makes you agree with others", "It encourages disputes", "It confuses the message"}
            << QStringList{"Language barriers", "Lack of time", "Listening barriers", "All of the above"}
            << QStringList{"By practicing", "By ignoring feedback", "By talking more", "By avoiding conflict"}
            << QStringList{"Verbal, non-verbal, written, and visual", "Only verbal", "Non-verbal only", "Written only"}
            << QStringList{"It increases productivity", "It causes delays", "It creates misunderstandings", "It doesn't matter"}
            << QStringList{"It makes conversations shorter", "It improves mutual respect", "It breaks trust", "It doesn't matter"}
            << QStringList{"To ask for more details", "To challenge the speaker", "To end the conversation", "To get a yes/no answer"}
            << QStringList{"It helps in creating personal connections", "It creates confusion", "It stops communication", "It makes no difference"};

    // Correct answer indices (0-based index)
    correctOptionIndexes << 0 << 3 << 1 << 0 << 1 << 0 << 0 << 0 << 0 << 0
                         << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;

    // Make sure the questions and options are paired correctly
    if (questions.size() != options.size() || questions.size() != difficultyLevels.size()) {
        QMessageBox::critical(this, "Error", "Mismatch in questions, options, or difficulty levels!");
        return;
    }
}

void QuizManagement::loadQuestion()
{
    // Check bounds before loading the question
    if (currentQuestion >= questions.size()) {
        submitButton->setEnabled(true); // Enable the submit button after the last question
        nextButton->setEnabled(false);  // Disable the next button
        return;
    }

    // Display the current question and corresponding options
    questionLabel->setText(questions[currentQuestion] + " (" + difficultyLevels[currentQuestion] + ")");

    // Set options dynamically based on the current question's options
    option1Button->setText("Option 1: " + options[currentQuestion][0]);
    option2Button->setText("Option 2: " + options[currentQuestion][1]);
    option3Button->setText("Option 3: " + options[currentQuestion][2]);
    option4Button->setText("Option 4: " + options[currentQuestion][3]);

    // Uncheck the options
    option1Button->setChecked(false);
    option2Button->setChecked(false);
    option3Button->setChecked(false);
    option4Button->setChecked(false);
}

void QuizManagement::nextQuestion()
{
    checkAnswer();  // Check if the selected answer is correct

    // Move to the next question
    currentQuestion++;
    loadQuestion();
}

void QuizManagement::checkAnswer()
{
    int selectedOption = -1;
    if (option1Button->isChecked()) selectedOption = 0;
    else if (option2Button->isChecked()) selectedOption = 1;
    else if (option3Button->isChecked()) selectedOption = 2;
    else if (option4Button->isChecked()) selectedOption = 3;

    // Check if the selected answer is correct
    if (selectedOption == correctOptionIndexes[currentQuestion]) {
        correctAnswers++;
    }
}

void QuizManagement::showResult()
{
    QMessageBox::information(this, "Quiz Completed", "You scored " + QString::number(correctAnswers) + " out of " + QString::number(questions.size()));
}

void QuizManagement::updateTimer()
{
    if (totalTime > 0) {
        totalTime--;
    } else {
        timer->stop();
        QMessageBox::information(this, "Time's Up", "Time is up! The quiz is over.");
        showResult();
    }
}

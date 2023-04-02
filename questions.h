#ifndef QUESTIONS_H
#define QUESTIONS_H
#include <QString>
#include <QVector>
#include <QDebug>



class Questions
{
public:
    Questions();
    void addQuestionHeading(QString heading);
    void addQuestion(QString basic, QString advanced);
    QVector<QString> getQuestions();
    QVector<QString> getQuestionsHeadings();
    QVector<QString> getQuestionsWithHeadings();
private:
    QVector<QString> questions;
    QVector<QString> questionsHeadings;
};

#endif // QUESTIONS_H

#include "questions.h"
Questions::Questions()
{

}

void Questions::addQuestionHeading(QString heading)
{
    questionsHeadings.push_back(heading);
}

void Questions::addQuestion(QString basic, QString advanced)
{

    questions.push_back(basic + advanced);
}

QVector<QString> Questions::getQuestions()
{
    return questions;
}

QVector<QString> Questions::getQuestionsHeadings()
{
    return questionsHeadings;
}

QVector<QString> Questions::getQuestionsWithHeadings()
{
    QVector<QString> questionsWithHeadings;
    for(int i=0;i<questionsHeadings.size();i++){
        questionsWithHeadings.push_back(QString("<span style=\"font-weight: bold;\">%1</span>").arg(questionsHeadings.at(i)) + "<br>" + questions.at(i));
    }
    return questionsWithHeadings;
}

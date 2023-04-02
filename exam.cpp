#include "exam.h"
Exam::Exam(Student *exStu,QVector<Questions> questions, int numberOfUnits)
{
    if(examinedStudent == nullptr && questions.size() > 0)
    {
        examinedStudent = exStu;
        questionsWithHeading = questions;
        unitsNumber = numberOfUnits;
    }
}

Exam::~Exam()
{
    if(examinedStudent != nullptr)
    examinedStudent = nullptr;

}

void Exam::checkExlusionFromQuestion()
{
    for(int i=currentUnit;i<questionsWithHeading.size();i++){
        if(examinedStudent->getGrade(i).toDouble() >= 5.5){
              examinedStudentGrades.push_back(5.0);
              goToNextUnit();
        } else {
            break;
        }
    }
}

double Exam::checkAverageGrade()
{
    double avg =0.0;
    for(int i=0;i<examinedStudentGrades.size();i++)
    {
        avg+=examinedStudentGrades[i];
    }
    return (avg/examinedStudentGrades.size());
}

QString Exam::getUnitName()
{
    if(examinedStudent->getGrade(currentUnit).toDouble() >= 5.5){
          return "BLOK " + QString::number(currentUnit + 2);
    }
    return "BLOK " + QString::number(currentUnit + 1);
}

 QString Exam::drawQuestion()
    {
        if(examinedStudent->getGrade(currentUnit).toDouble() >= 5.5){
           goToNextUnit();
        }
        QVector<QString> questionsFromUnit =  questionsWithHeading[currentUnit].getQuestionsWithHeadings();
        std::mt19937 mt(randomDevice());
        QString questions;
        if(examinedStudent->getGrade(currentUnit).toDouble() >= 3.5 && examinedStudent->getGrade(currentUnit).toDouble() < 4.5)
        {
            int notDrawnQuestionsNumber = questionsFromUnit.size();
            for(int i =0;i<2;i++)
            {
                std::uniform_int_distribution<int> ds(0, notDrawnQuestionsNumber - 1);
                int index = ds(mt);
                questions = questions +  "<br>" + questionsFromUnit.at(index) + "\n";
                std::swap(questionsFromUnit[index],questionsFromUnit[notDrawnQuestionsNumber - 1]);
                notDrawnQuestionsNumber--;
            }
        }
        else if(examinedStudent->getGrade(currentUnit).toDouble() >= 4.5)
        {
            int notDrawnQuestionsNumber = questionsFromUnit.size();
            for(int i =0;i<3;i++)
            {
                std::uniform_int_distribution<int> ds(0, notDrawnQuestionsNumber - 1);
                int index = ds(mt);
                questions = questions +  "<br>" + questionsFromUnit.at(index) + "\n";
                std::swap(questionsFromUnit[index],questionsFromUnit[notDrawnQuestionsNumber - 1]);
                notDrawnQuestionsNumber--;
            }
        }
        else
        {
            std::uniform_int_distribution<int> ds(0, questionsFromUnit.size() - 1);
            questions = questionsFromUnit.at(ds(mt));
        }
        goToNextUnit();
        return questions;
 }





void Exam::goToNextUnit()
{
    currentUnit++;
}

int Exam::getUnitNumber()
{
    return currentUnit;
}

bool Exam::checkExamEnd()
{

    if(currentUnit< questionsWithHeading.size()){
        for(int i=currentUnit;i<questionsWithHeading.size();i++){
            if(examinedStudent->getGrade(i).toDouble() < 5.5){
                return false;
                break;
            }
        }
        return true;
} else  return(currentUnit == questionsWithHeading.size());
}
void Exam::giveGrade(double ocena)
{
    examinedStudentGrades.push_back(ocena);
}

Student* Exam::getExaminedStudent()
{
    return examinedStudent;
}

QVector<double> Exam::getGrades()
{
    if(examinedStudentGrades.size() < unitsNumber){
        for(int i=examinedStudentGrades.size();i<unitsNumber;i++)
            examinedStudentGrades.push_back(5.0);
    }
    return examinedStudentGrades;
}

bool Exam::checkUnitPass()
{
    bool pass = true;
    for(int i=0;i<examinedStudentGrades.size();i++){
        if(examinedStudentGrades[i] <3.0)
        {
            pass = false;;
            break;
        }
    }
    return pass;
}

void Exam::end()
{
    for(int i=currentUnit;i<unitsNumber;i++){
      if(examinedStudent->getGrade(i).toDouble() < 5.5)
         examinedStudentGrades.push_back(2.0);
         else
           examinedStudentGrades.push_back(5.0);

    }
}


int Exam::getNumberOfPassedUnits()
{
    int numberOfPassedUnits = 0;
    for(int i=0;i<examinedStudentGrades.size();i++){
        if(examinedStudentGrades[i] >= 3.0)
        {
           numberOfPassedUnits++;
        }
    }
    return numberOfPassedUnits;
}



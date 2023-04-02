#include "MainApp.h"
#include "FileHandling.h"
#include <stdexcept>

MainApp::MainApp(QObject *parent)
    :QObject(parent) {}

MainApp::~MainApp()
{
    if(exam != nullptr)
    {
        delete exam;
        exam = nullptr;
    }
}

Student& MainApp::getStudent(int indexOfStudent)
{

    if(indexOfStudent >= 0 && indexOfStudent < students.size())
    return students[indexOfStudent];
    else throw std::invalid_argument("Bledny index");

}

QVector<Questions> MainApp::getQuestionsWithHeadings()
{
    return questions;
}

void MainApp::endExam()
{
    if(exam!=nullptr)
    {
        exam->end();
        if(exam->checkUnitPass()){
        emit writeOutStats(exam->getExaminedStudent()->getStudentDetails(),exam->checkAverageGrade(),exam->getGrades());
        }
        else{
         emit writeOutStats(exam->getExaminedStudent()->getStudentDetails(),exam->getNumberOfPassedUnits(),exam->getGrades());
        }
        delete exam;
        exam=nullptr;
    }

}
void MainApp::setGUI(MainWindow *ui) {GUI = ui;}
void MainApp::setStudents(QVector<Student> studentsToExam)
{
    if(students.isEmpty())
    {
        students = studentsToExam;
    }
    else {   
        students.clear();
        students = studentsToExam;
        emit claerStudents();
}
}
void MainApp::setQuestionsWithHeadings(QVector<Questions> examQuestions)
{
    if(questions.isEmpty())
        questions = examQuestions;
    else {
        questions.clear();
        questions = examQuestions;
        emit claerStudents();
    }
}

bool MainApp::checkLoadCorrectness()
{
    if(students.size() > 0 && questions.size() > 0)
    {
        emit examON();
        return true;
    }
    else
        return false;
}

void MainApp::startExam(Student& examinedStudent)
{

    if(exam == nullptr)
    {
        exam = new Exam(&examinedStudent,questions,questions.size());
    }
    exam->checkExlusionFromQuestion();
    emit showWarning("ROZPOCZĘTO EGZAMIN!","Zakonczenie egzaminu przed końcem spowoduje wpisanie w pozostałe bloki oceny 2.0");
    emit showUnits(exam->getUnitName());
    emit showQuestion(exam->drawQuestion());
    if(exam->checkExamEnd())
    {
    emit finishExam();
    }
}

void MainApp::moveToNextUnit()
{
    exam->checkExlusionFromQuestion();
    emit showUnits(exam->getUnitName());
    emit showQuestion(exam->drawQuestion());
    if(exam->checkExamEnd())
    {
    emit finishExam();
    }

}
int MainApp::getNumberOfStudents()
{
    return students.size();
}

int MainApp::getNumberOfUnits()
{
    return questions.size();
}

void MainApp::rateAnswer(double grade)
{
    exam->giveGrade(grade);
}

double MainApp::getGradesAverage()
{
    return exam->checkAverageGrade();
}

void MainApp::openFileWindow()
{
    FileHandling fileHandlingProgram(this);
    loadData = new LoadDataWindow(nullptr,&fileHandlingProgram);
    loadData->exec();


    delete loadData;
}

void MainApp::saveStudentResult(QVector<double> examGrades, QString studentPersonalDetails)
{
    FileHandling fileHandlingProgram(this);
    fileHandlingProgram.saveStudentExamGrade(examGrades,studentPersonalDetails, questions.size());
    fileHandlingProgram.saveToHTML(examGrades,studentPersonalDetails, questions.size());
}

void MainApp::chooseFilepath()
{
    FileHandling fileHandlingProgram(this);
    fileHandlingProgram.chooseFileToSave();
}


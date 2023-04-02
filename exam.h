#ifndef EXAM_H
#define EXAM_H
#include "student.h"
#include "questions.h"
#include "QRandomGenerator"
class Exam
{
public:
    Exam(Student* exStu, QVector<Questions> questions, int numberOfUnits);
    ~Exam();
    void checkExlusionFromQuestion();
    double checkAverageGrade();
    QString getUnitName();
    QString drawQuestion();
    void goToNextUnit();
    int getUnitNumber();
    bool checkExamEnd();
    void giveGrade(double ocena);
    Student *getExaminedStudent();
    QVector<double> getGrades();
    bool checkUnitPass();
    void end();
    int getNumberOfPassedUnits();
private:
    std::random_device randomDevice;
    int unitsNumber;
    int currentUnit=0;
    Student* examinedStudent = nullptr;
    QVector<Questions> questionsWithHeading;
    QVector<double> examinedStudentGrades;
};

#endif // EXAM_H

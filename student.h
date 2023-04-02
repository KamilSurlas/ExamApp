#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <exception>
#include <QVector>

class Student
{
private:
    QString studentName;
    QString studentSurname;
    QVector<double> grades;

public:
    void addGrade(double grade);
    int numberOfGrades();
    Student(QString name, QString surname);
    QString getStudentDetails() { return studentName + " " + studentSurname; }
    ~Student();
    QString getGrade(int index);
};

#endif // STUDENT_H

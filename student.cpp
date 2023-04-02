#include "student.h"
#include <stdexcept>


void Student::addGrade(double grade)
{ 
    grades.push_back(grade);
}

int Student::numberOfGrades()
{
    return grades.size();
}

Student::Student(QString name, QString surname)
    :studentName(name), studentSurname(surname)
{

}

Student::~Student()
{

}

QString Student::getGrade(int index)
{
    return QString::number(this->grades.at(index));
}




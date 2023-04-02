#ifndef OBSLUGAPLIKOW_H
#define OBSLUGAPLIKOW_H
#include <QFile>
#include "MainApp.h"

#include <QTextStream>
#include "student.h"
#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include "questions.h"
#include <QDebug>
#include <fstream>
class MainApp;
class LoadDataWindow;
class FileHandling : public QWidget
{
    Q_OBJECT
public:
    FileHandling(MainApp* mainApplication = nullptr);
    void loadStudents();
    void loadQuestions();
    void chooseQuestionsFilepath();
    void chooseStudentsFilepath();
    void chooseFileToSave();
    void saveStudentExamGrade(QVector<double> gradesFromExam, QString personalData, int numberOfUnits);
    void setGUI(LoadDataWindow *ui = nullptr){GUI=ui;}
    QVector<Questions> getUnits() { return units; }
    void saveToHTML(QVector<double> gradesFromExam, QString personalData, int numberOfUnits);
    QVector<Student> getStudenci() { return students; }
signals:

    void studentsLoaded(QString studentsFilepath);
    void questionsLoaded(QString questionsFilepath);
    void studentsLoaded(QVector<Student> students);
    void questionsLoaded(QVector<Questions> units);
private:
    void save(QVector<double> gradesFromExam, QString personalData, int numberOfUnits,QString filepath = saveFilepath);
    QString questionsFilepath;
    QString studentsFilepath;
    static QString saveFilepath;
    MainApp *mainApp = nullptr;
    LoadDataWindow *GUI = nullptr;
    QVector<Questions> units;
    QVector<Student> students;
};

#endif // OBSLUGAPLIKOW_H

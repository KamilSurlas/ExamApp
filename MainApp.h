#ifndef MAINAPP_H
#define MAINAPP_H
#include "exam.h"
#include "LoadDataWindow.h"
#include <QObject>
#include <QVector>
class LoadDataWindow;
class MainWindow;
class MainApp : public QObject
{
    Q_OBJECT
public:
    explicit MainApp(QObject *parent = nullptr);
    ~MainApp();
    void setGUI(MainWindow *ui = nullptr);
    Student& getStudent(int indexOfStudent);
    QVector<Questions> getQuestionsWithHeadings();
    void endExam();
    bool checkLoadCorrectness();
    void startExam(Student& examinedStudent);
    void moveToNextUnit();
    int getNumberOfStudents();
    int getNumberOfUnits();
    void rateAnswer(double grade);
    double getGradesAverage();
    void openFileWindow();
    void saveStudentResult(QVector<double> examGrades, QString studentPersonalDetails);
    void chooseFilepath();
private slots:
    void setStudents(QVector<Student> studentsToExam);
    void setQuestionsWithHeadings(QVector<Questions> examQuestions);
signals:
    void showWarning(QString warningHeading, QString warningContent);
    void writeOutStats(QString studentPersonalDetails, double examFinalGrade, QVector<double>  gradesFromUnits);
    void writeOutStats(QString studentPersonalDetails, int numberOfPassedUnits, QVector<double> gradesFromUnits);
    void claerStudents();
    void finishExam();
    void examON();
    void showUnits(QString unitName);
    void showQuestion(QString  question);
private:
    MainWindow *GUI = nullptr;
    LoadDataWindow *loadData = nullptr;
    Exam* exam = nullptr;
    QVector<Student> students;
    QVector<Questions> questions;
};

#endif // MAINAPP_H

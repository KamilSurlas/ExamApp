#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMessageBox>
#include "MainApp.h"
#include "ui_mainwindow.h"
#include "QVector"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainApp;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,MainApp* mainApplication = nullptr);
    ~MainWindow();
private slots:
    void on_examFinish_OK();
    void on_loadButton_clicked();
    void on_examStart_clicked();
    void on_finishExam_clicked();
    void on_studentList_activated(int index);
    void on_next_clicked();
    void on_unitSelected_OK(QString unitName);
    void on_startExamON_OK();
    void on_questionReady_OK(QString question);
    void clearStudents();
    void on_writeOutStats_OK(QString studentPersonalDetails, double studentFinalGrade, QVector<double> GradesFromUnits);
    void on_writeOutStats_OK(QString studentPersonalDetails,int numberOfPassed, QVector<double> GradesFromUnits);
    void on_accept_clicked();
    void on_chooseFilepath_clicked();
    void on_showWarning_OK(QString warningHeading,QString warningContent);
private:
    Ui::MainWindow *ui;
    MainApp* mainApp = nullptr;
    QVector<QLineEdit*> unitsArray;
    QVector<QLineEdit*> gradesArray;
};
#endif // MAINWINDOW_H

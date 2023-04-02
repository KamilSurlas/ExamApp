#ifndef LOADDATAWINDOW_H
#define LOADDATAWINDOW_H
#include <QApplication>
#include "FileHandling.h"
#include <QDialog>

class MainApp;
class FileHandling;
namespace Ui {
class LoadWindow;
}

class LoadDataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDataWindow(QWidget *parent = nullptr, FileHandling* fileProgram = nullptr);
    ~LoadDataWindow();
private slots:
    void on_loadStudents_clicked();
    void on_loadQuestions_clicked();
    void on_loadedStudents_OK(QString studentsFilepath);
    void on_loadedQuestions_OK(QString questionsFilepath);


private:
    FileHandling* FileHandlingProgram = nullptr;
    Ui::LoadWindow *ui;
};

#endif // LOADDATAWINDOW_H


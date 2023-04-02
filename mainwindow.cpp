#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent, MainApp* mainApplication)
    : QMainWindow(parent), ui(new Ui::MainWindow),mainApp(mainApplication)
{
   mainApplication->setGUI(this);
   ui->setupUi(this);
   ui->stackedWidget->setCurrentIndex(1);
   ui->listaOcen->addItems(QStringList() << "2.0" << "3.0" << "3.5" << "4.0" << "4.5" << "5.0");
   ui->listaOcen->setCurrentText(0);
   unitsArray =  { ui->ocenaBlok1, ui->ocenaBlok2, ui->ocenaBlok3, ui->ocenaBlok4 };
   gradesArray = {ui->ocenaBl1,ui->ocenaBl2,ui->ocenaBl3,ui->ocenaBl4};


   connect(mainApplication,SIGNAL(examON()),this,SLOT(on_startExamON_OK()));
   connect(mainApplication,SIGNAL(showUnits(QString)),this,SLOT(on_unitSelected_OK(QString)));
   connect(mainApplication,SIGNAL(showQuestion(QString)),this,SLOT(on_questionReady_OK(QString)));
   connect(mainApplication,SIGNAL(finishExam()),this,SLOT(on_examFinish_OK()));
   connect(mainApplication,SIGNAL(claerStudents()),this,SLOT(clearStudents()));
   connect(mainApplication,SIGNAL(writeOutStats(QString, double, QVector<double>)),this,SLOT(on_writeOutStats_OK(QString, double, QVector<double>)));
   connect(mainApplication,SIGNAL(showWarning(QString,QString)),this,SLOT(on_showWarning_OK(QString,QString)));
   connect(mainApplication,SIGNAL(writeOutStats(QString, int, QVector<double>)),this,SLOT(on_writeOutStats_OK(QString, int, QVector<double>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_examFinish_OK()
{
    ui->next->setEnabled(false);
}
void MainWindow::on_loadButton_clicked()
{
    mainApp->openFileWindow();
    if(mainApp->checkLoadCorrectness()){
    for (int i = 0; i < mainApp->getNumberOfStudents(); i++)
        {
         ui->studentList->addItem(mainApp->getStudent(i).getStudentDetails());
         for (int j = 0; j < mainApp->getNumberOfUnits(); j++) {
             unitsArray.at(j)->setDisabled(false);
             unitsArray.at(j)->setText(mainApp->getStudent(i).getGrade(j));
             unitsArray.at(j)->setText(mainApp->getStudent(0).getGrade(j));
         }
       }
}
}



void MainWindow::on_examStart_clicked()
{
      ui->listaOcen->setCurrentIndex(0);
      ui->napisKoncowa->setText("Ocena końcowa:");
      ui->stackedWidget->setCurrentIndex(2);
      ui->etBlok->clear();
      ui->questionLabel->clear();
      ui->next->setEnabled(true);
      mainApp->startExam(mainApp->getStudent(ui->studentList->currentIndex()));

}


void MainWindow::on_finishExam_clicked()
{
    mainApp->rateAnswer(ui->listaOcen->currentText().toDouble());
    ui->stackedWidget->setCurrentIndex(0);
    mainApp->endExam();
}


void MainWindow::on_studentList_activated(int index)
{
    for(int i=0;i<mainApp->getNumberOfUnits();i++)
    {
        unitsArray.at(i)->setText(mainApp->getStudent(index).getGrade(i));
    }

}
void MainWindow::on_next_clicked()
{
    mainApp->rateAnswer(ui->listaOcen->currentText().toDouble());
    ui->listaOcen->setCurrentIndex(0);
    mainApp->moveToNextUnit();
}

void MainWindow::on_unitSelected_OK(QString unitName)
{
    ui->etBlok->setText(unitName);
}

void MainWindow::on_startExamON_OK()
{
    ui->examStart->setEnabled(true);
}

void MainWindow::on_questionReady_OK(QString question)
{
    ui->questionLabel->setText(question);
}


void MainWindow::clearStudents()
{
    ui->studentList->clear();
}
void MainWindow::on_writeOutStats_OK(QString studentPersonalDetails, double studentFinalGrade, QVector<double> GradesFromUnits)
{
    if(!studentPersonalDetails.isEmpty() && GradesFromUnits.size() > 0)
    {
        ui->daneStudenta->setText(studentPersonalDetails);
        ui->ocenaZaEgz->setText(QString::number(studentFinalGrade));
        for(int i=0;i<GradesFromUnits.size();i++)
        {
            gradesArray[i]->setText(QString::number(GradesFromUnits[i]));
        }
    }
}

void MainWindow::on_writeOutStats_OK(QString studentPersonalDetails, int numberOfPassed, QVector<double> GradesFromUnits)
{
    ui->napisKoncowa->setText("Wynik egzaminu");
    if(!studentPersonalDetails.isEmpty() && GradesFromUnits.size() > 0)
    {
        ui->daneStudenta->setText(studentPersonalDetails);
        ui->ocenaZaEgz->setText("Niezaliczono egzaminu, ilosc zaliczonych blokow: " + QString::number(numberOfPassed));
        for(int i=0;i<GradesFromUnits.size();i++)
        {
            gradesArray[i]->setText(QString::number(GradesFromUnits[i]));
        }
    }
}

void MainWindow::on_accept_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
    QVector<double> grades;
    for (int i=0;i<gradesArray.size();i++) {
        if(!gradesArray[i]->text().isNull()){
            grades.push_back(gradesArray[i]->text().toDouble());
        }
    }
    mainApp->saveStudentResult(grades,ui->studentList->currentText());
}


void MainWindow::on_chooseFilepath_clicked()
{
    mainApp->chooseFilepath();
}

void MainWindow::on_showWarning_OK(QString warningHeading, QString warningContent)
{

    QMessageBox mesBox;
    mesBox.setStyleSheet("background-color: rgb(64,64,64); color: rgb(255,255,255);");
    mesBox.setIcon(QMessageBox::Information);
    mesBox.setText(warningHeading);
    mesBox.setInformativeText(warningContent);
    mesBox.setStandardButtons(QMessageBox::Ok);
    mesBox.exec();
}


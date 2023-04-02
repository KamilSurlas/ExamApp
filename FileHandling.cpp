#include "FileHandling.h"
QString FileHandling::saveFilepath = "wyniki.txt";
FileHandling::FileHandling(MainApp *mainApplication)
{
    mainApp = mainApplication;
    connect(this,SIGNAL(studentsLoaded(QVector<Student>)),mainApplication,SLOT(setStudents(QVector<Student>)));
    connect(this,SIGNAL(questionsLoaded(QVector<Questions>)),mainApplication,SLOT(setQuestionsWithHeadings(QVector<Questions>)));
}

void FileHandling::loadStudents()
{
    if(!studentsFilepath.isEmpty())
    {
        QFile studentsFile(studentsFilepath);
        studentsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream stream(&studentsFile);
        QStringList dividedLine;
        QString line;
        QVector<Student>::iterator iteratorStudents;

        while(stream.atEnd() == false)
        {
            line = stream.readLine();
            dividedLine = line.split(" ", Qt::SkipEmptyParts);
            students.push_back(Student(dividedLine.at(0), dividedLine.at(1)));
            iteratorStudents = std::prev(students.end());



            line = stream.readLine();
            dividedLine = line.split("; ", Qt::SkipEmptyParts);

            for (auto iterator = dividedLine.begin(); iterator != dividedLine.end(); iterator++) {
                iteratorStudents->addGrade(iterator->toDouble());
            }
        }
        studentsFile.close();


        emit studentsLoaded(studentsFilepath);
        emit studentsLoaded(students);
    }
}

void FileHandling::loadQuestions()
{
    if(!questionsFilepath.isEmpty()) {
        QFile questionsFile(questionsFilepath);
        questionsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream stream(&questionsFile);
        QString unitNumber;
        QString question;
        QString questionHeading;

        std::string check;

        int howManyUnits = 0;

        while(stream.atEnd()==false) {
            unitNumber = stream.readLine();
            check = unitNumber.toStdString();
            if (!check.find("Blok")) {
                howManyUnits++;
                units.push_back(Questions());
            }

        }
        questionsFile.close();
        questionsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream secondStream(&questionsFile);
        int line = 1;
        QString necessary;
        int NumbersOfUnits = -1;

        while(secondStream.atEnd()==false) {
            necessary = secondStream.readLine();

            check = necessary.toStdString();
            if (!check.find("Blok")) {
                line = 1;
                NumbersOfUnits++;
            }
            if(line == 2) {
                questionHeading = necessary;
                this->units[NumbersOfUnits].addQuestionHeading(questionHeading);


            }
            if(line == 3) {
                question = necessary;
                QString basicQuestion = QString("<span style=\" color:#ff0000;\">%1</span>").arg(question);
                necessary = secondStream.readLine();
                question = necessary;

                QString advancedQuestion = QString("<span style=\" color:#1aff00;\">%1</span>").arg(question);
                qInfo() << "zaawansowane: " << advancedQuestion;
                this->units[NumbersOfUnits].addQuestion(basicQuestion, advancedQuestion);
                line = 1;
            }
            line++;
        }
    questionsFile.close();
    emit questionsLoaded(units);
    emit questionsLoaded(questionsFilepath);

    }
}

void FileHandling::chooseQuestionsFilepath()
{
    questionsFilepath = QFileDialog::getOpenFileName(this,tr("Wczytaj pytania"),tr(""),tr("Plik tekstowy(*.txt)"));
}

void FileHandling::chooseFileToSave()
{
    QString newFilepath = QFileDialog::getSaveFileName(this,"Wybierz gdzie mają być zapisane statystyki","","Plik tekstowy(*.txt)");
    QFile fielToClean(newFilepath);
    fielToClean.resize(0);
    saveFilepath = newFilepath;
}



void FileHandling::chooseStudentsFilepath()
{
    studentsFilepath = QFileDialog::getOpenFileName(this,tr("Wybierz listę studentow"),tr(""),tr("Plik tekstowy(*.txt)"));
}

void FileHandling::saveStudentExamGrade(QVector<double> gradesFromExam, QString personalData, int numberOfUnits)
{
   save(gradesFromExam,personalData,numberOfUnits);
}
void FileHandling::saveToHTML(QVector<double> gradesFromExam, QString personalData, int numberOfUnits)
{
    save(gradesFromExam,personalData,numberOfUnits,QDir::currentPath() + "/wyniki.html");
}
void FileHandling::save(QVector<double> gradesFromExam, QString personalData, int numberOfUnits, QString filepath)
{
    QFile saveFile(filepath);
    bool pass = true;
    if(saveFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QString newLineSign;
        if(filepath != saveFilepath)
        {
            newLineSign = "<br>";
        }
        else
        {
            newLineSign = "\n";
        }
        QTextStream stream(&saveFile);
        QString grades = " ";
        stream << personalData;
        int unitNumber = 1;
        double sum = 0;
        for (int i = 0; i < numberOfUnits; ++i) {
            grades +=  newLineSign + "Blok " + QString::number(unitNumber) + ": " + QString::number(gradesFromExam.at(i));
            unitNumber++;
            sum += gradesFromExam.at(i);
            if (gradesFromExam.at(i) < 3.0) {
                pass = false;
            }
        }
        double averageGrade = sum / numberOfUnits;
        stream << grades ;
        if(pass)
            stream <<  newLineSign + "Srednia z blokow: " << averageGrade <<  newLineSign +"Wynik egzaminu: pozytywny"+ newLineSign + newLineSign;
        else
            stream <<  newLineSign +"Wynik egzaminu: negatywny" +  newLineSign + newLineSign;
    }
}

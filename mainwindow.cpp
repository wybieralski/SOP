#include <QtGui>
#include "mainwindow.h"
#include <QListWidget>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Imię i nazwisko:"));
    imie = new QLineEdit;
    imie->setReadOnly(true);
    //QLabel *commentLabel = new QLabel(tr("Komentarz:"));
    //komentarz = new QTextEdit;
    //komentarz->setReadOnly(true);
    QLabel *dateLabel = new QLabel(tr("Data i godzina wizyty: "));
    data = new QDateTimeEdit;
    data->setReadOnly(true);

    addButton = new QPushButton(tr("&Dodaj"));
    addButton->show();
    submitButton = new QPushButton(tr("&Potwierdź"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Anuluj"));
    cancelButton->hide();
    nextButton = new QPushButton(tr("&Następna"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Poprzednia"));
    previousButton->setEnabled(false);
    editButton = new QPushButton(tr("&Edytuj"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Usuń"));
    removeButton->setEnabled(false);
    findButton = new QPushButton(tr("&Znajdz"));
    findButton->setEnabled(false);
    showButton = new QPushButton(tr("&Wyswietla"));
    showButton->setEnabled(false);


    connect(addButton, SIGNAL(clicked()), this, SLOT(dodajWizyte()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(zapiszWizyte()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(anuluj()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(nastepna()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(poprzednia()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(edytuj()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(usun()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findContact()));
    connect(showButton, SIGNAL(clicked()), this, SLOT(wyswietlWizyty2()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addStretch();
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);

    QVBoxLayout *buttonLayout2 = new QVBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    dialog = new znajdzWizyte;
    wyswietl = new wyswietlWizyty;


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(imie, 0, 1);
    mainLayout->addWidget(dateLabel,1,0);
    mainLayout->addWidget(data, 1,1);
    //mainLayout->addWidget(timeLabel, 2, 0);
    //mainLayout->addWidget(godzina, 2,1);
   // mainLayout->addWidget(commentLabel, 3, 0, Qt::AlignTop);
   // mainLayout->addWidget(komentarz, 3, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 4, 1 );
    setLayout(mainLayout);
    setWindowTitle(tr("System obsługi przychodni"));

    ///opis funkcji

}

void MainWindow::dodajWizyte()
{
    oldName = imie->text();
    oldDate = data->dateTime();
    //oldComment = komentarz->toPlainText();
    //oldDate = datatoString("h:m:s ap");
    //oldTime= godzina->text();
    imie->clear();
    //komentarz->clear();
    data->clear();

    imie->setReadOnly(false);
    imie->setFocus(Qt::OtherFocusReason);
    //komentarz->setReadOnly(false);
    data->setReadOnly(false);
    //godzina->setReadOnly(false);


    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
    nextButton->setEnabled(false);
    previousButton->setEnabled(false);


}

void MainWindow::zapiszWizyte()
{
    QString imie2 = imie->text();
    //QString komentarz2 = komentarz->toPlainText();
    QDateTime data2 = data->dateTime();
    //QTime godzina2 = godzina->time();


    if (imie2.isEmpty() ){
        QMessageBox::information(this, tr("Puste pole"),
                                 tr("Uzupełnij imię i adres."));
        return;
    }

    if (currentMode == AddingMode ){

        if (!wizyty.contains(imie2)){
            wizyty.insert(imie2, data2);

            QMessageBox::information(this, tr("Wizyta została dodana"),
                                     tr("\"%1\" został dodany do listy wizyt.").arg(imie2));
           } else {
            QMessageBox::information(this, tr("Wizyta nie mogła zostać dodana"),
                                     tr("\"%1\" znajduje się już na liście").arg(imie2));
            return;
        }
    } else if (currentMode == EditingMode){

        if(oldName != imie2) {
            QMessageBox::information(this, tr("Pomyślnie edytowano"),
                                tr("\"%1\" został edytowany.").arg(oldName));
                            wizyty.remove(oldName);
                            wizyty.insert(imie2, data2);
                            //gid.insert(godzina2,data2);


        } else {
            QMessageBox::information(this, tr("Nie można było edytować"),
                               tr("\"%1\" jest już na liście").arg(imie2));
        }
    }else if (oldDate != data2) {
            QMessageBox::information(this, tr("Edit Successful"),
                tr("\"%1\" has been edited in your address book.").arg(imie2));
            wizyty[imie2] = data2;
        }

    updateInterface(NavigationMode);
}

void MainWindow::anuluj()
{
    imie->setText(oldName);
    imie->setReadOnly(true);

    data->setDateTime(oldDate);
    data->setReadOnly(true);
    //komentarz->setText(oldComment);
    //komentarz->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
    nextButton->setEnabled(false);
    previousButton->setEnabled(false);
}

void MainWindow::nastepna()
{
    QString imie2 = imie->text();
    QDateTime data2 = data->dateTime();
    //QTime godzina2 = godzina->time();
   // QDate data2 = data->date();
    //QString godzina2 = godzina->text();
    QMap<QString, QDateTime>::iterator i=wizyty.find(imie2);
    //QMap<QTime, QDate>::iterator j=gid.find(godzina2);
    //QMap<QString, QString>::iterator j=gid.find(godzina2);

    if ( i != wizyty.end() ){
        i++;

    }

    else if ( i == wizyty.end() ){
        i = wizyty.begin();
    }


    imie->setText(i.key());
    data->setDateTime(i.value());
    //komentarz->setText(i.value());
    //godzina->setText(j.key());
    //data->setText(j.value());
    //godzina->setTime(j.key());
    //data->setDate(j.value());
}

void MainWindow::poprzednia()
{
    QString imie2 = imie->text();
    QMap<QString, QDateTime>::iterator i=wizyty.find(imie2);
    if ( i != wizyty.end()){
     imie->clear();
     data->clear();
     return;
    }

    if ( i == wizyty.begin())
        i = wizyty.end();

    i--;
    imie->setText(i.key());
    data->setDateTime(i.value());
}

void MainWindow::edytuj()
{
    oldName = imie->text();
    oldDate = data->dateTime();

    updateInterface(EditingMode);
}

void MainWindow::usun()
{
    QString imie2 = imie->text();
    QDateTime data2 = data->dateTime();


       if (wizyty.contains(imie2)) {

           int button = QMessageBox::question(this,
               tr("Potwierdz usuniecie"),
               tr("Na pewno chcesz usunac wizyte \"%1\"?").arg(imie2),
               QMessageBox::Yes | QMessageBox::No);

           if (button == QMessageBox::Yes) {

               poprzednia();
               wizyty.remove(imie2);

               QMessageBox::information(this, tr("Usunięto wizytę"),
                   tr("\"%1\" zostałą usunięta z listy.").arg(imie2));
           }
       }

       updateInterface(NavigationMode);
}

void MainWindow::updateInterface(MainWindow::Mode mode)
{
    currentMode = mode;

    switch(currentMode){
    case AddingMode:
    case EditingMode:


        imie->setReadOnly(false);
        imie->setFocus(Qt::OtherFocusReason);
        data->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);
        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();
        break;

    case NavigationMode:


    if (wizyty.isEmpty()) {
         imie->clear();
         data->clear();
     }

     imie->setReadOnly(true);
     data->setReadOnly(true);
     addButton->setEnabled(true);

     submitButton->hide();
     cancelButton->hide();


     int number = wizyty.size();

     editButton->setEnabled(number >= 1);
     removeButton->setEnabled(number >= 1);
     nextButton->setEnabled(number > 1);
     previousButton->setEnabled(number > 1);
     findButton->setEnabled(number > 2);

     submitButton->hide();
     cancelButton->hide();
        break;
    }

}
void MainWindow::findContact()
{
    dialog->show();

    if (dialog->exec() == QDialog::Accepted) {
        QString contactName = dialog->getFindText();

        if (wizyty.contains(contactName)) {
            imie->setText(contactName);
            data->setDateTime(wizyty.value(contactName));
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void MainWindow::wyszukaj()
{
        wyswietl->show();

        if (wyswietl->exec() == QDialog::Accepted) {
            QString contactName = wyswietl->wyswietl();

            if (wizyty.contains(contactName)) {
                imie->setText(contactName);
                data->setDateTime(wizyty.value(contactName));
            } else {
                QMessageBox::information(this, tr("Contact Not Found"),
                    tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
                return;
            }
        }

        updateInterface(NavigationMode);
}

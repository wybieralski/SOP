#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Imię i nazwisko:"));
    imie = new QLineEdit;
    imie->setReadOnly(true);
    QLabel *commentLabel = new QLabel(tr("Komentarz:"));
    komentarz = new QTextEdit;
    komentarz->setReadOnly(true);
    QLabel *dateLabel = new QLabel(tr("Data wizyty: "));
    data = new QDateEdit;
    data->setReadOnly(true);
    QLabel *timeLabel = new QLabel(tr("Godzina wizyty: "));
    godzina = new QTimeEdit;
    godzina->setReadOnly(true);

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

    connect(addButton, SIGNAL(clicked()), this, SLOT(dodajWizyte()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(zapiszWizyte()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(anuluj()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(previous()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addStretch();

    QVBoxLayout *buttonLayout2 = new QVBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(imie, 0, 1);
    mainLayout->addWidget(dateLabel,1,0);
    mainLayout->addWidget(data, 1,1);
    mainLayout->addWidget(timeLabel, 2, 0);
    mainLayout->addWidget(godzina, 2,1);
    mainLayout->addWidget(commentLabel, 3, 0, Qt::AlignTop);
    mainLayout->addWidget(komentarz, 3, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 4, 1 );
    setLayout(mainLayout);
    setWindowTitle(tr("System obsługi przychodni"));

    ///opis funkcji

}

void MainWindow::dodajWizyte()
{
    oldName = imie->text();
    oldComment = komentarz->toPlainText();


    imie->clear();
    komentarz->clear();
    data->clear();
    godzina->clear();

    imie->setReadOnly(false);
    imie->setFocus(Qt::OtherFocusReason);
    komentarz->setReadOnly(false);
    data->setReadOnly(false);
    godzina->setReadOnly(false);


    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
    nextButton->setEnabled(false);
    previousButton->setEnabled(false);


}

void MainWindow::zapiszWizyte()
{
    QString imie2 = imie->text();
    QString komentarz2 = komentarz->toPlainText();

    if (imie2.isEmpty() || komentarz2.isEmpty()){
        QMessageBox::information(this, tr("Puste pole"),
                                 tr("Uzupełnij imię i adres."));
        return;
    }

    if (!wizyty.contains(imie2)){
        wizyty.insert(imie2, komentarz2);
        QMessageBox::information(this, tr("Wizyta została dodana"),
                                 tr("\"%1\" został dodany do listy wizyt.").arg(imie2));
       } else {
        QMessageBox::information(this, tr("Wizyta nie mogła zostać dodana"),
                                 tr("\"%1\" znajduje się już na liście").arg(imie2));
        return;
    }

    if (wizyty.isEmpty()) {
         imie->clear();
         komentarz->clear();
     }

     imie->setReadOnly(true);
     komentarz->setReadOnly(true);
     addButton->setEnabled(true);

     submitButton->hide();
     cancelButton->hide();


     int number = wizyty.size();
     nextButton->setEnabled(number > 1);
     previousButton->setEnabled(number > 1);
}

void MainWindow::anuluj()
{
    imie->setText(oldName);
    imie->setReadOnly(true);

    komentarz->setText(oldComment);
    komentarz->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
    nextButton->setEnabled(false);
    previousButton->setEnabled(false);
}

void MainWindow::nastepna()
{
    QString imie2 = imie->text();
    QMap<QString, QString>::iterator i=wizyty.find(imie2);

    if ( i != wizyty.end())
        i++;
    if ( i == wizyty.end())
        i = wizyty.begin();

    imie->setText(i.key());
    komentarz->setText(i.value());
}

void MainWindow::poprzednia()
{
    QString imie2 = imie->text();
    QMap<QString, QString>::iterator i=wizyty.find(imie2);

    if ( i != wizyty.end()){
     imie->clear();
     komentarz->clear();
     return;
    }

    if ( i == wizyty.begin())
        i = wizyty.end();

    i--;
    imie->setText(i.key());
    komentarz->setText(i.value());
}

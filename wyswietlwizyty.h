#ifndef WYSWIETLWIZYTY_H
#define WYSWIETLWIZYTY_H
#include <QDialog>
#include <QListView>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>

class wyswietlWizyty: public QDialog
{
public:
        wyswietlWizyty(QWidget *parent = 0);
        QString wyświetl();

public slots:
        void wyswietlWizyte();

private:
        QPushButton *showButton;
        QLineEdit *lineEdit;
        QString *szukaj;
};

#endif // WYSWIETLWIZYTY_H

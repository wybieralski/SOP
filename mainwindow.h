#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QMap>

class QLabel;
class QLineEdit;
class QTextEdit;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    enum Mode {NavigationMode, AddingMode, EditingMode};


public slots:
    void dodajWizyte();
    void zapiszWizyte();
    void anuluj();
    void nastepna();
    void poprzednia();
    void edytuj();
    void usun();


private:
    void updateInterface(Mode mode);
    QLineEdit *imie;
    QTextEdit *komentarz;
    QDateEdit *data;
    QTimeEdit *godzina;

    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *editButton;
    QPushButton *removeButton;


    QMap<QString, QString> wizyty;
    QString oldName;
    QString oldComment;

    Mode currentMode;

};
#endif // MAINWINDOW_H

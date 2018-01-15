#ifndef WYSZUKIWARKA_H
#define WYSZUKIWARKA_H

#include <QDialog>


class wyszukiwarka
{
    Q_OBJECT
public:
    wyszukiwarka();



public:
    FindDialog(QWidget *parent = 0);
    QString getFindText();

public slots:
    void findClicked();

private:
    QPushButton *findButton;
    QLineEdit *lineEdit;
    QString findText;
};

#endif // WYSZUKIWARKA_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);
    QString getFindText();

public slots:
    void findClicked();

private:
    QPushButton *findButton;
    QLineEdit *lineEdit;
    QString findText;
};

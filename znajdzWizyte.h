#ifndef znajdzWizyte_H
#define znajdzWizyte_H
#include <QDialog>

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


class QLineEdit;
class QPushButton;

class znajdzWizyte : public QDialog
{
    Q_OBJECT

public:
    znajdzWizyte(QWidget *parent = 0);
    QString getFindText();

public slots:
    void findClicked();

private:
    QPushButton *findButton;
    QLineEdit *lineEdit;
    QString findText;
};
#endif

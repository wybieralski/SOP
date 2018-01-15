#include "wyswietlwizyty.h"



wyswietlWizyty::wyswietlWizyty(QWidget *parent)
    :QDialog(parent)
{
    QLabel *szukajLabel = new QLabel(tr("Wybierz dzień"));
    lineEdit = new QLineEdit;

    showButton = new QPushButton(tr("Wyświetl"));
    szukaj =" ";

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(szukajLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(showButton);

    setLayout(layout);
    setWindowTitle(tr("Wizyty dla danego dnia"));
    connect(showButton, SIGNAL(clicked()), this, SLOT(wyswietlWizyte()));
    connect(showButton, SIGNAL(clicked()), this, SLOT(accept()));
}
void wyswietlWizyty::wyswietlWizyty()
{
    QString text = lineEdit->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name."));
        return;
    } else {
        findText = text;
        lineEdit->clear();
        hide();
    }
}

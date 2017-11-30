#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



public:
    explicit MainWindow(AddressBookController *controller, QWidget *parent = 0);
    ~MainWindow();

public slots:

    void createEntry();
    void deleteEntry();
    void editEntry();
    void saveEntry();
    void discardEntry();
    void resetEntry();

private:
    Ui::MainWindow *ui;



    void setupConnections();
};
#endif // MAINWINDOW_H

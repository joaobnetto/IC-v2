#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QProgressBar>
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addSingleItem();
    void importItems();
    void importSalas();
    void start();

private:
    Ui::MainWindow *ui;
    QTableWidget * table;
    QTableWidget * tableSala;
    QPushButton * startBtn;
    Data myData;
    QProgressBar * progress;
};

#endif // MAINWINDOW_H

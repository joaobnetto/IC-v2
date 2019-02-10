#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QDialog>
#include <QHBoxLayout>
#include <QTextStream>
#include <QProgressBar>
#include <QHeaderView>
#include <QFileDialog>
#include <QPushButton>

#define SALA_COLUMN 5
#define PEDIDO_COLUMN 6

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *w = new QWidget;
    setCentralWidget(w);
    setWindowTitle("Alocar");
    showMaximized();
    QVBoxLayout *m_layout = new QVBoxLayout(w);
    QHBoxLayout *tableLayout = new QHBoxLayout;
    table = new QTableWidget(0, PEDIDO_COLUMN);
    QStringList header;
    header << "Predio" << "Capacidade" << "Horario" << "Curso" << "Periodo" << "Info";
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableSala = new QTableWidget(0, SALA_COLUMN);

    header = QStringList();
    header << "Nome" << "Capacidade" << "Tipo" << "Predio" << "Grupo";
    tableSala->setHorizontalHeaderLabels(header);
    tableSala->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableLayout->addWidget(table);
    tableLayout->addWidget(tableSala);

    progress = new QProgressBar();
    progress->setMaximum(3*6*6);

    QHBoxLayout * btnLayout = new QHBoxLayout();
//    QPushButton * addBtn = new QPushButton("&Adicionar");
    QPushButton * impBtn = new QPushButton("&Importar Pedidos");
    QPushButton * impSBtn = new QPushButton("&Importar Salas");
    startBtn = new QPushButton("&Iniciar");

    startBtn->setEnabled(false);

//    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(impBtn);
    btnLayout->addWidget(impSBtn);
    btnLayout->addWidget(startBtn);

    m_layout->addLayout(tableLayout);
    m_layout->addWidget(progress);
    m_layout->addLayout(btnLayout);

//    connect(addBtn, SIGNAL ( clicked() ), this, SLOT ( addSingleItem() ));
    connect(impBtn, SIGNAL( clicked() ), this, SLOT ( importItems() ));
    connect(startBtn, SIGNAL( clicked() ), this, SLOT ( start() ));
    connect(impSBtn, SIGNAL( clicked() ), this, SLOT( importSalas() ));
}

void MainWindow::addSingleItem(){
//    QDialog * newItem = new QDialog(this);

}

void MainWindow::importItems(){
    auto fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Open file"), "~/", tr("JSON Files (*.json)"));
    if(fileName.isEmpty()){
        return;
    }
    myData.importData(fileName);
    for(int i = 0;i < myData.length();++i){
        table->insertRow(i);
        for(int j = 0;j < table->columnCount();++j){
            table->setItem(i, j, new QTableWidgetItem( myData.item(i, j) ));
        }
    }
    table->sortByColumn(0, Qt::AscendingOrder);
    if(myData.length() && myData.lengthSala()) startBtn->setEnabled(true);
}

void MainWindow::importSalas(){
    auto fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Open file"), "~/", tr("JSON Files (*.json)"));
    if(fileName.isEmpty()){
        return;
    }
    myData.importSala(fileName);
    QTextStream stream(stderr);
    stream << myData.lengthSala() << endl;
    for(int i = 0;i < myData.lengthSala();++i){
        tableSala->insertRow(i);
        for(int j = 0;j < tableSala->columnCount();++j){
            tableSala->setItem(i, j, new QTableWidgetItem( myData.sala(i, j) ));
        }
    }
    tableSala->sortByColumn(4, Qt::AscendingOrder);
    if(myData.length() && myData.lengthSala()) startBtn->setEnabled(true);
}
void MainWindow::start(){
    myData.alocarDados(*progress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

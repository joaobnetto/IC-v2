#include "data.h"
#include <QFileDialog>
#include <QTextStream>
#include <QObject>

Data::Data()
{

}

void Data::addItem(QString newData){
    QStringList split = newData.split(QStringLiteral(";"));
    data << split;
}

void Data::addSala(QString newSala){
    QStringList split = newSala.split(QStringLiteral(";"));
    salas << split;
}

void Data::importData(QString fileName){
    QStringList retorno = alocar.lerPedidos(fileName);
    QString str;
    foreach (str, retorno){
        addItem(str);
    }
}

void Data::importSala(QString fileName){
    QStringList retorno = alocar.lerSalas(fileName);
    QString str;
    foreach (str, retorno){
        addSala(str);
    }
}

int Data::length() const{
    return data.size();
}

int Data::lengthSala() const{
    return salas.size();
}


QString Data::item(int i, int j){
    return data[i][j];
}

QString Data::sala(int i, int j){
    return salas[i][j];
}

void Data::alocarDados(QProgressBar &progress){
    alocar.alocar(progress);
    alocar.imprimirPedidos();
}

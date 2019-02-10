#ifndef DATA_H
#define DATA_H

#include <QStringList>
#include <QFile>
#include <QObject>
#include <QProgressDialog>
#include "alocar.h"

class Data : public QObject
{
public:
    Data();
    void addItem(QString newData);
    void addSala(QString newSala);
    int length() const;
    int lengthSala() const;
    void importData(QString fileName);
    void importSala(QString fileName);
    QString item(int i, int j);
    QString sala(int i, int j);
    void alocarDados(QProgressBar &progress);
private:
    QList < QStringList > data;
    QList < QStringList > salas;
    Alocar alocar;
};

#endif // DATA_H

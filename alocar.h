#ifndef ALOCAR_H
#define ALOCAR_H

#include <vector>
#include "sala.h"
#include "graph.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <QString>
#include <QProgressBar>
#include <QStringList>

class Alocar{
private:
    std::vector < Sala > salas;
    std::vector < Pedido > nao_alocados;
    struct Vector4D{
        std::vector < Pedido > p;
    };
    Vector4D pedidos[6][3][6];

public:
    void alocar(QProgressBar &progress);
    QStringList lerPedidos(QString fileName);
    QStringList lerSalas(QString fileName);
    void imprimirSalas();
    void imprimirNaoAlocados();
    void imprimirPedidos();
};

#endif // ALOCAR_H

#ifndef LIVRAISON_H
#define LIVRAISON_H
#include <QString>
#include <QSqlQueryModel>
class livraison
{
    QString ID_LIVRAISON;
    QString DATE_LIVRAISON;
    QString FRAIS_LIVRAISON;
    QString TYPE_LIVRAISON;
    QString ETAT_LIVRAISON;
public:
    livraison();
    livraison(QString ID_LIVRAISON,QString DATE_LIVRAISON,QString FRAIS_LIVRAISON,QString TYPE_LIVRAISON,QString ETAT_LIVRAISON);
    void Ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *tri();
    void supprimer(QString ID_equipements);
    void modifier();
    QSqlQueryModel *rechercher(QString ID_LIVRAISON);
};

#endif // LIVRAISON_H

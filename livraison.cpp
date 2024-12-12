#include "livraison.h"
#include <QSqlQuery>

livraison::livraison()
{

}
livraison::livraison(QString ID_LIVRAISON,QString DATE_LIVRAISON,QString FRAIS_LIVRAISON,QString TYPE_LIVRAISON,QString ETAT_LIVRAISON)
{
    this->ID_LIVRAISON=ID_LIVRAISON;
    this->DATE_LIVRAISON=DATE_LIVRAISON;
    this->FRAIS_LIVRAISON=FRAIS_LIVRAISON;
    this->TYPE_LIVRAISON=TYPE_LIVRAISON;
    this->ETAT_LIVRAISON=ETAT_LIVRAISON;
}
void livraison::Ajouter()
{
    QSqlQuery query;
    query.prepare("insert into LIVRAISON (ID_LIVRAISON,DATE_LIVRAISON,FRAIS_LIVRAISON,TYPE_LIVRAISON,ETAT_LIVRAISON) values (:ID_LIVRAISON,:DATE_LIVRAISON,:FRAIS_LIVRAISON,:TYPE_LIVRAISON,:ETAT_LIVRAISON)");//requete bch najouti lel base les attributs
    query.bindValue(":ID_LIVRAISON", ID_LIVRAISON);
    query.bindValue(":DATE_LIVRAISON", DATE_LIVRAISON);
    query.bindValue(":FRAIS_LIVRAISON", FRAIS_LIVRAISON);
    query.bindValue(":TYPE_LIVRAISON", TYPE_LIVRAISON);
    query.bindValue(":ETAT_LIVRAISON", ETAT_LIVRAISON);
    query.exec();
}
QSqlQueryModel * livraison::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from LIVRAISON");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_LIVRAISON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_LIVRAISON"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FRAIS_LIVRAISON"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_LIVRAISON"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT_LIVRAISON"));
    return model;
}
QSqlQueryModel * livraison::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from LIVRAISON ORDER BY ID_LIVRAISON DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_LIVRAISON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_LIVRAISON"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FRAIS_LIVRAISON"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_LIVRAISON"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT_LIVRAISON"));
    return model;
}
void livraison::supprimer(QString id)
{
        QSqlQuery query;
        query.prepare("delete from LIVRAISON where ID_LIVRAISON = :ID_LIVRAISON");
        query.bindValue(":ID_LIVRAISON", id);
        query.exec();
}
void livraison::modifier()
{
    QSqlQuery query;
          query.prepare("update  LIVRAISON set  DATE_LIVRAISON=:DATE_LIVRAISON, FRAIS_LIVRAISON=:FRAIS_LIVRAISON,TYPE_LIVRAISON=:TYPE_LIVRAISON,ETAT_LIVRAISON=:ETAT_LIVRAISON where(ID_LIVRAISON=:ID_LIVRAISON)");
          query.bindValue(":ID_LIVRAISON",ID_LIVRAISON);
          query.bindValue(":DATE_LIVRAISON", DATE_LIVRAISON);
          query.bindValue(":FRAIS_LIVRAISON", FRAIS_LIVRAISON);
          query.bindValue(":TYPE_LIVRAISON", TYPE_LIVRAISON);
          query.bindValue(":ETAT_LIVRAISON", ETAT_LIVRAISON);
          query.exec();
}
QSqlQueryModel * livraison::rechercher(QString id)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from LIVRAISON where ID_LIVRAISON like '%"+id+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_LIVRAISON"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_LIVRAISON"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FRAIS_LIVRAISON"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE_LIVRAISON"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT_LIVRAISON"));
    return model;
}

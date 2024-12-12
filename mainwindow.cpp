#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraison.h"
#include <QMessageBox>
#include <QtCharts>
#include <QSqlQuery>
#include "smtpp.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::afficher()
{
    livraison l;
    ui->tableView->setModel(l.afficher());
}

void MainWindow::on_pushButton_clicked()
{
    QString ID_LIVRAISON = ui->lineEdit->text();
    QString DATE_LIVRAISON =  ui->dateEdit->date().toString();
    QString FRAIS_LIVRAISON = ui->lineEdit_3->text();
    QString TYPE_LIVRAISON = ui->lineEdit_4->text();
    QString ETAT_LIVRAISON = ui->lineEdit_5->text();
    livraison l(ID_LIVRAISON,DATE_LIVRAISON,FRAIS_LIVRAISON,TYPE_LIVRAISON,ETAT_LIVRAISON);
    if (ID_LIVRAISON=="" || DATE_LIVRAISON=="" || FRAIS_LIVRAISON=="" || TYPE_LIVRAISON=="" || ETAT_LIVRAISON==""  ) {

        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs");
    } else {
        if(FRAIS_LIVRAISON.toInt()<=0)
        {
            QMessageBox::warning(this, "Erreur", "Veuillez introduire un frais > 0 ");
        }
        else{
    l.Ajouter();
    ui->tableView->setModel(l.afficher());
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString ID_LIVRAISON = ui->lineEdit->text();
    livraison l;
    l.supprimer(ID_LIVRAISON);
    ui->tableView->setModel(l.afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    QString ID_LIVRAISON = ui->lineEdit->text();
    QString DATE_LIVRAISON =  ui->dateEdit->date().toString();
    QString FRAIS_LIVRAISON = ui->lineEdit_3->text();
    QString TYPE_LIVRAISON = ui->lineEdit_4->text();
    QString ETAT_LIVRAISON = ui->lineEdit_5->text();
    livraison l(ID_LIVRAISON,DATE_LIVRAISON,FRAIS_LIVRAISON,TYPE_LIVRAISON,ETAT_LIVRAISON);
    if (ID_LIVRAISON=="" || DATE_LIVRAISON=="" || FRAIS_LIVRAISON=="" || TYPE_LIVRAISON=="" || ETAT_LIVRAISON==""  ) {

        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs");
    } else {
        if(FRAIS_LIVRAISON.toInt()<=0)
        {
            QMessageBox::warning(this, "Erreur", "Veuillez introduire un frais > 0 ");
        }
        else{
    l.modifier();
    ui->tableView->setModel(l.afficher());
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    livraison l;
    ui->tableView->setModel(l.tri());
}


void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    livraison l;
    ui->tableView->setModel(l.rechercher(arg1));
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_6_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
   QSqlQuery query;
   query.exec("SELECT ETAT_LIVRAISON, COUNT(*) FROM LIVRAISON GROUP BY ETAT_LIVRAISON");

   QPieSeries *series = new QPieSeries();
   while (query.next()) {
       QString ETAT_LIVRAISON = query.value(0).toString();
       int count = query.value(1).toInt();
       QPieSlice *slice = new QPieSlice(ETAT_LIVRAISON, count);
       series->append(slice);
   }

   QChart *chart = new QChart();
   chart->addSeries(series);
   chart->setTitle("Statistics based on LIVRAISON ETAT_LIVRAISON");
   chart->setAnimationOptions(QChart::SeriesAnimations);

   QChartView *chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);
   chartView->setParent(ui->tableView_2);
   chartView->resize(ui->tableView_2->size());
   chartView->show();
}


void MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_pushButton_22_clicked()
{
    QString email = ui->lineEdit_7->text();
    QString titre = ui->lineEdit_8->text();
    QString contenu = ui->lineEdit_9->text();
    smtpp* ssmtp = new smtpp("lina.saied@esprit.tn", "xibm gpyu rltc cjry", "smtp.gmail.com", 465);

            connect(ssmtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


               ssmtp->sendMail("lina.saied@esprit.tn", email , titre,contenu);
                                  QMessageBox::information(nullptr, QObject::tr("EMAIL"),
                                  QObject::tr("Email Envoyé avec succees.\n"
                                  "click Cancel to exit"),QMessageBox::Cancel);
}


void MainWindow::on_pushButton_23_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_7_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_24_clicked()
{
    QPdfWriter pdf("C:/Users/linaS/OneDrive/Desktop/lina/livraison.pdf");

           QPainter painter(&pdf);
           int i = 4100;

                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des Commande");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));
                              painter.drawText(300,3600,"id_livraison");
                              painter.drawText(2000,3600,"DATE_LIVRAISON");
                              painter.drawText(4000,3600,"FRAIS_LIVRAISON");
                              painter.drawText(6000,3600,"TYPE_LIVRAISON");
                              painter.drawText(8000,3600,"ETAT_LIVRAISON");

                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from livraison");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(2000,i,query.value(1).toString());
                          painter.drawText(4000,i,query.value(2).toString());
                          painter.drawText(6000,i,query.value(3).toString());
                          painter.drawText(8000,i,query.value(4).toString());

                     i = i + 500;
                  }

                  int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
                  if (reponse == QMessageBox::Yes)
                  {
                      QDesktopServices::openUrl( QUrl::fromLocalFile("C:/Users/linaS/OneDrive/Desktop/lina/livraison.pdf"));
                      painter.end();
                  }
                  else
                  {
                      painter.end();
                  }
}
//fonction insertion image dans la base
bool MainWindow::insertImageIntoDatabase(const QByteArray& imageData,QString ID) {


       // Prepare SQL query
       QSqlQuery query;
       query.prepare("UPDATE livraison SET image = :imageData WHERE id_livraison = :id");
       query.bindValue(":imageData", imageData);
       query.bindValue(":id", ID);
       // Execute the query
       if (!query.exec()) {
           qDebug() << "Failed to insert image into database:";
           return false;
       }

       return true;
   }
//inserer image
void MainWindow::on_pushButton_25_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choose Image"), QDir::currentPath(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (imagePath.isEmpty()) {
               return;
           }

           // Read the image file
           QFile file(imagePath);
           if (!file.open(QIODevice::ReadOnly)) {
               qDebug() << "Failed to open image file:" << imagePath;
               return;
           }
    QByteArray imageData = file.readAll();
    QString ID = ui->lineEdit->text();
    if (!insertImageIntoDatabase(imageData,ID)) {
               qDebug() << "Failed to insert image into database.";
               return;
           }

           qDebug() << "Image inserted into database successfully.";
}

//afficher image
void MainWindow::on_pushButton_26_clicked()
{
    QString ID = ui->lineEdit->text();



       // Prepare SQL query to retrieve image data based on ID
       QSqlQuery query;
       query.prepare("SELECT image FROM livraison WHERE id_livraison = :id");
       query.bindValue(":id", ID);

       // Execute the query
       if (!query.exec()) {
           qDebug() << "Failed to retrieve image data from database:" ;
           return;
       }

       // Check if a record was found
       if (!query.next()) {
           qDebug() << "No image found for the given ID.";
           return;
       }

       // Retrieve image data from the query result
       QByteArray imageData = query.value("image").toByteArray();

       // Convert image data to QPixmap and display
       QPixmap pixmap;
       pixmap.loadFromData(imageData);

       // Assuming you have a QLabel named imageLabel where you want to display the image
       ui->label_28->setPixmap(pixmap);
       ui->label_28->setScaledContents(true);
       ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::update_label(){
    data = A.read_from_arduino();
qDebug() << data;
    QSqlQuery q;
    q.prepare("SELECT * from LIVRAISON WHERE id_livraison = :id");
    q.bindValue(":id",data.toInt());
    q.exec();
    q.first();


    if (q.value(0).toString() != "")
    {
ui->lineEdit->setText(q.value(0).toString());
ui->lineEdit_3->setText(q.value(2).toString());
ui->lineEdit_4->setText(q.value(3).toString());
ui->lineEdit_5->setText(q.value(4).toString());



    }




}

void MainWindow::on_pushButton_8_clicked()
{
   QString id= ui->arduino->text();

   QSqlQuery q;
   q.prepare("SELECT * from LIVRAISON WHERE id_livraison = :id");
   q.bindValue(":id",id);
   q.exec();
   q.first();


   if (q.value(0).toString() != "")
    {A.write_to_arduino("1");

   QMessageBox::information(this, "etat", "Livraison trouvee");
   }
    else {QMessageBox::warning(this, "etat", "Livraison non trouvee");}
}


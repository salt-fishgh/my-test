#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QtDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    //set routine

}


void MainWindow::on_pushButton_clicked()
{
    //when click this clear the textedit
    ui->textEdit->clear();
    //print qt support sql type
    //qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    if(!db.open())
    {
        qDebug()<<"fail open"<<endl;
        return;
    }
    QSqlQuery query;
    query.exec("select * from xuejin;");
    while(query.next())
    {
        qDebug()<<query.value(0).toInt()
               <<query.value(1).toString()
              <<query.value(2).toInt();
        ui->textEdit->append(query.value(0).toString()+QString("\t")+query.value(1).toString()+QString("\t")+query.value(2).toString());
    }
    //qDebug()<<query.value(1);


}

void MainWindow::on_pushButton_2_clicked()
{
    QString name = ui->lineEdit->text();

    QSqlDatabase::database().transaction();  //.transaction();
    QString str = QString("delete from xuejin where name = '%1';").arg(name);
    //qDebug()<<str<<endl;
    QSqlQuery query;
    query.exec(str);
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlDatabase::database().commit();

}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlDatabase::database().rollback();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString name = ui->lineEdit_2->text();
    QString age = ui->lineEdit_3->text();
    QSqlDatabase::database().transaction();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString str = QString("insert into xuejin(name,age) values('%1',%2);").arg(name).arg(age);
    qDebug()<<str;
    db.setDatabaseName("test.db");
    if(!db.open())
    {
        qDebug()<<db.lastError().text()<<endl;
        return ;
    }
    QSqlQuery query;
    bool flag = query.exec(str);
    if(!flag)
    {
        QMessageBox::warning(this,"tip","query exec is error");
    }
    //ui->lineEdit_2->clear();


}

void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox::warning(this,"tip","makesure to add database");
    QSqlDatabase::database().commit();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();


}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlDatabase::database().rollback();
}

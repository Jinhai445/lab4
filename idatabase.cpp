#include "idatabase.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QSqlRecord>
#include <QDateTime>
#include <QUuid>
#include <QSqlError>
QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");
    query.bindValue(":USER",userName);
    query.exec();
    qDebug()<< query.lastQuery()<< query.first();
    if(query.first()&& query.value("username").isValid()){
       QString passwd = query.value("password").toString();
        if(passwd == password){
           qDebug()<<"login ok";
            return "loginOk";
        }else{
            qDebug()<<"wrong password";
            return "wrongPassword";
        }
    }else {
        qDebug()<< "no such user";return "wrongUsername";
    }
}

void IDatabase::ininDatabase()
{
    database = QSqlDatabase ::addDatabase("QSQLITE");
    QString aFile = "D:/lab4b.db";
    database.setDatabaseName(aFile); //设置数据库名称；
    if(!database.open()){
        qDebug()<<"success";
    }else{
        qDebug()<<"failes";
    }
}

IDatabase::IDatabase(QObject *parent) :QObject(parent){
    ininDatabase();
}
bool IDatabase::initPatientModel(){
    patientTabModel =new QSqlTableModel(this, database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，onManualsubmit,onRowchangepatientTabModel->setSort(patientTabModel->fieldIndex("name"),0t::Ascendingorder); //排序if(!(patientTabModel->select()))//查询数据
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(patientTabModel->select())){
        return false;
    }
    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;

}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deletecurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}
bool IDatabase::submitPatientEdit(){
    return patientTabModel->submitAll();
}
void IDatabase::revertPatientEdit(){
    return patientTabModel->revertAll();
}

int IDatabase::addNewPatient()
{

    patientTabModel->insertRow(patientTabModel->rowCount(), QModelIndex());

    // 获取新插入行的索引
    int curRecNo = patientTabModel->rowCount() - 1;

    // 设置CREATEDSTAMP和ID字段
    QModelIndex indexCreatedStamp = patientTabModel->index(curRecNo, patientTabModel->fieldIndex("CREATEDSTAMP"));
    QModelIndex indexID = patientTabModel->index(curRecNo, patientTabModel->fieldIndex("ID"));

    // 更新字段
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    patientTabModel->setData(indexCreatedStamp, currentTime);
    patientTabModel->setData(indexID, QUuid::createUuid().toString(QUuid::WithoutBraces));

    return curRecNo;
}

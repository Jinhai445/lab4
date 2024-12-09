#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QSqlError>
PatientEditView::PatientEditView(QWidget *parent,int rowNo)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);
    dataMapper =new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(IDatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->addMapping(ui->ID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->ID_Card,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->Name,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->height,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->weight,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->PhoneNumber,tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->date,tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->sex,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->createTImeStamp,tabModel->fieldIndex("CREATEDSTAMP"));
    dataMapper->setCurrentIndex(rowNo);

}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_Bt_save_clicked()
{
    IDatabase::getInstance().submitPatientEdit();

    emit goPreviousView();
}


void PatientEditView::on_Bt_cancel_clicked()
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
}


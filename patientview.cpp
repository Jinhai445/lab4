#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"
#include <QModelIndex>
PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    IDatabase& iDatabase = IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btSearch_clicked()
{
    QString filter =  QString("name like '%%1%'").arg(ui->btEdit->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btDel_clicked()
{
    IDatabase::getInstance().deletecurrentPatient();
}


void PatientView::on_btModify_clicked()
{
    QModelIndex curIndex = IDatabase::getInstance().thePatientSelection->currentIndex();
    emit goPatientEditView(curIndex.row());
}


void PatientView::on_btAdd_clicked()
{
    int currow =IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}


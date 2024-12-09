#include "masterview.h"
#include "ui_masterview.h"
#include "departmentview.h"
#include "doctorview.h"
#include "loginview.h"
#include "patientview.h"
#include "patienteditview.h"
#include "welcomeview.h"
#include <qwidget.h>
#include "idatabase.h"
MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    goLoginView();
    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}
void MasterView:: goLoginView(){

    loginView = new LoginView();
    pushWidgetToStackView(loginView);
    connect(loginView,SIGNAL(loginSuccess()),this,SLOT(goWelcomeView()));
}
void MasterView::  goWelcomeView(){
    welcomeView = new WelcomeView();
    pushWidgetToStackView(welcomeView);
    connect(welcomeView,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomeView,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
    connect(welcomeView,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));
}
void MasterView:: goDoctorView(){
    doctorView = new DoctorView();
    pushWidgetToStackView(doctorView);
}
void MasterView:: goDepartmentView(){
    departmentmentView = new DepartmentView();
    pushWidgetToStackView(departmentmentView);
}
void MasterView:: goPatientView(){
    patientView = new PatientView();
    pushWidgetToStackView(patientView);
    connect(patientView,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));

}
void MasterView:: goPreviousView(){
    int count = ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());
        QWidget* widget = ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}
void MasterView::goPatientEditView(int rowNo){
    patientEditView = new PatientEditView(this,rowNo);
    pushWidgetToStackView(patientEditView);
    connect(patientEditView,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}
void MasterView::pushWidgetToStackView(QWidget* widget){
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    ui->labelTitle->setText(widget->windowTitle());
}


void MasterView::on_BtBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if(count>1){
        ui->BtBack->setEnabled(true);
    }else{
        ui->BtBack->setEnabled(false);
    }
    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if(title == "欢迎"){
        ui->BtOut->setEnabled(true);
    }else{
        ui->BtOut->setEnabled(false);
    }
}


void MasterView::on_BtOut_clicked()
{
    goPreviousView();
}


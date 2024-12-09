#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"
LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_Bt_login_clicked()
{
    QString status = IDatabase::getInstance().userLogin(ui->inputName->text(),ui->inputPwd->text());
    if(status=="loginOk"){
        emit loginSuccess();
    }

}


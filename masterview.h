#ifndef MASTERVIEW_H
#define MASTERVIEW_H
#include "departmentview.h"
#include "doctorview.h"
#include "loginview.h"
#include "patientview.h"
#include "patienteditview.h"
#include "welcomeview.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPreviousView();
    void goPatientEditView(int rowNo);
    void pushWidgetToStackView(QWidget* widget);
private slots:
    void on_BtBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_BtOut_clicked();

private:
    Ui::MasterView *ui;
    WelcomeView* welcomeView;
    DoctorView* doctorView;
    PatientView* patientView;
    DepartmentView* departmentmentView;
    LoginView* loginView;
    PatientEditView* patientEditView;
};
#endif // MASTERVIEW_H

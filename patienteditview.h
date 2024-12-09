#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H
#include <QDataWidgetMapper>
#include <QWidget>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr,int index = 0);
    ~PatientEditView();
signals:
  void goPreviousView();
private slots:
    void on_Bt_save_clicked();

    void on_Bt_cancel_clicked();

private:
    Ui::PatientEditView *ui;
    QDataWidgetMapper* dataMapper;
};

#endif // PATIENTEDITVIEW_H

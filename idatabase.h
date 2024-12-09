#ifndef IDATABASE_H
#define IDATABASE_H
#include <QSqlDatabase>
#include <QObject>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QDataWidgetMapper>
class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase &getInstance(){
        static IDatabase instance;
        return instance;
    }
    QString userLogin(QString userName,QString password);
    void ininDatabase();
private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &) = delete;
    void operator=(IDatabase const &) = delete;
    QSqlDatabase database;

public:
    QSqlTableModel* patientTabModel;
    QItemSelectionModel* thePatientSelection;
public:
    bool initPatientModel();
    bool searchPatient(QString filter);
    bool deletecurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();
    int addNewPatient();
signals:
};

#endif // IDATABASE_H

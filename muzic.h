
#ifndef MUZIC_H
#define MUZIC_H

#include <QMainWindow>
#include <QtWidgets>
class QStandardItemModel;
class QTableView;


QT_BEGIN_NAMESPACE
namespace Ui { class Muzic; }
QT_END_NAMESPACE

class Muzic : public QMainWindow

{
    Q_OBJECT

public:
    Muzic(QWidget *parent = nullptr);
    ~Muzic();
    void setupG();

public slots:
    void addItem();
    void updateRow(QStandardItem *item);

private:
    Ui::Muzic *ui;
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QDoubleSpinBox *doubleSpinBox;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QStandardItemModel *model;
    QTableView *view;
};

#endif // MUZIC_H

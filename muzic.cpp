
#include "muzic.h"
#include "./ui_muzic.h"
#include <QStandardItemModel>
#include <QTableView>

Muzic::Muzic(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Muzic),
    centralWidget(new QWidget),
    lineEdit(new QLineEdit),
    lineEdit_2(new QLineEdit),
    doubleSpinBox(new QDoubleSpinBox),
    spinBox(new QSpinBox),
    pushButton(new QPushButton("&Add")),
    model(new QStandardItemModel(this)),
    view(new QTableView)
{
    ui->setupUi(this);
    connect(pushButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateRow(QStandardItem*)));
    setupG();
}

Muzic::~Muzic()
{
    delete ui;
}

void Muzic::setupG()
{
    QLabel* composerLabel(new QLabel("Composer"));
    QLabel* titleLabel(new QLabel("Album title"));
    QLabel* costLabel(new QLabel("Replacement cost"));
    QLabel* ratingLabel(new QLabel("Rating"));

    doubleSpinBox->setRange(0,99999);
    spinBox->setRange(0,100);

    QStringList headerRow;
    headerRow.append("Composer");
    headerRow.append("Album title");
    headerRow.append("Replacement cost");
    headerRow.append("Rating");
    model->setHorizontalHeaderLabels(headerRow);
    view->setModel(model);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSortingEnabled(true);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(composerLabel, 0, 0);
    layout->addWidget(titleLabel, 0, 1);
    layout->addWidget(costLabel, 0, 2);
    layout->addWidget(ratingLabel, 0, 3);
    layout->addWidget(lineEdit, 1, 0);
    layout->addWidget(lineEdit_2, 1, 1);
    layout->addWidget(doubleSpinBox, 1, 2);
    layout->addWidget(spinBox, 1, 3);
    layout->addWidget(pushButton, 1, 4);
    layout->addWidget(view, 2, 0, 1, 5);
    layout->setRowMinimumHeight(2, 50);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    this->adjustSize();
}

void Muzic::addItem()
{
    // get values
    QString composer = lineEdit->text();
    QString album = lineEdit_2->text();
    double price = doubleSpinBox->value();
    int rating = spinBox->value();

    // reset GUI
    lineEdit->clear();
    lineEdit_2->clear();
    doubleSpinBox->setValue(0.0);
    spinBox->setValue(0);
    lineEdit->setFocus();

    // add to model
    QList<QStandardItem*> row;
    QStandardItem *composerItem = new QStandardItem(composer);
    QStandardItem *albumItem = new QStandardItem(album);
    QStandardItem *priceItem = new QStandardItem(QString::number(price));
    QStandardItem *ratingItem = new QStandardItem(QString::number(rating));
    row << composerItem << albumItem << priceItem << ratingItem;
    model->appendRow(row);
    updateRow(priceItem);  // to set colours
}

void Muzic::updateRow(QStandardItem *itemSelected)
{
    int col = itemSelected->column();
    if (col == 2)  // the cost has changed
    {
        double price = itemSelected->data(Qt::DisplayRole).toDouble();
        itemSelected->setData(QString::number(price, 'f', 2), Qt::DisplayRole);

        //ensure row is correct colour
        QColor colour = Qt::white;
        int row = itemSelected->row();
        if (price >= 250)
            colour = Qt::red;
        for (int col=0; col<4; col++)
            model->item(row, col)->setBackground(colour);
    }
}



#include "PersonInfo.h"
#include "qboxlayout.h"
#include "qchar.h"
#include "qfont.h"
#include "qlabel.h"
#include "qlayout.h"
#include "qlayoutitem.h"
#include "qpixmap.h"
#include "qpushbutton.h"
#include "qstandarditemmodel.h"
#include "qtableview.h"
#include "qwidget.h"
#include <QHeaderView>

PersonWidget::PersonWidget(const QWidget* parent)
{

    mainLayout = new QVBoxLayout();

    // sendbutton
    sendBtn = new QPushButton(QString("Send Message"), this);
    sendBtn->setFixedHeight(50);
    // Info
    infoTable                    = new QTableView(this);
    NonClickableItemModel* model = new NonClickableItemModel(9, 2);
    model->setItem(0, 0, new QStandardItem(QString("Tel")));
    model->setItem(0, 1, new QStandardItem(QString("64560")));
    model->setItem(1, 0, new QStandardItem(QString("Email")));
    model->setItem(1, 1, new QStandardItem(QString("HSDA@glodon.com")));
    model->setItem(2, 0, new QStandardItem(QString("Address")));
    model->setItem(2, 1, new QStandardItem(QString("Xi An")));
    model->setItem(3, 0, new QStandardItem(QString("More Information")));
    model->setItem(3, 1, new QStandardItem(QString("Press to check")));
    model->setItem(4, 0, new QStandardItem(QString("My OKR")));
    model->setItem(4, 1, new QStandardItem(QString("OKR")));
    model->setItem(5, 0, new QStandardItem(QString("Position")));
    model->setItem(5, 1, new QStandardItem(QString("Sky")));
    model->setItem(6, 0, new QStandardItem(QString("IDNumber")));
    model->setItem(6, 1, new QStandardItem(QString("0708-2560")));
    model->setItem(7, 0, new QStandardItem(QString("Department")));
    model->setItem(7, 1, new QStandardItem(QString("GOGOGO")));
    model->setItem(8, 0, new QStandardItem(QString("Corporation")));
    model->setItem(8, 1, new QStandardItem(QString("Glodon")));
    infoTable->setModel(model);
    infoTable->horizontalHeader()->hide();
    infoTable->verticalHeader()->hide();
    infoTable->setShowGrid(false);

    // Header
    nameLabel = new QLabel(QString("Hao Lixia"), this);
    nameLabel->setFont(QFont(QString("Microsoft YaHei"), 15));


    avaterLabel = new QLabel(this);

    avaterLabel->resize(100, 100);
    QPixmap avatorPixmap(avaterLabel->size());
    avatorPixmap.load(QString(":/image/person1.png"));

    avaterLabel->setPixmap(avatorPixmap.scaled(avaterLabel->size()));

    jobLabel = new QLabel(QString("Senior software Development Engineer"), this);
    jobLabel->setFont(QFont(QString("Microsoft YaHei"), 10));

    personLabel = new QLabel(this);

    nameLayout   = new QHBoxLayout();
    infoLayout   = new QVBoxLayout();
    headerLayout = new QHBoxLayout();

    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(personLabel);

    infoLayout->addLayout(nameLayout);
    infoLayout->addWidget(jobLabel);
    infoLayout->setSizeConstraint(QLayout::SetFixedSize);

    headerLayout->addLayout(infoLayout);
    headerLayout->addSpacerItem(new QSpacerItem(100, 0));
    headerLayout->addWidget(avaterLabel);

    mainLayout->addSpacerItem(new QSpacerItem(0, 80));
    mainLayout->addLayout(headerLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 40));
    mainLayout->addWidget(infoTable);
    mainLayout->addSpacerItem(new QSpacerItem(0, 40));
    mainLayout->addWidget(sendBtn);

    setLayout(mainLayout);
}

PersonWidget::~PersonWidget()
{
}
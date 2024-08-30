#include "LeftButtonWidget.h"
#include "qboxlayout.h"
#include "qchar.h"
#include "qlayoutitem.h"
#include "qpushbutton.h"
#include "qsizepolicy.h"
#include "qwidget.h"

LeftButtonWidget::LeftButtonWidget(QWidget* parent)
{
    vbLayout     = new QVBoxLayout();
    btnName      = new QPushButton(QString("Name"), this);
    btnMsg       = new QPushButton(QString("Msg"), this);
    btnEmail     = new QPushButton(QString("Email"), this);
    btnDoc       = new QPushButton(QString("Doc"), this);
    btnDate      = new QPushButton(QString("Date"), this);
    btnMeet      = new QPushButton(QString("Meet"), this);
    btnWorkbench = new QPushButton(QString("Workbench"), this);
    btnBook      = new QPushButton(QString("Book"), this);
    btnMore      = new QPushButton(QString("More"), this);

    btnName->setFixedHeight(50);
    btnMsg->setFixedHeight(50);
    btnEmail->setFixedHeight(50);
    btnDoc->setFixedHeight(50);
    btnDate->setFixedHeight(50);
    btnMeet->setFixedHeight(50);
    btnWorkbench->setFixedHeight(50);
    btnBook->setFixedHeight(50);
    btnMore->setFixedHeight(50);

    vbLayout->addWidget(btnName);
    vbLayout->addWidget(btnMsg);
    vbLayout->addWidget(btnEmail);
    vbLayout->addWidget(btnDoc);
    vbLayout->addWidget(btnDate);
    vbLayout->addWidget(btnMeet);
    vbLayout->addWidget(btnWorkbench);
    vbLayout->addWidget(btnBook);
    vbLayout->addWidget(btnMore);
    vbLayout->addItem(new QSpacerItem(0, 600, QSizePolicy::Preferred, QSizePolicy::Preferred));

    this->setLayout(vbLayout);
}

LeftButtonWidget::~LeftButtonWidget()
{
}
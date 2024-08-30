#include "MessageWidget.h"
#include "qboxlayout.h"
#include "qchar.h"
#include "qlistwidget.h"
#include "qwidget.h"
#include <QDebug>

MessageWidget::MessageWidget(QWidget* parent)
{
    msgList    = new QListWidget(this);
    chatWidget = new ChatWidget(this);
    mainLayout = new QHBoxLayout;

    icon = new QIcon(QString(":/image/person.png"));

    mainLayout->addWidget(msgList);
    mainLayout->addWidget(chatWidget);

    setLayout(mainLayout);
    InitConnect();
}
void MessageWidget::InitConnect()
{
    AddContactor("dsda", "DS");
    connect(chatWidget->m_SendBtn, &QPushButton::clicked, this, [this]() { this->chatWidget->SendInfo(msgList->currentItem()->text()); });
}
void MessageWidget::AddContactor(QString name, QString briefInfo)
{
    QListWidgetItem* item = new QListWidgetItem(msgList);
    item->setIcon(*icon);
    item->setText(name);
}

void MessageWidget::SetCurrentChat(QString name)
{
}

MessageWidget::~MessageWidget()
{
}
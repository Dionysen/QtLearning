#include "ChatWidget.h"
#include "qaction.h"
#include "qboxlayout.h"
#include "qchar.h"
#include "qicon.h"
#include "qlayoutitem.h"
#include "qlistwidget.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qsizepolicy.h"
#include "qtextedit.h"
#include "qvector.h"
#include "qwidget.h"
#include <QSpacerItem>

ChatWidget::ChatWidget(QWidget* parent)
{
    m_MsgList     = new QListWidget(this);
    m_ToolBar     = new QToolBar(this);
    m_InputWidget = new QTextEdit(this);
    m_SendBtn     = new QPushButton(QString("Send"), this);

    m_SendBtn->setFixedSize(100, 60);

    m_ToolBar->addAction(new QAction(QIcon(":/image/emoji.png"), QString(""), m_ToolBar));
    m_ToolBar->addAction(new QAction(QIcon(":/image/picture.png"), QString(""), m_ToolBar));
    m_ToolBar->addAction(new QAction(QIcon(":/image/phone.png"), QString(""), m_ToolBar));
    m_ToolBar->addAction(new QAction(QIcon(":/image/more.png"), QString(""), m_ToolBar));

    mainLayout = new QVBoxLayout();

    QHBoxLayout* senLayout = new QHBoxLayout();
    senLayout->addSpacerItem(new QSpacerItem(600, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));
    senLayout->addWidget(m_SendBtn);

    mainLayout->addWidget(m_MsgList);
    mainLayout->addWidget(m_ToolBar);
    mainLayout->addWidget(m_InputWidget);
    mainLayout->addLayout(senLayout);

    setLayout(mainLayout);
}

void ChatWidget::ConnectBtn()
{
}

void ChatWidget::UpdateMsgListByHistory(const QString name)
{
    m_MsgList->clear();
    auto currItem = m_ChatHistory.value(name);
    for (const auto i : *currItem)
    {
        m_MsgList->addItem(i);
    }
    m_InputWidget->clear();
}

void ChatWidget::SendInfo(const QString& name)
{
    QString info = m_InputWidget->toPlainText();
    if (info.isEmpty())
        return;

    if (m_ChatHistory.contains(name))
    {
        auto currItem = m_ChatHistory.value(name);
        currItem->push_back(info);
    }
    else
    {
        QSharedPointer<QVector<QString>> item = QSharedPointer<QVector<QString>>::create(QVector<QString>{ info });

        m_ChatHistory[name] = item;
    }
    UpdateMsgListByHistory(name);
}

ChatWidget::~ChatWidget()
{
}

#include "qboxlayout.h"
#include "qchar.h"
#include "qhash.h"
#include "qlistwidget.h"
#include "qmainwindow.h"
#include "qobjectdefs.h"
#include "qpushbutton.h"
#include "qtextedit.h"
#include "qvector.h"
#include "qwidget.h"
#include <QWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QSharedPointer>

class ChatWidget : public QWidget
{
    Q_OBJECT
  public:
    ChatWidget(QWidget* parent = nullptr);
    ~ChatWidget();

    void UpdateMsgListByHistory(const QString name);

  public slots:
    void SendInfo(const QString& name);

  private:
    void ConnectBtn();

  public:
    QListWidget* m_MsgList;
    QToolBar*    m_ToolBar;
    QTextEdit*   m_InputWidget;
    QPushButton* m_SendBtn;

    QVBoxLayout* mainLayout;

    QHash<QString, QSharedPointer<QVector<QString>>> m_ChatHistory;
};

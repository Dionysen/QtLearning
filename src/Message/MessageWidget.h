#include <QWidget>
#include "ChatWidget.h"
#include "qboxlayout.h"

class MessageWidget : public QWidget
{
  public:
    MessageWidget(QWidget* parent = nullptr);
    ~MessageWidget();


    void AddContactor(QString name, QString briefInfo);
    void SetCurrentChat(QString name);

    QListWidget* msgList;
    ChatWidget*  chatWidget;
    QHBoxLayout* mainLayout;

    QIcon* icon;

    void InitConnect();
};
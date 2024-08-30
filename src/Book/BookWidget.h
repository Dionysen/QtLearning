
#include <QTreeView>
#include <QPushButton>
#include "qboxlayout.h"
#include "qchar.h"
#include "qwidget.h"

#include "PersonInfo.h"
#include <QHBoxLayout>


class BookWidget : public QWidget
{
    Q_OBJECT
  public:
    BookWidget(QWidget* parent = nullptr);
    ~BookWidget();

  private:
    void ConnectBtn();

  signals:
    void OnTreeViewDoubleClicked(QString name);

  private:
    // treeview
    QTreeView* m_TreeView;

    // btn
    QPushButton* insertBtn;
    QPushButton* delBtn;

    // person info
    PersonWidget* persionInfoWidget;

    QHBoxLayout* mainLayout;
};
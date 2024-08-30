#pragma once
#include "qboxlayout.h"
#include "qobjectdefs.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include <QWidget>

class MainWindow;
class LeftButtonWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;

  public:
    LeftButtonWidget(QWidget* parent = nullptr);
    ~LeftButtonWidget();

  private:
    QPushButton* btnName;
    QPushButton* btnMsg;
    QPushButton* btnEmail;
    QPushButton* btnDoc;
    QPushButton* btnDate;
    QPushButton* btnMeet;
    QPushButton* btnWorkbench;
    QPushButton* btnBook;
    QPushButton* btnMore;

    QVBoxLayout* vbLayout;
};
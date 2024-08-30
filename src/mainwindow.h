#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qboxlayout.h"
#include "qmainwindow.h"
#include "qobjectdefs.h"
#include <QMainWindow>
#include <QPushbutton>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QTreeView>
#include "qstackedwidget.h"
#include <QStackedWidget>
#include "LeftButtonWidget.h"
#include "MessageWidget.h"
#include <QStackedLayout>
#include "BookWidget.h"
#include "LoginWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private:
    void ConnectMainMenu();

  private:
    LoginWidget* m_LoginWidget;
    // Center Widget
    QWidget*        centreWidget;
    QHBoxLayout*    mainLayout;
    QStackedWidget* mainStackWidget;

    // Main Menu
    LeftButtonWidget* leftBtnWidget;

    // Function widgets
    BookWidget*    bookWidget;
    MessageWidget* msgWidget;
};

#endif  // MAINWINDOW_H

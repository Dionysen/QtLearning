#include "mainwindow.h"
#include "QItemSelectionModel"
#include "qboxlayout.h"
#include "qchar.h"
#include "qglobal.h"
#include "qpushbutton.h"
#include "qstackedwidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // Centerwidget
    centreWidget = new QWidget(this);

    // leftbtn
    leftBtnWidget = new LeftButtonWidget(centreWidget);

    // stackwidget
    mainStackWidget = new QStackedWidget(centreWidget);

    bookWidget = new BookWidget(centreWidget);
    mainStackWidget->addWidget(bookWidget);

    msgWidget = new MessageWidget(centreWidget);
    mainStackWidget->addWidget(msgWidget);

    // Main Layout
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(leftBtnWidget);
    mainLayout->addWidget(mainStackWidget);

    centreWidget->setLayout(mainLayout);
    setCentralWidget(centreWidget);
    resize(1200, 800);

    m_LoginWidget = new LoginWidget(this);
    m_LoginWidget->show();
    // Connect
    ConnectMainMenu();
}

void MainWindow::ConnectMainMenu()
{
    connect(leftBtnWidget->btnBook, &QPushButton::clicked, this, [=]() { mainStackWidget->setCurrentWidget(bookWidget); });
    connect(leftBtnWidget->btnMsg, &QPushButton::clicked, this, [=]() { mainStackWidget->setCurrentWidget(msgWidget); });
    connect(bookWidget, &BookWidget::OnTreeViewDoubleClicked, this, [this](QString name) {
        msgWidget->AddContactor(name, "");
        mainStackWidget->setCurrentWidget(msgWidget);
    });
    connect(m_LoginWidget, &LoginWidget::LoginSignal, this, [&]() { this->show(); });
}

MainWindow::~MainWindow()
{
}

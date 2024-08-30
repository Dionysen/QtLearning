#include "SettingDialog.h"
#include "qboxlayout.h"
#include "qdialog.h"
#include "qformlayout.h"
#include "qlayoutitem.h"
#include "qlineedit.h"
#include "qwidget.h"
#include <QFormLayout>
#include <QLabel>

SettingDialog::SettingDialog(QWidget* parent)
    : m_CentralWidget(new QWidget(this))
    , QDialog(parent)
{
    this->resize(500, 300);
    this->setModal(true);
    this->setWindowTitle(QStringLiteral("网络代理设置"));

    // combox
    QComboBox* m_IsProxyComboBox = new QComboBox(m_CentralWidget);
    m_IsProxyComboBox->clear();
    m_IsProxyComboBox->insertItems(0, QStringList() << QStringLiteral("不使用代理") << QStringLiteral("使用代理"));

    QComboBox* m_ProxySettingComboBox = new QComboBox(m_CentralWidget);
    m_ProxySettingComboBox->clear();
    m_ProxySettingComboBox->insertItems(0, QStringList() << QStringLiteral("使用HTTP代理") << QStringLiteral("使用SOCKET代理"));

    m_IPEditor       = new QLineEdit(m_CentralWidget);
    m_PortEditor     = new QLineEdit(m_CentralWidget);
    m_UsernameEditor = new QLineEdit(m_CentralWidget);
    m_PasswordEditor = new QLineEdit(m_CentralWidget);

    // Label
    QFormLayout* mainFormLayout = new QFormLayout(m_CentralWidget);
    mainFormLayout->setSpacing(6);
    mainFormLayout->setContentsMargins(11, 11, 11, 11);
    mainFormLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* isProxy      = new QLabel(QStringLiteral("代理设置"), m_CentralWidget);
    QLabel* proxySetting = new QLabel(QStringLiteral("代理类型"), m_CentralWidget);
    QLabel* ip           = new QLabel(QStringLiteral("IP地址"), m_CentralWidget);
    QLabel* port         = new QLabel(QStringLiteral("端口"), m_CentralWidget);
    QLabel* username     = new QLabel(QStringLiteral("用户名"), m_CentralWidget);
    QLabel* password     = new QLabel(QStringLiteral("密码"), m_CentralWidget);


    // isProxy
    QHBoxLayout* isProxyLayout = new QHBoxLayout();
    isProxyLayout->addWidget(m_IsProxyComboBox);
    isProxyLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainFormLayout->setWidget(0, QFormLayout::LabelRole, isProxy);
    mainFormLayout->setLayout(0, QFormLayout::FieldRole, isProxyLayout);

    // Proxy Setting
    QHBoxLayout* proxySettingLayout = new QHBoxLayout();
    proxySettingLayout->addWidget(m_ProxySettingComboBox);
    proxySettingLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainFormLayout->setWidget(1, QFormLayout::LabelRole, proxySetting);
    mainFormLayout->setLayout(1, QFormLayout::FieldRole, proxySettingLayout);


    // ipAndPortLayout
    QHBoxLayout* ipAndPortLayout = new QHBoxLayout();
    ipAndPortLayout->addWidget(m_IPEditor);
    ipAndPortLayout->addWidget(port);
    ipAndPortLayout->addWidget(m_PortEditor);
    ipAndPortLayout->addSpacerItem(new QSpacerItem(100, 0));
    mainFormLayout->setWidget(2, QFormLayout::LabelRole, ip);
    mainFormLayout->setLayout(2, QFormLayout::FieldRole, ipAndPortLayout);

    // username and password
    mainFormLayout->setWidget(3, QFormLayout::LabelRole, username);
    mainFormLayout->setWidget(3, QFormLayout::FieldRole, m_UsernameEditor);
    mainFormLayout->setWidget(4, QFormLayout::LabelRole, password);
    mainFormLayout->setWidget(4, QFormLayout::FieldRole, m_PasswordEditor);

    setMaximumSize(600, 350);
    setLayout(mainFormLayout);
    mainFormLayout->setMargin(40);
    mainFormLayout->setHorizontalSpacing(20);
    mainFormLayout->setVerticalSpacing(15);
}
SettingDialog::~SettingDialog()
{
}
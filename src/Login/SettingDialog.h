
#include "qobjectdefs.h"
#include "qwidget.h"
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

class SettingDialog : public QDialog
{
    Q_OBJECT
  public:
    SettingDialog(QWidget* parent = nullptr);
    ~SettingDialog();

  private:
    QWidget* m_CentralWidget;

    QComboBox* m_IsProxyComboBox;
    QComboBox* m_ProxySettingComboBox;
    QLineEdit* m_IPEditor;
    QLineEdit* m_PortEditor;
    QLineEdit* m_UsernameEditor;
    QLineEdit* m_PasswordEditor;
};
#include "qobjectdefs.h"
#include "qpixmap.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <mutex>
#include "SettingDialog.h"
#include "QRCodeGenerator.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
  public:
    QPixmap GenQRCode();

    LoginWidget(QWidget* parent = nullptr);
    ~LoginWidget();

  signals:
    void LoginSignal();
    void UpdateQRCode(QPixmap pixmap);

  public slots:
    void ShowMainwindow();

  private:
    void InitConnect();

  private:
    QWidget* m_ParentWindow;

    CQR_Encode m_QREncode;

    QWidget*     m_CentralWidget;
    QPushButton* m_SettingBtn;
    QLabel*      m_Logo;
    QLabel*      m_QRCode;
    QLabel*      m_Text;
    QPushButton* m_Login;

    SettingDialog* m_SettingDialog;

    // mutex
    std::mutex              mtx;
    std::condition_variable cv;
    bool                    f_stopChecking = false;
};
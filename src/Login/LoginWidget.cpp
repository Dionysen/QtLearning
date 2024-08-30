#include "LoginWidget.h"
#include "qdatetime.h"
#include "qobject.h"
#include "qobjectdefs.h"
#include "qpixmap.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include <QDateTime>
#include <QTimer>
#include <QThread>
#include <thread>

LoginWidget::LoginWidget(QWidget* parent)
    : m_ParentWindow(parent)
{
    m_CentralWidget = new QWidget(this);

    this->resize(400, 600);
    this->setWindowTitle(QStringLiteral("企业微信"));
    this->setStyleSheet("background-color: white;");
    this->setFixedSize(400, 600);

    m_SettingDialog = new SettingDialog(this->m_CentralWidget);

    m_SettingBtn = new QPushButton(m_CentralWidget);
    m_Logo       = new QLabel(m_CentralWidget);
    m_QRCode     = new QLabel(m_CentralWidget);
    m_Text       = new QLabel(m_CentralWidget);

    // Login btn
    m_Login = new QPushButton(QStringLiteral("游客登陆"), m_CentralWidget);
    m_Login->setGeometry(QRect(20, 530, 100, 50));
    m_Login->setStyleSheet("background: transparent; border: none;");
    // Setting btn
    m_SettingBtn->setGeometry(QRect(330, 530, 50, 50));
    m_SettingBtn->setStyleSheet("background: transparent; border: none;");
    QPixmap buttonPixmap       = QPixmap(":/image/button.png");
    QPixmap scaledPixmapButton = buttonPixmap.scaled(m_SettingBtn->size(), Qt::IgnoreAspectRatio);
    m_SettingBtn->setIcon(QIcon(scaledPixmapButton));

    // Text
    m_Text->setGeometry(QRect(50, 490, 300, 30));
    QFont font;
    font.setPointSize(11);
    m_Text->setFont(font);
    m_Text->setAlignment(Qt::AlignCenter);
    m_Text->setText(QStringLiteral("请使用手机企业微信扫码登录"));

    // QRCode
    m_QRCode->setGeometry(QRect(60, 170, 280, 280));
    // QPixmap pixmap(":/image/qrcode.png");
    QPixmap pixmap        = GenQRCode();
    QPixmap scaledPixmap2 = pixmap.scaled(m_QRCode->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_QRCode->setPixmap(scaledPixmap2);

    // Logo
    m_Logo->setGeometry(QRect(50, 40, 300, 91));
    QImage  img(":/image/text.png");
    QPixmap pixmap3       = QPixmap::fromImage(img);
    QPixmap scaledPixmap3 = pixmap3.scaled(m_Logo->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_Logo->setPixmap(scaledPixmap3);

    // Connect
    InitConnect();
}

void LoginWidget::InitConnect()
{
    connect(m_SettingBtn, &QPushButton::clicked, this, [this]() { m_SettingDialog->show(); });
    // 时间二维码
    std::thread t = std::thread([&]() {
        std::unique_lock<std::mutex> lock(mtx);
        f_stopChecking = false;
        while (!f_stopChecking)
        {
            QPixmap pixmap       = GenQRCode();
            QPixmap scaledPixmap = pixmap.scaled(m_QRCode->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            emit UpdateQRCode(scaledPixmap);

            auto timeout = std::chrono::seconds(1);
            cv.wait_for(lock, timeout, [&] { return f_stopChecking; });
        }
    });
    t.detach();

    connect(m_Login, &QPushButton::clicked, this, [this]() {
        if (this->m_ParentWindow)
        {
            this->m_ParentWindow->show();
            this->hide();
        }
    });

    // connect(m_Login, &QPushButton::clicked, this, &LoginWidget::ShowMainwindow);

    connect(this, &LoginWidget::UpdateQRCode, this, [this](QPixmap pixmap) {
        m_QRCode->setGeometry(QRect(60, 170, 280, 280));
        m_QRCode->setPixmap(pixmap);
    });
}

void LoginWidget::ShowMainwindow()
{
    if (this->parentWidget())
    {
        this->parentWidget()->show();
        this->hide();
    }
}

QPixmap LoginWidget::GenQRCode()
{
    int     levelIndex   = 1;
    int     versionIndex = 0;
    bool    bExtent      = true;
    int     maskIndex    = -1;
    QString encodeString = QDateTime::currentDateTime().toString();

    bool success = m_QREncode.EncodeData(levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data());


    int qrImageSize = m_QREncode.m_nSymbleSize;

    int encodeImageSize = qrImageSize + (QR_MARGIN * 2);

    // 初始缩放因子为1
    int scaleFactor = 1;
    // 不足280则放大
    if (encodeImageSize < 280)
    {
        scaleFactor = static_cast<int>(ceil(280.0 / encodeImageSize));
        encodeImageSize *= scaleFactor;
    }

    QImage encodeImage(encodeImageSize, encodeImageSize, QImage::Format_Mono);
    encodeImage.fill(1);

    // 创建二维码图像（不缩放）
    // for (int i = 0; i < qrImageSize; i++)
    //     for (int j = 0; j < qrImageSize; j++)
    //         if (qrEncode.m_byModuleData[i][j])
    //             encodeImage.setPixel(i + QR_MARGIN, j + QR_MARGIN, 0);

    // 创建二维码图像
    for (int i = 0; i < qrImageSize; i++)
    {
        for (int j = 0; j < qrImageSize; j++)
        {
            if (m_QREncode.m_byModuleData[i][j])
            {
                // 使用缩放比例设置像素
                for (int x = 0; x < scaleFactor; ++x)
                {
                    for (int y = 0; y < scaleFactor; ++y)
                    {
                        encodeImage.setPixel((i * scaleFactor) + x + QR_MARGIN * scaleFactor, (j * scaleFactor) + y + QR_MARGIN * scaleFactor,
                                             0);  // 设置为黑色
                    }
                }
            }
        }
    }

    QPixmap pix = QPixmap::fromImage(encodeImage);

    return pix;
}

LoginWidget::~LoginWidget()
{
    std::lock_guard<std::mutex> lock(mtx);
    f_stopChecking = true;
    cv.notify_all();
}

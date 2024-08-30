#pragma once

#include "qboxlayout.h"
#include <QTableView>
#include <QLabel>
#include "qlabel.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qtableview.h"
#include <QFormLayout>
#include <QWidget>
#include <QStandardItemModel>
#include "BookTreeList.h"

class NonClickableItemModel : public QStandardItemModel
{
  public:
    NonClickableItemModel(int rows, int columns, QObject* parent = nullptr)
        : QStandardItemModel(rows, columns, parent)
    {
    }
    // 覆盖 flags 函数，使所有项不可点击
    Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
        return defaultFlags & ~Qt::ItemIsSelectable & Qt::ItemIsEnabled;
    }
};

class PersonWidget : public QWidget
{
    Q_OBJECT
  public:
    PersonWidget(const QWidget* parent = nullptr);
    ~PersonWidget();
    void CreatePersonInfo(int row, int column, MyTreeNode::PersonInfo info)
    {
    }
    void ShowInfo();

  private:
    QVBoxLayout* mainLayout;

    QPushButton* sendBtn;
    QTableView*  infoTable;

    QLabel* nameLabel;
    QLabel* avaterLabel;
    QLabel* jobLabel;
    QLabel* personLabel;

    QHBoxLayout* nameLayout;
    QVBoxLayout* infoLayout;
    QHBoxLayout* headerLayout;
};
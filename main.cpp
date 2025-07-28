#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateTime> // 添加此行以使用 QDateTime::currentMSecsSinceEpoch()
#include <QObject>   // 确保 connect 函数可用
#include <QTableView> // 修改：使用 QTableView 替代 QListView
#include <QStringListModel> // 新增：作为 QListView 的数据源
#include <QStandardItemModel> // 新增：支持多列数据展示
#include <QTimer> // 新增：用于定时刷新行情
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建主窗口
    MainWindow w;
    QWidget *centralWidget = new QWidget(&w);
    w.setCentralWidget(centralWidget);

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    // 设置主窗口大小为 800x600
    w.resize(800, 600);

    // 左侧行情模块
    QWidget *leftWidget = new QWidget(&w);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    // 修改：使用 QTableView 展示行情数据
    QTableView *marketTableView = new QTableView(leftWidget); // 修改：使用 QTableView
    QStandardItemModel *marketModel = new QStandardItemModel(0, 7, leftWidget); // 支持 7 列数据
    marketTableView->setModel(marketModel);

    // 设置表头
     marketModel->setHorizontalHeaderItem(0, new QStandardItem("代码")); // 修改：表头改为英文
     marketModel->setHorizontalHeaderItem(1, new QStandardItem("价格格"));
     marketModel->setHorizontalHeaderItem(2, new QStandardItem("买一"));
     marketModel->setHorizontalHeaderItem(3, new QStandardItem("卖一"));
     marketModel->setHorizontalHeaderItem(4, new QStandardItem("持仓"));
     marketModel->setHorizontalHeaderItem(5, new QStandardItem("成交"));
     marketModel->setHorizontalHeaderItem(6, new QStandardItem("Time"));

    // 设置表头
   
//    marketModel->setHorizontalHeaderItem(0, new QStandardItem(QString::fromUtf8("代码")));
//    marketModel->setHorizontalHeaderItem(1, new QStandardItem(QString::fromUtf8("最新价")));
//    marketModel->setHorizontalHeaderItem(2, new QStandardItem(QString::fromUtf8("买一")));
//    marketModel->setHorizontalHeaderItem(3, new QStandardItem(QString::fromUtf8("卖一")));
//    marketModel->setHorizontalHeaderItem(4, new QStandardItem(QString::fromUtf8("持仓量")));
//    marketModel->setHorizontalHeaderItem(5, new QStandardItem(QString::fromUtf8("成交量")));
//    marketModel->setHorizontalHeaderItem(6, new QStandardItem(QString::fromUtf8("时间")));



    QPushButton *generateButton = new QPushButton("Generate Random Market Data", leftWidget); // 修改：按钮文本改为英文

    // 定义生成行情数据的函数
    auto generateMarketData = [&]() {
        qsrand(QDateTime::currentMSecsSinceEpoch()); // 使用当前时间作为随机种子
        marketModel->removeRows(0, marketModel->rowCount()); // 清空旧数据

        for (int i = 0; i < 5; ++i) { // 生成 5 条行情数据
            QList<QStandardItem*> rowData;
            QString variety = QString("IF2509-%1").arg(i + 1); // 品种
            double latestPrice = 1000 + qrand() % 100; // 最新价
            double buyOne = latestPrice - (qrand() % 10) / 100.0; // 买一
            double sellOne = latestPrice + (qrand() % 10) / 100.0; // 卖一
            int position = qrand() % 1000; // 持仓量
            int volume = qrand() % 1000; // 成交量
            QString latestTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"); // 最新时间

            rowData << new QStandardItem(variety)
                    << new QStandardItem(QString::number(latestPrice, 'f', 2))
                    << new QStandardItem(QString::number(buyOne, 'f', 2))
                    << new QStandardItem(QString::number(sellOne, 'f', 2))
                    << new QStandardItem(QString::number(position))
                    << new QStandardItem(QString::number(volume))
                    << new QStandardItem(latestTime);

            marketModel->appendRow(rowData);
        }
    };

    // 使用 connect 连接按钮点击信号到槽函数
    QObject::connect(generateButton, &QPushButton::clicked, generateMarketData);

    // 创建定时器，每秒刷新一次行情
    QTimer *refreshTimer = new QTimer(&w);
    QObject::connect(refreshTimer, &QTimer::timeout, generateMarketData);
    refreshTimer->start(1000); // 每秒触发一次

    // 设置控件对齐方式和大小策略
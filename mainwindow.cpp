#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

#include <QApplication>
#include <QSplitter>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateTime> // 添加此行以使用 QDateTime::currentMSecsSinceEpoch()
#include <QObject>   // 确保 connect 函数可用

MainWindow::~MainWindow()
{
}

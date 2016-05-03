#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit>
#include <QtWebKit/QtWebKit>
#include <QtWebView/QtWebView>
#include <QProgressBar>
#include <QUrl>
#include <QtDebug>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QWebFrame>
#include "dialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setUrlSlot(QUrl);
    void setTitleSlot(QString);
    void browserWebSlot();
    void deleteProgressBarSlot(bool);
    void sourceCodeSlot();
    void on_webView_linkClicked(QUrl);

private:
    Ui::MainWindow *ui;
    QProgressBar *progress;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->progress=new QProgressBar;
    ui->statusBar->addWidget(this->progress);
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    QObject::connect(ui->webView,SIGNAL(linkClicked(QUrl)),this,SLOT(on_webView_linkClicked(QUrl)));
    QObject::connect(ui->webView,SIGNAL(loadProgress(int)),this->progress,SLOT(setValue(int)));
    QObject::connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(setUrlSlot(QUrl)));
    QObject::connect(ui->webView,SIGNAL(titleChanged(QString)),this,SLOT(setTitleSlot(QString)));
    QObject::connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(browserWebSlot()));
    QObject::connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(deleteProgressBarSlot(bool)));
    QObject::connect(ui->sourceAction,SIGNAL(triggered()),this,SLOT(sourceCodeSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_webView_linkClicked(QUrl url)
{
    ui->webView->load(url);
    ui->lineEdit->setText(url.toString());
}

void MainWindow::setUrlSlot(QUrl url)
{
    ui->lineEdit->setText(url.toString());
}

void MainWindow::setTitleSlot(QString title)
{
    this->setWindowTitle(title);
}

void MainWindow::browserWebSlot()
{
    ui->webView->load(QUrl(ui->lineEdit->text()));
}

void MainWindow::deleteProgressBarSlot(bool ok)
{
    if(ok)
    {
        delete this->progress;
        this->progress=NULL;
        this->ui->statusBar->showMessage("Load Finished",5*1000);
    }
}

void MainWindow::sourceCodeSlot()
{
    QString context= ui->webView->page()->currentFrame()->toHtml();
    Dialog *dialog=new Dialog;
    dialog->setWebSource(context);
    dialog->show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateUi();
    filedir = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete filedir;
}

void MainWindow::CreateUi()
{
    selectfolder = new QPushButton("选择文件夹",this);
    connect(selectfolder,&QPushButton::clicked,this,&MainWindow::DisplayFileList);
    confirm = new QPushButton("确认",this);
    connect(confirm,&QPushButton::clicked,this,&MainWindow::RenameFlies);
    oldname = new QLineEdit(this);
    newname = new QLineEdit(this);
    label1 = new QLabel("需要替换的文字：",this);
    label2 = new QLabel("替换的文字：",this);
    textbrowser = new QTextBrowser(this);
    layout = new QGridLayout(this);

    layout->addWidget(label1,0,0);
    layout->addWidget(oldname,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(newname,0,3);
    layout->addWidget(selectfolder,0,4);
    layout->addWidget(confirm,1,4);
    layout->addWidget(textbrowser,2,0,1,5);

    widget = new QWidget(this);
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle("FileRename");
}

void MainWindow::SelectFolder()
{
    filepath = QFileDialog::getExistingDirectory(this,"选择文件夹");
    if(filedir != nullptr) delete filedir;
    filedir = new QDir(filepath);
    filedir->setFilter(QDir::Files);
    filelist = filedir->entryList();
}

void MainWindow::DisplayFileList()
{
    SelectFolder();
    if(filelist.size() == 0)
    {
        textbrowser->insertPlainText("此文件夹没有文件\n");
        textbrowser->moveCursor(QTextCursor::MoveOperation::End);
        return;
    }
    else
    {
        textbrowser->insertPlainText("=============================重命名前==================================\n");
        textbrowser->moveCursor(QTextCursor::MoveOperation::End);
        for(int i=0; i<filelist.size(); i++)
        {
            textbrowser->insertPlainText(filelist[i]+"\n");
            textbrowser->moveCursor(QTextCursor::MoveOperation::End);
        }
        textbrowser->insertPlainText("\n");
        textbrowser->moveCursor(QTextCursor::MoveOperation::End);
    }
}

void MainWindow::RenameFlies()
{
    if(filedir == nullptr)
    {
        textbrowser->insertPlainText("请先选择对应文件夹\n");
        textbrowser->moveCursor(QTextCursor::MoveOperation::End);
        return;
    }
    QString oldfilename, newfilename;
    for(auto &filename : filelist)
    {
        oldfilename = filedir->absoluteFilePath(filename);
        QFile file(oldfilename);
        newfilename = oldfilename.replace(oldname->text(),newname->text());
        if (!file.rename(newfilename) && oldfilename!=newfilename)
        {
            QMessageBox msg(QMessageBox::Warning,"提示","重命名失败");
            msg.exec();
            return;
        }
    }
    textbrowser->insertPlainText("=============================重命名后==================================\n");
    textbrowser->moveCursor(QTextCursor::MoveOperation::End);
    filedir->setPath(filepath);
    filelist = filedir->entryList();
    for(auto &filename : filelist)
    {
        textbrowser->insertPlainText(filename+"\n");
        textbrowser->moveCursor(QTextCursor::MoveOperation::End);
    }
    textbrowser->insertPlainText("\n");
    textbrowser->moveCursor(QTextCursor::MoveOperation::End);
}

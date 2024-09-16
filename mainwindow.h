#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QListWidget>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateUi();
    void SelectFolder();
    void DisplayFileList();
    void RenameFlies();

private:
    Ui::MainWindow *ui;
    QPushButton *selectfolder;
    QPushButton *confirm;
    QLineEdit *oldname;
    QLineEdit *newname;
    QLabel *label1;
    QLabel *label2;
    QTextBrowser *textbrowser;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QGridLayout *layout;
    QWidget *widget;

    QString filepath;
    QDir *filedir;
    QStringList filelist;
};
#endif // MAINWINDOW_H

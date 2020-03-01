#include "mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    text1 = new QTextEdit;
    QFont font;
    font.setPixelSize(30);
    text1->setFont(font);//设置text1字体大小为30
//    QColor color;
//    color.setRgb(255, 0, 0);
//    text1->setTextColor(color);//设置颜色为红色
    this->setCentralWidget(text1);//将这个TextEdit放到对话框的中间

    file = this->menuBar()->addMenu("文件");//在菜单栏加入一个菜单项
    edit = this->menuBar()->addMenu("编辑");
    buile = this->menuBar()->addMenu("构建");
    help = this->menuBar()->addMenu("帮助");

    file_open = new QAction("打开", this);//建立一个Action
//    file_open->setShortcut(QKeySequence(tr("Ctrl+O")));
    file_open->setShortcut(tr("Ctrl+O"));//将open菜单的快捷方式设置为Command + O

    file_save = new QAction("保存", this);
    file_save->setShortcut(tr("Ctrl+S"));

    file_exit = new QAction("退出", this);
    file_exit->setShortcut(tr("Ctrl+Q"));

    file->addAction(file_open);//将file_open这个Action添加到file菜单下面
    file->addAction(file_save);
    file->addSeparator();//加入一个分隔符
    file->addAction(file_exit);

    edit_copy = new QAction("拷贝", this);
    edit_copy->setShortcut(tr("Ctrl+C"));
    edit->addAction(edit_copy);

    edit_paste = new QAction("粘贴", this);
    edit_paste->setShortcut(tr("Ctrl+V"));
    edit->addAction(edit_paste);

    edit_cut = new QAction("剪切", this);
    edit_cut->setShortcut(tr("Ctrl+X"));
    edit->addAction(edit_cut);

    edit_selectAll = new QAction("全选", this);
    edit_selectAll->setShortcut(tr("Ctrl+A"));
    edit->addAction(edit_selectAll);

    build_compile = new QAction("构建文件", this);
    build_compile->setShortcut(tr("Ctrl+B"));
    buile->addAction(build_compile);

    build_run = new QAction("运行", this);
    build_run->setShortcut(tr("Ctrl+R"));
    buile->addAction(build_run);

    help_about = new QAction("关于", this);
    help_about->setShortcut(tr("Ctrl+H"));
    help->addAction(help_about);


    //Qt的消息槽机制
    connect(file_open, SIGNAL(triggered()), this, SLOT(on_open()));
    connect(file_save, SIGNAL(triggered()), this, SLOT(on_save()));

    connect(file_exit, SIGNAL(triggered()), this, SLOT(on_exit()));
    connect(edit_copy, SIGNAL(triggered()), this, SLOT(on_copy()));
    connect(edit_paste, SIGNAL(triggered()), this, SLOT(on_paste()));
    connect(edit_cut, SIGNAL(triggered()), this, SLOT(on_cut()));
    connect(edit_selectAll, SIGNAL(triggered()), this, SLOT(on_selectAll()));

    connect(build_compile, SIGNAL(triggered()), this, SLOT(on_compile()));
    connect(build_run, SIGNAL(triggered()), this, SLOT(on_run()));

    connect(help_about, SIGNAL(triggered()), this, SLOT(on_about()));
}

MainWindow::~MainWindow()
{
    delete text1;
}

void MainWindow::on_open()
{
    filename =  QFileDialog::getOpenFileName();//打开一个标准对话框，返回文件打开路径

    if(filename.isEmpty()) return;

    QString content;

//    filename.toStdString().data();//将QString转化为 const char *
    FILE *file = fopen(filename.toStdString().data(), "r");
    if(file == nullptr) {
        QMessageBox::information(this, "错误", "打开文件失败");
    } else {
        while (!feof(file)) {
            char buf[1024] = {0};
            fgets(buf, sizeof(buf), file);
            content += buf;
        }
        fclose(file);
        text1->setText(content);
    }
}

void MainWindow::on_save()
{
    filename = QFileDialog::getSaveFileName();
    if(filename.isEmpty()) return;

    FILE *file = fopen(filename.toStdString().data(), "w");
    if(file == nullptr) {
        QMessageBox::information(this, "错误", "打开文件失败");
    } else {
//        text1->toPlainText().toStdString().data();//字符串转换为 const char *
        fputs(text1->toPlainText().toStdString().data(), file);
        fclose(file);
    }
}

void MainWindow::on_about()
{
    QMessageBox::information(this, "关于", "版权所有");
}

void MainWindow::on_exit()
{
    exit(0);
}

void MainWindow::on_copy()
{
    text1->copy();
}

void MainWindow::on_paste()
{
    text1->paste();
}

void MainWindow::on_cut()
{
    text1->cut();
}

void MainWindow::on_selectAll()
{
    text1->selectAll();
}

void MainWindow::on_compile()
{
//    QString content;
//    FILE *file = fopen(filename.toStdString().data(), "r");
//    if(file == nullptr) return;

//    while(!feof(file)) {
//        char buf[1024] = {0};
//        fgets(buf, sizeof (buf), file);
//        content += buf;
//    }
//    fclose(file);

//    content.replace("整数", "int").replace("主函数", "main");

//    QString destname = filename;

//    destname.replace(".e", ".c");
//    file = fopen(destname.toStdString().data(), "w");
//    fputs(content.toStdString().data(), file);
//    fclose(file);

    QString destname = filename;
    destname.replace(".c", ".exe");//将filename中的.c退换为.exe
    QString command = "gcc -o " + destname + " " + filename;
    system(command.toStdString().data());

}

void MainWindow::on_run()
{
    QString destname = filename;
    destname.replace(".c", ".exe");//将filename中的.c退换为.exe

    system(destname.toStdString().data());
}


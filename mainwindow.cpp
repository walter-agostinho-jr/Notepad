#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionNovo, &QAction::triggered, this, &MainWindow::novoDoc);
    connect(ui->actionAbrir, &QAction::triggered, this, &MainWindow::abrirDoc);
    connect(ui->actionSalvar, &QAction::triggered, this, &MainWindow::salvarDoc);
    connect(ui->actionSalvar_como, &QAction::triggered, this, &MainWindow::salvarComo);
    connect(ui->actionCopiar, &QAction::triggered, this, &MainWindow::copiar);
    connect(ui->actionColar, &QAction::triggered, this, &MainWindow::colar);
    connect(ui->actionCortar, &QAction::triggered, this, &MainWindow::cortar);
    connect(ui->actionRefazer, &QAction::triggered, this, &MainWindow::refazer);
    connect(ui->actionDesfazer, &QAction::triggered, this, &MainWindow::desfazer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::novoDoc()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::abrirDoc()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a File");

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text))
        {
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::salvarDoc()
{
    if(mFilename.isEmpty())
    {
        salvarComo();
        return;
    }

    QFile sFile(mFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

void MainWindow::salvarComo()
{
    QString file = QFileDialog::getSaveFileName(this, "Open a File");

    if(!file.isEmpty())
    {
        mFilename = file;
        salvarDoc();
    }
}

void MainWindow::copiar()
{
    ui->textEdit->copy();
}

void MainWindow::colar()
{
    ui->textEdit->paste();
}

void MainWindow::cortar()
{
    ui->textEdit->cut();
}

void MainWindow::refazer()
{
    ui->textEdit->redo();
}

void MainWindow::desfazer()
{
    ui->textEdit->undo();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QFontDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    ui->textBrowser->setReadOnly(false);
    file_path = QFileDialog::getOpenFileName(this, tr("choose file"), "/home");
    if (file_path == "") {
        return;
    }
    QFile file(file_path);
    file.open(QIODevice::ReadWrite);
    QString line = file.readAll();
    file.close();

    ui->textBrowser->setHtml(line);
}


void MainWindow::on_actionSave_triggered()
{
    QString text = ui->textBrowser->toHtml();
    if(!text.isEmpty()){
        QFile file(file_path);
        QTextStream in(&file);
        in.setCodec("UTF-8");
        file.open(QIODevice::WriteOnly);
        in << text;
        file.close();
    }
}


void MainWindow::on_actionUndo_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    ui->textBrowser->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    ui->textBrowser->redo();
}


void MainWindow::on_actionCut_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    ui->textBrowser->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    ui->textBrowser->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    ui->textBrowser->paste();
}


void MainWindow::on_actionFont_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    QFont initialFont = ui->textBrowser->font();      // initial font face
    QTextCursor cursor = ui->textBrowser->textCursor();

    auto pointsize = ui->textBrowser->fontPointSize();

    if(pointsize) initialFont.setPointSize(pointsize);      // initial font size
    bool ok;
    QFont font = QFontDialog::getFont(&ok, initialFont, this, tr("Font Properties"), QFontDialog::DontUseNativeDialog);
    /*! If user clicks OK then change to selected font with properties*/
    if (!ok) {
        return;
    }
    ui->textBrowser->setCurrentFont(font);
}


void MainWindow::on_actionZoom_in_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    QTextCursor cursor = ui->textBrowser->textCursor();
    qreal fontSize = cursor.charFormat().fontPointSize();
    if(fontSize == 0){
        fontSize = 16;
    }
    QTextCharFormat fmt;
    fmt.setFontPointSize(fontSize+1);
    cursor.mergeCharFormat(fmt);
}


void MainWindow::on_actionZoom_out_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;
    QTextCursor cursor = ui->textBrowser->textCursor();
    qreal fontSize = cursor.charFormat().fontPointSize();
    if(fontSize == 0){
        fontSize = 16;
    }
    QTextCharFormat fmt;
    fmt.setFontPointSize(fontSize - 1);
    cursor.mergeCharFormat(fmt);
}


void MainWindow::on_actionOnline_Help_triggered()
{
    QMessageBox::information(0,"Help","Kindly write to us at hussainganie388@gmail.com");
}


void MainWindow::on_actionContact_us_triggered()
{

    QMessageBox::information(0,"Contact us","Please feel free to reachout at hussainganie388@gmail.com");
}


void MainWindow::on_actionAbout_Notepad_triggered()
{
    QMessageBox::information(0, "About us", "NOTEPAD - Edit text \n Version: 0.0.1");
}


void MainWindow::on_actionBold_triggered()
{
    if(!ui->textBrowser)
        return;
    QTextCursor cursor = ui->textBrowser->textCursor();
    /*
     * charFormat returns the format of the character before the position
     * So, we interchange the ancr and position
    */
    int pos = cursor.position();
    int ancr = cursor.anchor();
    if (pos < ancr) {
        cursor.setPosition(pos, QTextCursor::MoveAnchor);
        cursor.setPosition(ancr, QTextCursor::KeepAnchor);
    }
    //qDebug()<<"pos : ancr"<<pos<<ancr;
    bool isBold = cursor.charFormat().font().bold();
    /*
     * If the font-weight value is bold then
     * it will change it to normal else bold.
    */
    QTextCharFormat fmt;
    fmt.setFontWeight(isBold ? QFont::Normal : QFont::Bold);
    cursor.mergeCharFormat(fmt);
    ui->textBrowser->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionSuperscript_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;

    auto cursor = ui->textBrowser->textCursor();

    QTextCharFormat fmt;

    fmt.setVerticalAlignment((cursor.charFormat().verticalAlignment() == QTextCharFormat::AlignSuperScript)?\
                                 QTextCharFormat::AlignNormal : \
                                 QTextCharFormat::AlignSuperScript
                                 ); // Ternary operator for isSuperscripted ? alignNormal : alignSuperscript

    cursor.mergeCharFormat(fmt);
    ui->textBrowser->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionSubsscript_triggered()
{
    if(!ui->textBrowser || ui->textBrowser->isReadOnly())
        return;

    auto cursor = ui->textBrowser->textCursor();

    QTextCharFormat fmt;

    fmt.setVerticalAlignment((cursor.charFormat().verticalAlignment() == QTextCharFormat::AlignSubScript)?\
                                 QTextCharFormat::AlignNormal : \
                                 QTextCharFormat::AlignSubScript
                                 );

    cursor.mergeCharFormat(fmt);
    ui->textBrowser->mergeCurrentCharFormat(fmt);
}


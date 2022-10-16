#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString file_path;

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionFont_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionOnline_Help_triggered();

    void on_actionContact_us_triggered();

    void on_actionAbout_Notepad_triggered();

    void on_actionBold_triggered();

    void on_actionSuperscript_triggered();

    void on_actionSubsscript_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

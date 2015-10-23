#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QMenu>
#include <QFileDialog>
#include "preprocwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void showThisMenu();
    ~MainWindow();

private:
    QVBoxLayout* layoutV;

    QPushButton* btnStart;
    QPushButton* btnLoad;
    QPushButton* btnPreProc;
    QPushButton* btnProc;
    QPushButton* btnPostProc;

    void clean();
signals:

public slots:
    void startMenu();
    void loadPreProc();
    void backToMainMenu();

private slots:
    void openFile();

};

#endif // MAINWINDOW_H

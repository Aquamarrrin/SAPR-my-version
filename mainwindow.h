#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include "chooseprocwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton* btnStart;
    QPushButton* btnSave;
    QPushButton* btnLoad;


signals:

public slots:
    void startMenu();

};

#endif // MAINWINDOW_H

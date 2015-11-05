#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "construction.h"
#include "preprocwindow.h"
#include "proccalculations.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void showThisMenu();
    void takeValues(QVector<Rod> rods, QVector<Load> loads);
    ~MainWindow();

private:
    QVBoxLayout* layoutV;

    QPushButton* btnStart;
    QPushButton* btnLoad;
    QPushButton* btnPreProc;
    QPushButton* btnProc;
    QPushButton* btnPostProc;

    QVector<Rod> rods;
    QVector<Load> loads;

    QVector<QVector<float> > matrixA;
    QVector<float> matrixB;
    QVector<float> matrixD;

    void clean();
signals:

public slots:
    void startMenu();
    void loadPreProc();
    void loadProc();
    void backToMainMenu();

private slots:
    void openFile();
    void saveFile();

};

#endif // MAINWINDOW_H

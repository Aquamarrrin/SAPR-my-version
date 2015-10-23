#ifndef PREPROCWINDOW_H
#define PREPROCWINDOW_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QHeaderView>
#include <QSlider>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "construction.h"

class PreProcWindow : public QWidget
{
    Q_OBJECT
public:
    //PreProcWindow(const QString filePath = "" ,QWidget *parent = 0);
    explicit PreProcWindow(QWidget *parent = 0);

private:
    QVBoxLayout* layoutV;
    QHBoxLayout* layoutH;

    QPushButton* btnDraw;

    QSlider* numNodes;
    QSlider* numLoads;

    QTableWidget* tableRodSettings;
    QTableWidget* tableLoad;

    Construction* constr;

    QVector<QString> fileOfTablesText;

    bool isFilled(int row, QTableWidget *table);
    bool isNotEmpty(int row, QTableWidget *table);
    bool isExist(int row, int column, QTableWidget *table);

    void parseFileOfTablesText();

signals:

public slots:
    void createTableRod(int nNodes);
    void createTableLoad(int nLoads);
    void showConstruction();
    void backToMenu();

private slots:
    void saveFile();
    void openFile();


};

#endif // PREPROCWINDOW_H

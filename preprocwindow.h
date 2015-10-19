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
#include "construction.h"

class PreProcWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PreProcWindow(QWidget *parent = 0);

private:
    QVBoxLayout* layoutV;
    QHBoxLayout* layoutH;

    QPushButton* btnDraw;

    QSlider* numNodes;
    QSlider* numLoads;

    QTableWidget* tableNode;
    QTableWidget* tableRod;
    QTableWidget* tableRodSettings;
    QTableWidget* tableLoad;

    Construction* constr;

    bool isFilled(int row, QTableWidget *table);

signals:

public slots:
    void createTableRod(int nNodes);
    void createTableLoad(int nLoads);
    void showConstruction();


};

#endif // PREPROCWINDOW_H

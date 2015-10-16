#ifndef CHOOSEPROCWINDOW_H
#define CHOOSEPROCWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include "preprocwindow.h"

class ChooseProcWindow : public QWidget
{
    Q_OBJECT
public:
    ChooseProcWindow(QWidget *parent = 0);
    ~ChooseProcWindow();

private:
    QPushButton* btnPreProc;
    QPushButton* btnProc;
    QPushButton* btnPostProc;

signals:

public slots:
    void loadPreProc();

};

#endif // CHOOSEPROCWINDOW_H

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
#include <QRegExp>
#include "mainwindow.h"
#include "construction.h"

class PreProcWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PreProcWindow(QString filePath = "" ,QWidget *parent = 0);
    ~PreProcWindow();
    Construction* getConstr();
    void openTmpFile();

private:
    QGridLayout* layoutG;

    QSlider* numNodes; //Кол-во строк в таблице стержней
    QSlider* numLoads; //Кол-во строк в таблице нагрузок

    QTableWidget* tableRodSettings; //Таблица стержней и их параметров
    QTableWidget* tableLoad; //Таблица нагрузок на узлы в стержнях

    Construction* constr; //Виджет конструкции, где и происходитвся отрисовка
    QVector<QString> fileOfTablesText; //Вектор , содержащий текст открытого файла

    bool isFilled(int row, QTableWidget *table); //Проверка на заполненность строки в таблице
    bool isNotEmpty(int row, QTableWidget *table); //Проверка на не пустоту строки в таблице
    bool isExist(int row, int column, QTableWidget *table); //Проверка на существование элемента в таблице
    bool isNumber(const QString &str); //Проверка на соответствие строки числу

    void parseFileOfTablesText(); //Парсер файла
    //void setValuesOfTableRods(); //Передаём вектор стержней и записываем его параметры в соответствую таблицу

signals:

public slots:
    void createTableRod(int nNodes); //Создаём таблицу стержней
    void createTableLoad(int nLoads); //Создаём таблицу нагрузок
    void showConstruction(); //Передаём все необходимые параметры в конструкцию и отрисовываем её
    void backToMenu(); //Возврат в меню выбора процессоров

private slots:
    void saveFile(); //Сохранение файла
    void openFile(); //Открытие файла
    void addRod(); //Добавляем стержень по нажатию кнопки
    void addLoad(); //Добавляем нагрузку по нажатию кнопки
    void delRod(); //Удалить стержень по нажатию кнопки
    void delLoad(); //Удалить нагрузку по нажатию кнопки


};

#endif // PREPROCWINDOW_H

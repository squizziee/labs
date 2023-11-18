#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "C:\Users\HP\Downloads\QCustomPlot\qcustomplot\qcustomplot.h"
#include "hashmap.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<double> table_sizes = {16, 64, 128, 2048};
       QVector<double> times;

       for (int table_size : table_sizes)
       {
           hash_table<int, QString> hash_table(table_size);

           srand(time(NULL));

           int ke;

           for (int i = 0; i < table_size; ++i)
           {
               int key = rand() % 1000;
               QString value = QString::number(i);
               hash_table.insert(key, value);
               ke = key;
           }

           auto start = std::chrono::high_resolution_clock::now();

           hash_table.get(rand());

           auto end = std::chrono::high_resolution_clock::now();

           auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

           times.push_back(duration.count());
           qDebug() << duration.count();
       }
       ui->widget->xAxis->setRange(16, 2048);
       ui->widget->yAxis->setRange(0, 200);

       ui->widget->addGraph();
       ui->widget->graph(0)->setData(table_sizes, times);
       ui->widget->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


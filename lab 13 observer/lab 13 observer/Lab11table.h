#pragma once

#include <QtWidgets/QMainWindow>
#include "lab13observer.h"

class Lab11table : public QMainWindow
{
    Q_OBJECT

public:
    Lab11table(QWidget *parent = nullptr);
    ~Lab11table();

private:
    Ui::lab13observerClass ui;
};

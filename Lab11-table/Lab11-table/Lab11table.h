#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab11table.h"

class Lab11table : public QMainWindow
{
    Q_OBJECT

public:
    Lab11table(QWidget *parent = nullptr);
    ~Lab11table();

private:
    Ui::Lab11tableClass ui;
};

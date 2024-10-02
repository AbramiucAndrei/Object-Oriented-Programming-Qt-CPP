#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab13observer.h"

class lab13observer : public QMainWindow
{
    Q_OBJECT

public:
    lab13observer(QWidget *parent = nullptr);
    ~lab13observer();

private:
    Ui::lab13observerClass ui;
};

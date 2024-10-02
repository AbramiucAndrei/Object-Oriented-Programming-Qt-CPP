#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab14.h"

class lab14 : public QMainWindow
{
    Q_OBJECT

public:
    lab14(QWidget *parent = nullptr);
    ~lab14();

private:
    Ui::lab14Class ui;
};

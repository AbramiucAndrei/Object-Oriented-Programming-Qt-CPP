#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EXAMEN.h"

class EXAMEN : public QMainWindow
{
    Q_OBJECT

public:
    EXAMEN(QWidget *parent = nullptr);
    ~EXAMEN();

private:
    Ui::EXAMENClass ui;
};

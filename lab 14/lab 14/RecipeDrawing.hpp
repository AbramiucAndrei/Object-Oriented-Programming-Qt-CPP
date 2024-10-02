#pragma once

#include "Service.hpp"

#include <QDialog>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPaintEvent>

class RecipeDrawing : public QDialog, public Observer {
private:
    Service &service;
    QLabel *count_label;
    QVBoxLayout *main_layout;

    const int RECT_WIDTH = 20;
    const int RECT_HEIGHT = 40;
    const int PENCIL_WIDTH = 5;

public:
    explicit RecipeDrawing(Service &service, QWidget *parent = nullptr)
            : QDialog(parent), service(service) {
        service.addListener(this);
        main_layout = new QVBoxLayout(this);
        count_label = new QLabel("Number of medicamente: 0");
        main_layout->addWidget(count_label);
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        auto const &farmacy = service.getAllRecipe();

        const int SPACE_BETWEEN_RECTS = 10;
        int currentX = SPACE_BETWEEN_RECTS;
        int currentY = height() - RECT_HEIGHT;

        for (const auto &medicament : farmacy) {
            painter.setPen(QPen(Qt::blue, PENCIL_WIDTH));
            painter.setBrush(QBrush{Qt::blue, Qt::SolidPattern});

            painter.drawRect(currentX, currentY, RECT_WIDTH, RECT_HEIGHT);

            currentX += RECT_WIDTH + SPACE_BETWEEN_RECTS;
        }

        count_label->setText("Number of medicamente: " + QString::number(farmacy.size()));
    }

    void update() override {
        repaint();
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        service.deleteListener(this);
    }
};
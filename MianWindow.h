#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MianWindow.h"

class MianWindow : public QMainWindow
{
    Q_OBJECT

public:
    MianWindow(QWidget *parent = nullptr);
    ~MianWindow();

private:
    Ui::MianWindowClass ui;
};

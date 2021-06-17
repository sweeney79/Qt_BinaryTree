#pragma once

#include <QWidget>
#include "ui_Add_Node.h"

class Add_Node : public QWidget
{
    Q_OBJECT

public:
    Add_Node(QWidget *parent = Q_NULLPTR);
    ~Add_Node();

    QPushButton* get_btn();
    QString get_name();
    float get_value();
    unsigned get_type();
    QString get_parent_name();
    void clear_parent_list();
    void add_to_parent_list(QString);

private:
    Ui::Add_Node ui;
};

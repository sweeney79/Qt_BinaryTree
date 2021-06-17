#pragma once

#include <QWidget>
#include "ui_Node_Float.h"
#include "Node.h"

class Node_Float : public Node
{
    Q_OBJECT

public:
  Node_Float(QString, float, bool = false);
  ~Node_Float();
  QPushButton* get_btn();

public slots:
  void update_float_value(int);
  void emit_delete_node();

private:
  Ui::Node_Float ui;
};

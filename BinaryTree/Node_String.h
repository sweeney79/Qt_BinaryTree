#pragma once

#include "ui_Node_String.h"
#include "Node.h"

class Node_String : public Node
{
    Q_OBJECT

public:
  Node_String(QString, float, bool = false);
  ~Node_String();
   QPushButton* get_btn();

public slots:
  void update_string_value(const QString &);
  void emit_delete_node();

private:
  Ui::Node_String ui;
  bool check_for_empty_input(const QString);
};

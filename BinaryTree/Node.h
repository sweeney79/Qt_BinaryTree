#pragma once
#include <QWidget>
#include <QPushButton>

// Node is a base class, meant to be inherited by Node_Float and Node_String
class Node : public QWidget
{
  Q_OBJECT

public:
  Node(QWidget *parent = Q_NULLPTR);
  virtual ~Node();

  virtual QPushButton* get_btn() { return NULL; };

  // name get/set
  void set_node_name(QString);
  QString get_node_name();

  // value get/set
  void set_node_value(float);
  float get_node_value();

  // child node getters
  Node* get_left_node();
  Node* get_right_node();

  // child node setters
  void set_left_node(Node*);
  void set_right_node(Node*);

  // parent node get/set
  void set_parent_node(Node*);
  Node* get_parent_node();

  bool is_root;
  unsigned height_in_tree;

public slots:
  void remove_child(Node*);

private:
  // storage variables
  QString name;
  float value;

  Node* node_parent;
  Node* child_left;
  Node* child_right;

signals:
  void delete_node(Node*);
  void update_buttons();
};
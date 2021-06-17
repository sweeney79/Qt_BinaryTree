#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TreeView.h"
#include "BinaryTree_Model.h"
#include "Add_Node.h"

class TreeView : public QMainWindow
{
  Q_OBJECT

public:
  TreeView(QWidget *parent = Q_NULLPTR);
  ~TreeView();

  void show_binary_tree(Node*, unsigned);
  void setup_binary_tree_display(BinaryTree_Model*, unsigned);

  // add node
  Add_Node* form_add_node;

private:
  BinaryTree_Model* binary_tree;
  unsigned max_height;
  //QTimer* timer;

  // tree display
  Ui::TreeViewClass ui;
  QMap<QString, QHBoxLayout*> map_of_hboxes;
  QList<QSpacerItem*> list_of_layout_spacers;

  void create_tree_layout();
  void enable_delete_btn_on_nodes();
  void add_node_at_height(Node*, unsigned);
  void paintEvent(QPaintEvent *);
  void update_add_node_controls();
  bool check_new_node_name(QString node_name);

public slots:
  void update_delete_controls();
  void show_add_node_controls();
  void create_new_node();
};

#pragma once
#include <Node.h>
#include "Node_Float.h"
#include "Node_String.h"
#include <QList>

class BinaryTree_Model : public QObject
{
  Q_OBJECT

public:
  BinaryTree_Model(Node*);
  virtual ~BinaryTree_Model();

  void create_slider_node(QString, float);
  void create_string_node(QString, float);
  bool add_node_to_parent(QString, QString);

  Node* root_node;
  QMap<QString, Node*> map_of_nodes_in_tree;

public slots:
  void remove_node(Node* node);

  // could be used to help sort nodes by value
  static bool valueComparison(Node* n1, Node*n2)
  {
    return n1->get_node_value() < n2->get_node_value();
  }
};


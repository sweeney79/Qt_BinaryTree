
#include <QtWidgets/QApplication>
#include "Node_Float.h"
#include "Node_String.h"
#include "BinaryTree_Model.h"
#include "TreeView.h"

#define MAX_TREE_HEIGHT 5

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // create a new binary tree with a root node
  BinaryTree_Model* binary_tree = new BinaryTree_Model(new Node_Float("Root", 7.0, true));

  // create nodes
  binary_tree->create_slider_node("Node A", 5.0);
  binary_tree->create_slider_node("Node B", 20.0);
  binary_tree->create_slider_node("Node C", 2.0);
  binary_tree->create_slider_node("Node D", 4.0);
  binary_tree->create_string_node("Node E", 10.0);
  binary_tree->create_string_node("Node F", 15.0);
  binary_tree->create_string_node("Node G", 1.0);
  binary_tree->create_string_node("Node H", 13.0);
  binary_tree->create_string_node("Node I", 16.0);
  binary_tree->create_string_node("Node J", 3.0);

  // add nodes to the binary tree
  binary_tree->add_node_to_parent("Node A", "Root");
  binary_tree->add_node_to_parent("Node B", "Root");
  binary_tree->add_node_to_parent("Node C", "Node A");
  binary_tree->add_node_to_parent("Node D", "Node A");
  binary_tree->add_node_to_parent("Node E", "Node B");
  binary_tree->add_node_to_parent("Node F", "Node B");
  binary_tree->add_node_to_parent("Node G", "Node C");
  binary_tree->add_node_to_parent("Node J", "Node D");
  binary_tree->add_node_to_parent("Node H", "Node F");
  binary_tree->add_node_to_parent("Node I", "Node F");

  // display the binary tree
  TreeView w;
  w.setup_binary_tree_display(binary_tree, MAX_TREE_HEIGHT);
  w.show_binary_tree(binary_tree->root_node, 0);
  w.show();
  return a.exec();
}

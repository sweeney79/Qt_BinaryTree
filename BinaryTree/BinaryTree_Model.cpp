#include "BinaryTree_Model.h"


BinaryTree_Model::BinaryTree_Model(Node* root)
{
  root_node = NULL;

  if (root)
  {
    root_node = root;
    map_of_nodes_in_tree.insert(root_node->get_node_name(), root_node);
  }
}


BinaryTree_Model::~BinaryTree_Model()
{
  if (root_node)
  {
    delete root_node;
    root_node = NULL;
  }
}

// add a new node to the tree by assigning it a parent node
bool BinaryTree_Model::add_node_to_parent(QString node_name, QString parent_node_name)
{
  if (!root_node) return false;
  if (!map_of_nodes_in_tree.contains(node_name) && !map_of_nodes_in_tree.contains(parent_node_name)) return false;

  // get nodes
  Node* parent_node = map_of_nodes_in_tree.value(parent_node_name);
  Node* child_node = map_of_nodes_in_tree.value(node_name);

  if (parent_node && child_node)
  {
    // check if there's an open spot on parent's the left
    if (!parent_node->get_left_node())
    {
      // add it to the left side
      parent_node->set_left_node(child_node);
      child_node->set_parent_node(parent_node);
      return true;
    }
    else if (!parent_node->get_right_node())
    {
      // add it to the right side
      parent_node->set_right_node(child_node);
      child_node->set_parent_node(parent_node);
      return true;
    }
  }
}

void BinaryTree_Model::create_slider_node(QString name, float value)
{
  Node* new_node = new Node_Float(name, value);
  map_of_nodes_in_tree.insert(new_node->get_node_name(), new_node);
}

void BinaryTree_Model::create_string_node(QString title, float value)
{
  Node* new_node = new Node_String(title, value);
  map_of_nodes_in_tree.insert(new_node->get_node_name(), new_node);
}

void BinaryTree_Model::remove_node(Node* node)
{
  // remove node from model
  map_of_nodes_in_tree.remove(node->get_node_name());
}
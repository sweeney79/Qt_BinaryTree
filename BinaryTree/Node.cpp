#include "Node.h"


Node::Node(QWidget *parent)
  : QWidget(parent)
{
  node_parent = NULL;
  child_left = NULL;
  child_right = NULL;
}


Node::~Node()
{
  if (child_left)
  {
    delete child_left;
    child_left = NULL;
  }

  if (child_right)
  {
    delete child_right;
    child_right = NULL;
  }
}

// parent node
void Node::set_parent_node(Node* node)
{
  node_parent = node;
}

Node* Node::get_parent_node()
{
  return node_parent;
}

// getters - child notes
Node* Node::get_left_node()
{
  return child_left;
}

Node* Node::get_right_node()
{
  return child_right;
}

// setters - child notes
void Node::set_left_node(Node* node)
{
  if (node)
  {
    child_left = node;
  }
}

void Node::remove_child(Node* node)
{
  if (child_left && node->get_node_name().compare(child_left->get_node_name()) == 0)
  {
    delete child_left;
    child_left = NULL;
    emit update_buttons();
  }
  else if (child_right && node->get_node_name().compare(child_right->get_node_name()) == 0)
  {
    delete child_right;
    child_right = NULL;
    emit update_buttons();
  }
}

void Node::set_right_node(Node* node)
{
  if (node)
  {
    child_right = node;
  }
}

// name
void Node::set_node_name(QString name)
{
  this->name = name;
}

QString Node::get_node_name()
{
  return name;
}

// value
void Node::set_node_value(float value)
{
  this->value = value;
}

float Node::get_node_value()
{
  return value;
}
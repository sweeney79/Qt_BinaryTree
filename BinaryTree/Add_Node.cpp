#include "Add_Node.h"

Add_Node::Add_Node(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

Add_Node::~Add_Node()
{
}

QPushButton* Add_Node::get_btn()
{
  return ui.btn_create_node;
}

QString Add_Node::get_name()
{
  return ui.lineEdit_name->text();
}

float Add_Node::get_value()
{
  return ui.doubleSpinBox_value->value();
}

unsigned Add_Node::get_type()
{
  return ui.comboBox_type->currentIndex();
}

QString Add_Node::get_parent_name()
{
  return ui.comboBox_parent->currentText();
}

void Add_Node::clear_parent_list()
{
  ui.comboBox_parent->clear();
}

void Add_Node::add_to_parent_list(QString name)
{
  ui.comboBox_parent->addItem(name);
}
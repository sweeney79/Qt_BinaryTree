#include "Node_Float.h"

Node_Float::Node_Float(QString name, float value, bool root)
{
    ui.setupUi(this);
    is_root = root;

    // react to the slider changing
    connect(ui.slider_value, SIGNAL(valueChanged(int)), this, SLOT(update_float_value(int)));

    // update this node's variables
    set_node_name(name);
    set_node_value(value);

    // update widget display
    int converted_value = value * 100;
    ui.slider_value->setValue(converted_value);
    ui.label_name->setText(name);

    // hide and disable displays not needed at creation
    ui.btn_delete->setVisible(false);
    ui.btn_delete->setEnabled(false);
    connect(ui.btn_delete, SIGNAL(clicked()), this, SLOT(emit_delete_node()));
}

Node_Float::~Node_Float()
{
}

void Node_Float::emit_delete_node()
{
  emit delete_node(this);
}

QPushButton* Node_Float::get_btn()
{
  return ui.btn_delete;
}

// called when the slider changes
void Node_Float::update_float_value(int num)
{
  // slider is to the nearest tenths (has 10000 values for values 0.00 - 100.00)
  // convert from int to float by dividing by 100
  float converted_value = num / 100.0;

  // update the display label
  ui.label_slider_value->setText(QString::number(converted_value));
  
  // update this node's value
  set_node_value(converted_value);
}
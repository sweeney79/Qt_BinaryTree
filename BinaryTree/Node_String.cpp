#include "Node_String.h"

Node_String::Node_String(QString name, float value, bool root)
{
    ui.setupUi(this);
    is_root = root;

    // set-up  a validator to restrict user input to 0.00 - 100.00
    QRegularExpression rx("100\\.00|[1-9][0-9]?\\.\\d{2}");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui.lineEdit_value->setValidator(validator);

    // update this node's variables
    set_node_name(name);
    set_node_value(value);

    // update widget display
    ui.label_name->setText(name);
    ui.lineEdit_value->setText(QString::number(value));

    // when the string value changes, store the value
    connect(ui.lineEdit_value, SIGNAL(textChanged(const QString &)), this, SLOT(update_string_value(const QString &)));

    // hide and disable displays not needed at creation
    ui.label_zero_message->setVisible(false);
    ui.btn_delete->setVisible(false);
    ui.btn_delete->setEnabled(false);
    connect(ui.btn_delete, SIGNAL(clicked()), this, SLOT(emit_delete_node()));
}

Node_String::~Node_String()
{
}

void Node_String::emit_delete_node()
{
  emit delete_node(this);
}

QPushButton* Node_String::get_btn()
{
  return ui.btn_delete;
}

// react to the user changing the string
void Node_String::update_string_value(const QString &str)
{
  float f = QString(str).toFloat();

  bool is_empty = check_for_empty_input(str);

  if (is_empty)
  {
    set_node_value(1.00);
  }
  else
  {
    set_node_value(f);
  }
}

bool Node_String::check_for_empty_input(const QString str)
{
  if (str.isEmpty())
  {
    // show the zero message
    ui.label_zero_message->setVisible(true);
    ui.lineEdit_value->setStyleSheet("background-color:rgb(97, 97, 97);\
                                      color:white;\
                                      border:1px solid white; ");
    return true;
  }
  else
  {
    // hide the zero message
    ui.label_zero_message->setVisible(false);
    ui.lineEdit_value->setStyleSheet("background-color:rgb(97, 97, 97);\
                                      color:white;\
                                      border:none; ");
    return false;
  }
}
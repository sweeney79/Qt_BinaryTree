#include "TreeView.h"
#include <QLineF>
#include <QPainter>
#include <QMessageBox>

TreeView::TreeView(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  form_add_node = new Add_Node();
  form_add_node->setAttribute(Qt::WA_QuitOnClose, false);
  connect(ui.btn_add_node, SIGNAL(clicked()), this, SLOT(show_add_node_controls()));
  connect(form_add_node->get_btn(), SIGNAL(clicked()), this, SLOT(create_new_node()));
}

TreeView::~TreeView()
{
  if (binary_tree)
  {
    delete binary_tree;
    binary_tree = NULL;
  }

  if (form_add_node)
  {
    delete form_add_node;
    form_add_node = NULL;
  }
}

void TreeView::setup_binary_tree_display(BinaryTree_Model* tree, unsigned max)
{
  binary_tree = tree;
  ui.label_num_nodes->setText("Number of Tree Nodes: " + QString::number(binary_tree->map_of_nodes_in_tree.size()));

  max_height = max;
  ui.label_max_height->setText("Max Tree Height: " + QString::number(max_height));
  
  create_tree_layout();
  enable_delete_btn_on_nodes();
}

void TreeView::enable_delete_btn_on_nodes()
{
  for (Node* node : binary_tree->map_of_nodes_in_tree.values())
  {
    // get the node's delete button
    QPushButton* button = node->get_btn();

    // if node has no children
    if (!node->is_root && !node->get_left_node() && !node->get_right_node())
    {
      // enable delete functionality
      button->setVisible(true);
      button->setEnabled(true);

      // tell the tree view to remove node
      connect(node, SIGNAL(delete_node(Node*)), binary_tree, SLOT(remove_node(Node*)));

      // tell the parent node that the node is gone (set it to NULL)
      connect(node, SIGNAL(delete_node(Node*)), node->get_parent_node(), SLOT(remove_child(Node*)));

      // enable new delete buttons
      connect(node->get_parent_node(), SIGNAL(update_buttons()), this, SLOT(update_delete_controls()));
    }
    else
    {
      // enable delete functionality
      button->setVisible(false);
      button->setEnabled(false);
    }
  }
}

void TreeView::create_tree_layout()
{
  for (int i = 0; i <= max_height; i++)
  {
    // create horizontal layout to use as a new tree height
    QHBoxLayout* horizontal_layout = new QHBoxLayout(ui.frame_tree);
    horizontal_layout->setObjectName("height_" + QString::number(i));
    map_of_hboxes.insert(horizontal_layout->objectName(), horizontal_layout);

    // add horizontal layout to vertical layout 
    ui.verticalLayout_frame->addLayout(horizontal_layout);

    // create a spacer for the layout
    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    list_of_layout_spacers.append(spacer);

    // add spacer to vertical layout 
    ui.verticalLayout_frame->addSpacerItem(spacer);
  }
}

void TreeView::show_binary_tree(Node* node, unsigned level)
{
  unsigned next_level = level + 1;

  if (node)
  {
    // add node to the tree at the right level
    add_node_at_height(node, level);
  }

  // if the node has a left child, add it
  if (node->get_left_node())
  {
    show_binary_tree(node->get_left_node(), next_level);
  }

  // if the node has a right child, add it
  if (node->get_right_node())
  {
    show_binary_tree(node->get_right_node(), next_level);
  }
}

void TreeView::add_node_at_height(Node* node, unsigned num)
{
  QString hbox_at_level = "height_" + QString::number(num);
  QHBoxLayout* temp_layout_helper = map_of_hboxes.value(hbox_at_level);

  if (temp_layout_helper)
  {
    temp_layout_helper->addWidget(node);
    node->height_in_tree = num;
  }
}

void TreeView::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  QPen pen;
  pen.setColor(QColor(181,109,30));
  pen.setWidth(5);
  painter.setPen(pen);

  for (Node* node : binary_tree->map_of_nodes_in_tree.values())
  {
    // draw a line between the node and it's left child node
    if (node && node->get_left_node())
    {
      QPoint start = node->mapToGlobal(node->rect().center() + QPoint(0, node->height() / 2));
      QPoint end = node->get_left_node()->mapToGlobal(node->get_left_node()->rect().center() - QPoint(0, node->get_left_node()->height() / 2));
      painter.drawLine(mapFromGlobal(start), mapFromGlobal(end));
    }
    // draw a line between the node and it's right child node
    if (node && node->get_right_node())
    {
      QPoint start = node->mapToGlobal(node->rect().center() + QPoint(0, node->height() / 2));
      QPoint end = node->get_right_node()->mapToGlobal(node->get_right_node()->rect().center() - QPoint(0, node->get_right_node()->height() / 2));
      painter.drawLine(mapFromGlobal(start), mapFromGlobal(end));
    }
  }
}

void TreeView::update_delete_controls()
{
  ui.label_num_nodes->setText("Number of Tree Nodes: " + QString::number(binary_tree->map_of_nodes_in_tree.size()));

  // update list of nodes with no children
  update_add_node_controls();

  // recheck if other delete buttons can be enabled
  enable_delete_btn_on_nodes();

  // repaint display
  repaint();
  QApplication::processEvents();
}

void TreeView::update_add_node_controls()
{
  form_add_node->clear_parent_list();

  // update list of possible parent nodes
  for (Node* node : binary_tree->map_of_nodes_in_tree.values())
  {
    // if node has no children
    if (!node->get_left_node() || !node->get_right_node())
    {
      // and node is not at the maxiumum height
      if (node->height_in_tree < max_height)
      {
        form_add_node->add_to_parent_list(node->get_node_name());
      }
    }
  }
}

void TreeView::show_add_node_controls()
{
  update_add_node_controls();

  if (form_add_node)
  {
    form_add_node->show();
    form_add_node->raise();
  }
}

void TreeView::create_new_node()
{
  bool result = false;

  // get node name
  QString node_name = form_add_node->get_name();

  // check that the name is valid
  result = check_new_node_name(node_name);

  if (result)
  {
    // get node value
    float value = form_add_node->get_value();

    // get slider/string type
    switch (form_add_node->get_type())
    {
    case 0:
      binary_tree->create_slider_node(node_name, value);
      break;
    case 1:
      binary_tree->create_string_node(node_name, value);
      break;
    }

    // get selected parent node name
    QString parent_name = form_add_node->get_parent_name();

    // add the node to the tree
    result = binary_tree->add_node_to_parent(node_name, parent_name);

    if (result)
    {
      // update the tree
      show_binary_tree(binary_tree->root_node, 0);

      // update potential new node parent list
      update_add_node_controls();

      // recheck if other delete buttons can be disabled/enabled
      enable_delete_btn_on_nodes();

      ui.label_num_nodes->setText("Number of Tree Nodes: " + QString::number(binary_tree->map_of_nodes_in_tree.size()));

      // repaint display
      this->update();
    }
  }
}

bool TreeView::check_new_node_name(QString node_name)
{
  if (node_name.isEmpty())
  {
    QMessageBox msg;
    msg.setText("You must give the node a name.");
    msg.exec();
    return false;
  }

  // check that name isn't being used already
  for (Node* node : binary_tree->map_of_nodes_in_tree.values())
  {
    if (node->get_node_name().compare(node_name) == 0)
    {
      QMessageBox msg;
      msg.setText("The node must have a unique name.");
      msg.exec();
      return false;
    }
  }

  return true;
}
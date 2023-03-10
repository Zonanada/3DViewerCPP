/// \file
#include "mainwindow.h"

#include "./ui_mainwindow.h"

/**
 * @brief Construct a new Main Window:: Main Window object
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  //    glwidget = new GLWidget;
  //    glwidget->show();
  ui->setupUi(this);
  connect(this, &MainWindow::setState, ui->openGLWidget, &Rendering::setState);
  connect(this, &MainWindow::setFilename, ui->openGLWidget, &Rendering::setFilename);
  connect(this, &MainWindow::setLook, ui->openGLWidget, &Rendering::setLook);
  connect(this, &MainWindow::setProjection, ui->openGLWidget, &Rendering::setProjection);
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief the state of the object is collected
 *
 * @return state_st*
 */
state_st *MainWindow::getState() {
  state_st *state = new state_st;
  state->rx = ui->rotation_x->value();
  state->ry = ui->rotation_y->value();
  state->rz = ui->rotation_z->value();
  state->scale = ui->scale->value();
  state->tx = ui->transfer_x->value();
  state->ty = ui->transfer_y->value();

  return state;
}

void MainWindow::on_rotation_x_valueChanged() {if(ui->fileName->text() != "") emit setState(getState()); }

void MainWindow::on_rotation_y_valueChanged() {if(ui->fileName->text() != "") emit setState(getState()); }

void MainWindow::on_rotation_z_valueChanged() {if(ui->fileName->text() != "") emit setState(getState()); }

void MainWindow::on_transfer_x_valueChanged() {if(ui->fileName->text() != "") emit setState(getState()); }

void MainWindow::on_transfer_y_valueChanged() {if(ui->fileName->text() != "") emit setState(getState()); }

void MainWindow::on_scale_valueChanged() {if(ui->fileName->text() != "") emit setState(getState()); }

/**
 * @brief will take the name and send it to rendering
 *
 */
void MainWindow::on_openFile_clicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Выберете файл", QDir::homePath());
  std::string strName = fileName.toStdString();

  if (strName.size() > 0) {
    char *name = (char *)calloc(strName.size()+1, sizeof(char));
    for (int i = 0; i < fileName.size(); i++) {
      name[i] = strName[i];
      name[i+1] = '\0';
    }
    ui->fileName->setText(fileName);

    vertex_index_st *data = new vertex_index_st;
    reading(name, data);
    std::string vertexCount =
        "Вершин: " + std::to_string(data->vertex.memory / 3);
    std::string ribsCount = "Рёбер: " + std::to_string(data->index.memory / 2);

    ui->countVertex->setText(QString::fromStdString(vertexCount));
    ui->countIndex->setText(QString::fromStdString(ribsCount));
    delete data;

    emit setFilename(name);
    emit setState(getState());
  }
}

/**
 * @brief creates a struct with object state
 *
 * @return look_st* with fortune
 */
look_st *MainWindow::getLook() {
  look_st *look = new look_st;
  look->rW = ui->rW->value();
  look->gW = ui->gW->value();
  look->bW = ui->bW->value();
  look->aW = ui->aW->value();

  look->rL = ui->rL->value();
  look->gL = ui->gL->value();
  look->bL = ui->bL->value();

  look->rV = ui->rV->value();
  look->gV = ui->gV->value();
  look->bV = ui->bV->value();

  look->widthLine = ui->widthLine->value();
  look->widthVertex = ui->widthVertex->value();
  return look;
}

void MainWindow::on_rW_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_gW_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_bW_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_aW_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_rV_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_gV_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_bV_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_rL_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_gL_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_bL_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_widthLine_valueChanged() { emit setLook(getLook()); }

void MainWindow::on_widthVertex_valueChanged() { emit setLook(getLook()); }

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    ui->rotation_x->setValue((pos_mouse_y - event->position().y()) / 100);
    ui->rotation_y->setValue((pos_mouse_y - event->position().x()) / 100);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    pos_mouse_x = event->position().x();
    pos_mouse_y = event->position().y();
}



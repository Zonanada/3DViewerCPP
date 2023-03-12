
#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(this, &MainWindow::setData, ui->openGLWidget, &GLWidget::getData);
  connect(this, &MainWindow::update_render, ui->openGLWidget, &GLWidget::update_render);
  emit setData(&data);
//  connect(this, &MainWindow::setLook, ui->openGLWidget, &Rendering::setLook);
//  connect(this, &MainWindow::setProjection, ui->openGLWidget, &Rendering::setProjection);
}

MainWindow::~MainWindow() { delete ui; }

State MainWindow::getState() {
  State state;
  state.rotate_by_x = ui->rotation_x->value();
  state.rotate_by_y = ui->rotation_y->value();
  state.rotete_by_z = ui->rotation_z->value();
  state.scale = ui->scale->value();
  state.transfer_by_x = ui->transfer_x->value();
  state.transfer_by_y = ui->transfer_y->value();
  state.transfer_by_z = ui->transfer_z->value();
  return state;
}

void output_vertex(std::vector <double> &nums) {
    for (auto it : nums) {
        std::cout << it << " ";
    }
    std::cout << "\n";
}

void MainWindow::on_rotation_x_valueChanged() {
    if(ui->fileName->text() != "") data.set_state(getState());
//    std::cout << "state X" << "\n";
//    output_vertex(data.get_vertexes());
    emit update_render();
}

void MainWindow::on_rotation_y_valueChanged() {
    if(ui->fileName->text() != "") data.set_state(getState());
    emit update_render();
}

void MainWindow::on_rotation_z_valueChanged() {
    if(ui->fileName->text() != "") data.set_state(getState());
    emit update_render();
}

void MainWindow::on_transfer_x_valueChanged() {
    if(ui->fileName->text() != "")
      data.set_state(getState());
      emit update_render();
}

void MainWindow::on_transfer_y_valueChanged() {
    if(ui->fileName->text() != "")
        data.set_state(getState());
        emit update_render();
}

void MainWindow::on_scale_valueChanged() {
    if(ui->fileName->text() != "")
        data.set_state(getState());
        emit update_render();
}

void MainWindow::on_transfer_z_valueChanged() {
    if(ui->fileName->text() != "")
        data.set_state(getState());
        emit update_render();
}



void MainWindow::on_openFile_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выберете файл", QDir::homePath());
    ui->fileName->setText(fileName);
    data.parse_filename(fileName.toStdString());
    QString vertexCount = "Вершин: " + QString::number(data.get_vertexes().size() / 3);
    QString ribsCount = "Рёбер: " + QString::number(data.get_indexes().size() / 2);
    ui->countVertex->setText(vertexCount);
    ui->countIndex->setText(ribsCount);
    data.set_state(getState());
    emit update_render();
}


//look_st *MainWindow::getLook() {
//  look_st *look = new look_st;
//  look->rW = ui->rW->value();
//  look->gW = ui->gW->value();
//  look->bW = ui->bW->value();
//  look->aW = ui->aW->value();

//  look->rL = ui->rL->value();
//  look->gL = ui->gL->value();
//  look->bL = ui->bL->value();

//  look->rV = ui->rV->value();
//  look->gV = ui->gV->value();
//  look->bV = ui->bV->value();

//  look->widthLine = ui->widthLine->value();
//  look->widthVertex = ui->widthVertex->value();
//  return look;
//}

//void MainWindow::on_rW_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_gW_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_bW_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_aW_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_rV_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_gV_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_bV_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_rL_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_gL_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_bL_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_widthLine_valueChanged() { emit setLook(getLook()); }

//void MainWindow::on_widthVertex_valueChanged() { emit setLook(getLook()); }

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






#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(this, &MainWindow::setData, ui->openGLWidget, &GLWidget::getData);
  connect(this, &MainWindow::update_render, ui->openGLWidget, &GLWidget::update_render);
  emit setData(&data, &look);
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
    if (!fileName.isEmpty()) {
        ui->fileName->setText(fileName);
        data.parse_filename(fileName.toStdString());
        QString vertexCount = "Вершин: " + QString::number(data.get_vertexes().size() / 3);
        QString ribsCount = "Рёбер: " + QString::number(data.get_indexes().size() / 2);
        ui->countVertex->setText(vertexCount);
        ui->countIndex->setText(ribsCount);
        data.set_state(getState());
        emit update_render();
    }
}

void MainWindow::change_look() {
    look.red_widget = ui->rW->value();
    look.green_widget = ui->gW->value();
    look.blue_widget = ui->bW->value();
    look.alpha_widget = ui->aW->value();
    look.red_line = ui->rL->value();
    look.green_line = ui->gL->value();
    look.blue_line = ui->bL->value();
    look.red_vertex = ui->rV->value();
    look.green_vertex = ui->gV->value();
    look.blue_vertex = ui->bV->value();
    look.width_vertex = ui->widthVertex->value();
    look.width_line = ui->widthLine->value();
    emit update_render();
}

void MainWindow::on_rW_valueChanged() { change_look(); }

void MainWindow::on_gW_valueChanged() { change_look(); }

void MainWindow::on_bW_valueChanged() { change_look(); }

void MainWindow::on_aW_valueChanged() { change_look(); }

void MainWindow::on_rV_valueChanged() { change_look(); }

void MainWindow::on_gV_valueChanged() { change_look(); }

void MainWindow::on_bV_valueChanged() { change_look(); }

void MainWindow::on_rL_valueChanged() { change_look(); }

void MainWindow::on_gL_valueChanged() { change_look(); }

void MainWindow::on_bL_valueChanged() { change_look(); }

void MainWindow::on_widthLine_valueChanged() { change_look(); }

void MainWindow::on_widthVertex_valueChanged() { change_look(); }

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


void MainWindow::on_projection_clicked() {
    QString text_button = ui->projection->text();
    if (text_button == "Параллельная") {
        ui->projection->setText("Центральная");
        data.set_projection(true);
    } else {
        ui->projection->setText("Параллельная");
        data.set_projection(false);
    }
    emit update_render();
}


void MainWindow::on_type_line_clicked() {
    QString type_line = ui->type_line->text();
    if (type_line == "Сплошная") {
        ui->type_line->setText("Пунктирная");
        look.line_stipple = true;
    } else {
        ui->type_line->setText("Сплошная");
        look.line_stipple = false;
    }
    emit update_render();
}


void MainWindow::on_type_vertex_clicked() {
    QString type_vertex = ui->type_vertex->text();
    if (type_vertex == "Квадратные") {
        look.type_vectors = "Круглые";
        ui->type_vertex->setText("Круглые");
    } else if (type_vertex == "Круглые") {
        look.type_vectors = "Нет";
        ui->type_vertex->setText("Нет");
    } else {
        look.type_vectors = "Квадратные";
        ui->type_vertex->setText("Квадратные");
    }
    emit update_render();
}


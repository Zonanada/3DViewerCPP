#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "glwidget.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include "../controller/controller.h"

struct Size_and_color {
    double red_line = 0;
    double green_line = 1;
    double blue_line = 0;
    double red_vertex = 1;
    double green_vertex = 0;
    double blue_vertex = 0;
    double red_widget = 0;
    double green_widget = 0;
    double blue_widget = 0;
    double alpha_widget = 0;
    double width_line = 1;
    double width_vertex = 3;
    bool line_stipple = false;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rotation_x_valueChanged();
    void on_rotation_y_valueChanged();
    void on_rotation_z_valueChanged();
    void on_transfer_x_valueChanged();
    void on_transfer_y_valueChanged();
    void on_transfer_z_valueChanged();
    void on_scale_valueChanged();
    void on_openFile_clicked();

    void on_rW_valueChanged();
    void on_gW_valueChanged();
    void on_bW_valueChanged();
    void on_aW_valueChanged();

    void on_rV_valueChanged();
    void on_gV_valueChanged();
    void on_bV_valueChanged();
    void on_rL_valueChanged();
    void on_gL_valueChanged();
    void on_bL_valueChanged();
    void on_widthLine_valueChanged();
    void on_widthVertex_valueChanged();
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void on_projection_clicked();

    void on_type_line_clicked();

private:
    State getState();
    Ui::MainWindow *ui;
    Controller data;
    Size_and_color size_and_color;
//    Rendering *rendering;
    double pos_mouse_x;
    double pos_mouse_y;

public:
    void change_look();



signals:
//    void setState(state_st *state);
    void setData(Controller *data, Size_and_color *size_and_color);
    void update_render();
//    void setLook(look_st *look);
//    void setProjection();

};
#endif // MAINWINDOW_H

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

GLWidget::~GLWidget() {}


void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

void GLWidget::paintGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (data->get_projection()) {
        glFrustum(-1.12, 1.12, -1.12, 1.12, 3, 7);
    } else {
        glOrtho(-1.85, 1.85, -1.85, 1.85, -2, 2);
    }
    glClearColor(look->red_widget, look->green_widget, look->blue_widget, look->alpha_widget);

    glEnable(GL_BLEND);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(look->width_line);
    glColor3d(look->red_line, look->green_line, look->blue_line);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, &data->get_vertexes()[0]);

    if (look->line_stipple) {
        glDisable(GL_LINE_STIPPLE);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2,0X00FF);
    } else{
        glDisable(GL_LINE_STIPPLE);
    }

    glDrawElements(GL_LINES, data->get_indexes().size(), GL_UNSIGNED_INT, &data->get_indexes()[0]);
    glPointSize(GLfloat(look->width_vertex));
    glColor3d(look->red_vertex, look->green_vertex, look->blue_vertex);

    if (look->type_vectors != "Нет") {
        glDisable(GL_POINT_SMOOTH);
        if (look->type_vectors == "Круглые") {
            glEnable(GL_POINT_SMOOTH);
        }
        glDrawArrays(GL_POINTS, 0, data->get_vertexes().size() / 3);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::getData(Controller *input_data, Look *input_look) {
    data = input_data;
    look = input_look;
}

void GLWidget::update_render() {
    update();
}


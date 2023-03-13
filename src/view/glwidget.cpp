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
    glClearColor(size_and_color->red_widget, size_and_color->green_widget, size_and_color->blue_widget, size_and_color->alpha_widget);
    if (size_and_color->line_stipple) {
        glLineStipple(2,0X00FF);
    }
    glEnable(GL_BLEND);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(size_and_color->width_line);
    glColor3d(size_and_color->red_line, size_and_color->green_line, size_and_color->blue_line);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_DOUBLE, 0, &data->get_vertexes()[0]);
    glDrawElements(GL_LINES, data->get_indexes().size(), GL_UNSIGNED_INT, &data->get_indexes()[0]);

    glPointSize(GLfloat(size_and_color->width_vertex));
    glColor3d(size_and_color->red_vertex, size_and_color->green_vertex, size_and_color->blue_vertex);

    glDrawArrays(GL_POINTS, 0, data->get_vertexes().size() / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::getData(Controller *input_data, Size_and_color *input_size_and_color) {
    data = input_data;
    size_and_color = input_size_and_color;
}

void GLWidget::update_render() {
    update();
}


//void GLWidget::setState(state_st *state) {
//  stateСhange(&data->vertex, state);
//  update();
//}


//void GLWidget::setFilename(char *name) {
//  if (data != NULL) {
//    deleteData(data);
//  }
//  data = getData(name);
//  update();
//}

//void GLWidget::setLook(look_st *look) {
//  rW = look->rW;
//  gW = look->gW;
//  bW = look->bW;
//  aW = look->aW;

//  rV = look->rV;
//  gV = look->gV;
//  bV = look->bV;

//  rL = look->rL;
//  gL = look->gL;
//  bL = look->bL;

//  widthLine = look->widthLine;
//  widthVertex = look->widthVertex;
//  update();
//}


//void GLWidget::setProjection() {
//  if (perspective == 1) {
//    perspective = 0;
//  } else {
//    perspective = 1;
//  }
//  update();
//}

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

GLWidget::~GLWidget() {}


void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
//    qreal aspect = qreal(w) / qreal(h ? h : 1);
//    float fov = 60.0 * M_PI / 180;
//    float heapHeight = 2 / (2 * tan(fov / 2));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();






}

void GLWidget::paintGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (data->get_projection()) {
        glFrustum(-1.25, 1.25, -1.25, 1.25, 3, 7);
    } else {
        glOrtho(-2, 2, -2, 2, -2, 2);
    }
    glClearColor(rW, gW, bW, aW);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(widthLine);
    glColor3d(rL, gL, bL);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_DOUBLE, 0, &data->get_vertexes()[0]);
    glDrawElements(GL_LINES, data->get_indexes().size(), GL_UNSIGNED_INT, &data->get_indexes()[0]);

    glPointSize(GLfloat(3));
    glColor3d(rV, gV, bV);

    glDrawArrays(GL_POINTS, 0, data->get_vertexes().size() / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::getData(Controller *input_data) {
    data = input_data;
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

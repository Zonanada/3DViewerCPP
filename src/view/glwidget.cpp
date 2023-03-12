#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

GLWidget::~GLWidget() {}


void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
    qreal aspect = qreal(w) / qreal(h ? h : 1);
//    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    float fov = 60.0 * M_PI / 180;  // 60 угол в градусах
    float heapHeight = 2 / (2 * tan(fov / 2));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-2, 2, -2, 2, -2, 2);
    glFrustum(-2, 2, -2, 2, 3, 7);




//    projection.setToIdentity();
//    projection.perspective(fov, aspect, zNear, zFar);

}

void GLWidget::paintGL() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    QMatrix4x4 matrix;
//    matrix.translate(0.0, 0.0, -5.0);
//    matrix.rotate(rotation);

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

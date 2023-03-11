#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <string>
#include "../controller/controller.h"
#include <iostream>


class GLWidget : public QOpenGLWidget
{
    public:
        GLWidget(QWidget *parent = 0);
        ~GLWidget();

    protected:
        void initializeGL();
        void resizeGL();
        void paintGL();

    public:
        double rW =0, gW = 0, bW = 0, aW = 0;
        double rL = 0 , gL = 1, bL = 0, rV = 1, gV = 0, bV= 0;
        double widthLine, widthVertex;
//        vertex_index_st *data;
        char* filename;
        int perspective, typeLine;
    private:
        Controller *data = nullptr;

    public slots:
        void getData(Controller *input_data);
        void update_render();
//        void setFilename(char *name);
//        void setLook(look_st *look);
//        void setProjection();

};

#endif // GLWIDGET_H

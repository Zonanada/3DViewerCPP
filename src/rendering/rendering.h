#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <string>
#include <iostream>

extern "C" {
    #include "../backend/parser.h"
}


class Rendering : public QOpenGLWidget
{
    public:
        Rendering(QWidget *parent = 0);
        ~Rendering();

    protected:
        void initializeGL();
        void resizeGL();
        void paintGL();

    public:
        double rW, gW, bW, aW;
        double rL, gL, bL, rV, gV, bV;
        double widthLine, widthVertex;
        vertex_index_st *data;
        char* filename;
        int perspective, typeLine;

    public slots:
        void setState(state_st *state);
        void setFilename(char *name);
        void setLook(look_st *look);
        void setProjection();

};

#endif // GLWIDGET_H

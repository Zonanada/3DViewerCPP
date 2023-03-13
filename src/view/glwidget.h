#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <string>
#include "../controller/controller.h"
#include <iostream>
#include <QMatrix4x4>
#include <mainwindow.h>


class GLWidget : public QOpenGLWidget
{
    public:
        GLWidget(QWidget *parent = 0);
        ~GLWidget();

    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;

    private:
        Controller *data = nullptr;
        Size_and_color *size_and_color;
        QMatrix4x4 projection;
        QQuaternion rotation;

    public slots:
        void getData(Controller *input_data, Size_and_color *input_size_and_color);
        void update_render();
//        void setFilename(char *name);
//        void setLook(look_st *look);
//        void setProjection();

};

#endif // GLWIDGET_H

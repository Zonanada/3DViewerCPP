#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <string>
#include "../controller/controller.h"
#include <iostream>
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
        Look *look;

    public slots:
        void getData(Controller *input_data, Look *input_look);
        void update_render();

};

#endif // GLWIDGET_H

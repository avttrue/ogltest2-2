#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

class SimpleObject3D;

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void initShaders();
    void initCube(float width, const QImage &img);

private:
    QMatrix4x4 m_PojectionMatrix;
    QOpenGLShaderProgram m_Program;
    QVector2D m_MousePosition;
    QQuaternion m_Rotation;

    QVector<SimpleObject3D*> m_objects;
};

#endif // OGLWIDGET_H

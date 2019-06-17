#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include<QOpenGLBuffer>
#include<QMatrix4x4>
#include<QVector2D>

class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLFunctions;

struct VertexData
{
    VertexData() {}
    VertexData(QVector3D p, QVector2D t, QVector3D n)
        : position(p), textcoord(t), normal(n) {}
    QVector3D position;
    QVector2D textcoord;
    QVector3D normal;
};

class SimpleObject3D
{
public:
    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vert, const QVector<GLuint> &ind, const QImage &img);
    ~SimpleObject3D();

    void init(const QVector<VertexData> &vert, const QVector<GLuint> &ind, const QImage &img);
    void draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions);
    void translate(const QVector3D &trvector);

protected:
    void free();

private:
    QOpenGLBuffer m_VertexBuffer;
    QOpenGLBuffer m_IndexBuffer;
    QMatrix4x4 m_ModelMatrix;
    QOpenGLTexture* m_Texture;
};

#endif // SIMPLEOBJECT3D_H

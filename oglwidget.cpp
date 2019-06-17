#include "oglwidget.h"
#include "simpleobject3d.h"

#include <QMouseEvent>
#include <QOpenGLContext>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{}

OGLWidget::~OGLWidget()
{}

void OGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();

    initCube(1.3f, QImage(":/cube3.png"));
    m_Objects.at(0)->translate(QVector3D(-0.7f, 0.0f, 0.0f));

    initCube(1.0f, QImage(":/cube1.png"));
    m_Objects.at(1)->translate(QVector3D(0.7f, 0.0f, 0.0f));
}

void OGLWidget::resizeGL(int w, int h)
{
    float aspect = w / (h? static_cast<float>(h) : 1);
    m_PojectionMatrix.setToIdentity();
    m_PojectionMatrix.perspective(45, aspect, 0.1f, 10.0f);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(0.0f, 0.0f, -3.0f);
    viewMatrix.rotate(m_Rotation);

    m_Program.bind();
    m_Program.setUniformValue("u_projectionMatrix", m_PojectionMatrix);
    m_Program.setUniformValue("u_viewMatrix", viewMatrix);
    m_Program.setUniformValue("u_lightPosition", QVector4D(0.0f, 0.0f, 0.0f, 1.0f));
    m_Program.setUniformValue("u_lightPower", 1.5f);

    for(auto o: m_Objects) o->draw(&m_Program, context()->functions());
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        m_MousePosition = static_cast<QVector2D>(event->localPos());
    }

    event->accept();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QVector2D diffpos = static_cast<QVector2D>(event->localPos()) - m_MousePosition;
        m_MousePosition = static_cast<QVector2D>(event->localPos());

        float angle = diffpos.length() / 2.0f;
        QVector3D axis = QVector3D(diffpos.y(), diffpos.x(), 0.0f);
        m_Rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_Rotation;

        update();
    }

    event->accept();
}

void OGLWidget::initShaders()
{
    if(! m_Program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertshader.vsh"))
        close();
    if(! m_Program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragshader.fsh"))
        close();

    if(! m_Program.link())
        close();
}

void OGLWidget::initCube(float width, const QImage &img)
{
    float width_div_2 = width / 2.0f;

    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2),
                               QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),
                               QVector2D(1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2),
                               QVector2D(1.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2),
                               QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2),
                               QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2),
                               QVector2D(0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),
                               QVector2D(1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),
                               QVector2D(1.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2),
                               QVector2D(0.0f, 1.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2),
                               QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),
                               QVector2D(1.0f, 1.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0f, 0.0f), QVector3D(0.0f, 0.0f, -1.0f)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),
                               QVector2D(0.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),
                               QVector2D(0.0f, 0.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2),
                               QVector2D(1.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0f, 0.0f), QVector3D(-1.0f, 0.0f, 0.0f)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2),
                               QVector2D(0.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2),
                               QVector2D(0.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2),
                               QVector2D(1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2),
                               QVector2D(1.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));

    QVector<GLuint> indexes;
    for(GLuint i = 0; i < 24; i += 4)
    {
        indexes.append(i + 0); indexes.append(i + 1); indexes.append(i + 2);
        indexes.append(i + 2); indexes.append(i + 1); indexes.append(i + 3);
    }

    m_Objects.append(new SimpleObject3D(vertexes, indexes, img));
}

#ifndef MEGLWIDGET_H
#define MEGLWIDGET_H

#include <QGLWidget>


class meGLWidget : public QGLWidget
{

    Q_OBJECT
public:
    explicit meGLWidget(QWidget *parent = 0);

signals:

public slots:

protected:

    void initializeGL();
    void paintGL();


    void sendDataToOpenGL();
    void installShader();
    bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
    bool checkShaderStatus(GLuint shaderID);
    bool checkProgramStatus(GLuint programID);
    std::string readShaderCode(const char *fileName);
};

#endif // MEGLWIDGET_H

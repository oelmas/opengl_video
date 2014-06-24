#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "meglwidget.h"

using namespace std;


extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

meGLWidget::meGLWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

void meGLWidget::sendDataToOpenGL()
{

    const float RED_TRIANGLE_Z = 0.5;
    const float BLUE_TRIANGLE_Z = -0.5;
    GLfloat verts[] ={
        -1.0f, -1.0f, RED_TRIANGLE_Z,      //0
        +1.0f, +0.0f,+0.0f,
        +0.0f, +1.0f, RED_TRIANGLE_Z,       //1
        +1.0f, +0.0f,+0.0f,
        +1.0f, -1.0f, RED_TRIANGLE_Z,      //2
        +1.0f, +0.0f,+0.0f,

        -1.0f, +1.0f,BLUE_TRIANGLE_Z,       //3
        +0.0f, +0.0f,+1.0f,
        +1.0f, +1.0f,BLUE_TRIANGLE_Z,       //4
        +0.0f, +0.0f,+1.0f,
        +0.0f, -1.0f,BLUE_TRIANGLE_Z,       // 5
        +0.0f, +0.0f,+1.0f,

    };


    GLuint vertexBufferID;

    glGenBuffers(1,
                 &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,
                 vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(verts),
                 verts,
                 GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (char*)(sizeof(float)*3));

    GLushort indices[]={0,1,2, 3,4,5 };
    GLuint indexBufferID;

    glGenBuffers(1,
                 &indexBufferID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferID );

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(indices),
                 indices,
                 GL_STATIC_DRAW);
}

bool meGLWidget::checkStatus(GLuint objectID,
                             PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
                             PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                             GLenum statusType)
{
    GLint status;

    objectPropertyGetterFunc(objectID, statusType, &status);
    if (status!= GL_TRUE) {
        GLint infoLogLength;
        objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH,&infoLogLength );
        GLchar* buffer= new GLchar[infoLogLength];

        GLsizei bufferSize;
        getInfoLogFunc(objectID , infoLogLength, &bufferSize,buffer);
        std::cout << buffer << std::endl;
        delete [] buffer;
        return false;
    }
    return true;


}

bool meGLWidget::checkShaderStatus(GLuint shaderID)
{
    return checkStatus(shaderID,glGetShaderiv, glGetShaderInfoLog,GL_COMPILE_STATUS);

}

bool meGLWidget::checkProgramStatus(GLuint programID)
{

    return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}


std::string meGLWidget::readShaderCode(const char* fileName)
{
    ifstream meInput(fileName);
    if (! meInput.good()) {
        cout << "File failed to load..." << fileName;
        exit(1);
    }

    return std::string( std::istreambuf_iterator<char>(meInput),
                        std::istreambuf_iterator<char>());

}

void meGLWidget::installShader()
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER );
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER );


    const char* adapter[1];
    string temp = readShaderCode("/home/oelmas/Development/OpenCVOpenGLQT/openglQT/qtOpencv/VertexShaderCode.glsl");
    adapter[0]= temp.c_str();
    glShaderSource(vertexShaderID, 1, adapter, 0);

    temp = readShaderCode("/home/oelmas/Development/OpenCVOpenGLQT/openglQT/qtOpencv/FragmentShaderCode.glsl");
    adapter[0] = temp.c_str();
    glShaderSource(fragmentShaderID, 1, adapter, 0);


    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    if (!checkShaderStatus(vertexShaderID) || ! checkShaderStatus(fragmentShaderID)) {
        return;

    }

    GLuint programID = glCreateProgram();
    glAttachShader( programID, vertexShaderID);
    glAttachShader( programID, fragmentShaderID);
    glLinkProgram(programID);

    if (!checkProgramStatus(programID))
        return;


    glUseProgram(programID);

}

void meGLWidget::initializeGL()
{

    glewInit();
    glEnable(GL_DEPTH_TEST);
    sendDataToOpenGL();
    installShader();

}

void meGLWidget::paintGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glClear(GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width(), height());
    //    glDrawArrays(GL_TRIANGLES,0,6);
    glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_SHORT,0);

}

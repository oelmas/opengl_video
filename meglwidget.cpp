#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "meglwidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Primitives/Vertex.h"
#include "Primitives/shapedata.h"
#include "Primitives/shapegenerator.h"
//#include <Qt>


using namespace std;


extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE* sizeof(float);
GLuint programID;

using glm::mat4;
using glm::vec3;

GLuint numIndices;


meGLWidget::meGLWidget(QWidget *parent) :QGLWidget(parent)
{

}

void meGLWidget::sendDataToOpenGL()
{

    ShapeData shape = ShapeGenerator::makeCube();//ShapeGenerator::makeTriangle();


    GLuint vertexBufferID;

    glGenBuffers(1,&vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,shape.vertexBufferSize(),shape.vertices,GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,VERTEX_BYTE_SIZE, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,VERTEX_BYTE_SIZE, (char*)(sizeof(float)*3));


    GLuint indexBufferID;

    glGenBuffers(1,&indexBufferID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferID );

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,shape.indexBufferSize(),shape.indices,GL_STATIC_DRAW);

    numIndices = shape.numIndices;
    shape.cleanUp();



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

    programID = glCreateProgram();
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width(), height());

    mat4 projectionMatrix = glm::perspective(60.0f,((float)width())/ height(),0.1f,10.0f);
    mat4 projectionTranslationMatrix = glm::translate(projectionMatrix,vec3(0.0f,0.0f,-3.0f));

    mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, 144.0f,glm::vec3(1.0f, 0.0f,0.0f));

    GLint fullTransformMatrixUniformLocation =
            glGetUniformLocation(programID,"fullTransformMatrix");


    glUniformMatrix4fv(fullTransformMatrixUniformLocation,1,GL_FALSE,
                       &fullTransformMatrix[0][0]);

    glDrawElements(GL_TRIANGLES,
                   numIndices, // TODO: Buraya gelecek değişkeni bulmak gerek,
                   GL_UNSIGNED_SHORT,
                   0);

}

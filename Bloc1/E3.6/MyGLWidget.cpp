//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders(); //Siguiente sesión.
  createBuffers();
  rotation = 0.0;
}

void MyGLWidget::keyPressEvent(QKeyEvent * e) {
    makeCurrent();
    if(e->key() == Qt::Key_R){
        rotation += (float)M_PI/6;
    }
    update();
}

//Función que hace una transform diferente en función del numero que se le pasa por parámetro.
void MyGLWidget::modelTransform(int number){
    if(number == 0){
        glm::mat4 TG(1.0);
        TG = glm::rotate(TG,rotation,glm::vec3(0.0,0.0,1.0));
        glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
    }
    else if (number == 1){
        glm::mat4 TG(1.0);
        TG = glm::rotate(TG,-rotation,glm::vec3(0.0,0.0,1.0));
        glUniformMatrix4fv(transLoc,1,GL_FALSE, &TG[0][0]);
    }
    else{
        glm::mat4 TG(1.0);
        TG = glm::rotate(TG,rotation,glm::vec3(0.0,0.0,1.0));
        glUniformMatrix4fv(transLoc,1,GL_FALSE,&TG[0][0]);
    }

}

void MyGLWidget::paintGL ()
{
  //Esta vez hemos de conseguir dos transforms diferentes a la hora de pintar
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  /*******************PRIMER OBJETO************************/
  // Activem l'Array a pintar 
  glBindVertexArray(VAO1[0]);
  modelTransform(0);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 9);
  
  // Desactivem el VAO
  glBindVertexArray(0);

  /*******************SEGUNDO OBJETO************************/
  glBindVertexArray(VAO1[1]);
  modelTransform(1);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  glViewport (0, 0, w, h);
}

void MyGLWidget::createBuffers ()
{

  /*************************PRIMER OBJETO*******************************/
  glm::vec3 Vertices[9];  // 4 Vértices para dibujar el cuadrado. OJO!! Triangle strip utilizado
  Vertices[0] = glm::vec3(-0.5, -1.0, 0.0); //primer triangulo
  Vertices[1]= glm::vec3(-0.5, 0.0, 0.0);
  Vertices[2] = glm::vec3(0.5, -1.0, 0.0);

  Vertices[3]= glm::vec3(-0.5, 0.0, 0.0); //segundo triangulo
  Vertices[4] = glm::vec3(0.5, -1.0, 0.0);
  Vertices[5] = glm::vec3(0.5, 0.0, 0.0);

  Vertices[6] = glm::vec3(-0.5,0.0,0.0);
  Vertices[7] = glm::vec3(0.5,0.0,0.0);
  Vertices[8] = glm::vec3(0.0,0.5,0.0);

  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(2, VAO1); //recordamos que creamos 2 VAO
  glBindVertexArray(VAO1[0]);

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(2, VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);

  /********************SEGUNDO OBJETO***********************************/
  glm::vec3 Vertices2[3];
  Vertices2[0] = glm::vec3(1.0, 1.0, 0.0); //primer triangulo
  Vertices2[1]= glm::vec3(0.75, 1.0, 0.0);
  Vertices2[2] = glm::vec3(0.75, 0.75, 0.0);

  glBindVertexArray(VAO1[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);

}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  transLoc = glGetUniformLocation(program->programId(),"TG");
}

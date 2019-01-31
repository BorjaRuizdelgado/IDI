#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  scale = 1.0f;
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
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  homer.load("/home/borja/Desktop/Codi-Esquelet/models/HomerProves.obj");
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();
  iniCamera();
  rotation = 0.0;

}

void MyGLWidget::iniCamera(){
    FOV =(float)M_PI/2.0f;
    ra = 1.0f;
    zn = 0.4f;
    zf = 3.0f;
    obs = glm::vec3(0,0,1);
    vrp = glm::vec3(0,0,0);
    up = glm::vec3(0,1,0);
    projectTransform();
    viewTransform();
}

void MyGLWidget::paintGL () 
{
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransform(0);

  // Activem el VAO per a pintar la caseta 
  glBindVertexArray (VAO_Homer);
  // pintem
  glDrawArrays(GL_TRIANGLES, 0, homer.faces().size() * 3);


  modelTransform(1);
  glBindVertexArray (VAO_Suelo);

  // pintem
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray(0);
}

void MyGLWidget::modelTransform (int number)
{
    if( number == 0){
      // Matriu de transformació de model
      glm::mat4 transform (1.0f);
      transform = glm::rotate(transform,rotation,glm::vec3(0,1,0));
      transform = glm::scale(transform, glm::vec3(scale));
      glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    }
    else if (number == 1){
        glm::mat4 transform(1.0f);
        transform = glm::scale(transform, glm::vec3(scale));
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    }
}

void MyGLWidget::projectTransform(){
    glm::mat4 proj=glm::perspective(FOV,ra,zn,zf);
    glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);
}

void MyGLWidget::viewTransform(){
    glm::mat4 View=glm::lookAt(obs,vrp,up);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  glViewport(0, 0, w, h);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
  case Qt::Key_R: {
      rotation += (float)M_PI/4;
      break;
  }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::createBuffers () 
{
    //Creamos suelo
    glGenVertexArrays(1, &VAO_Suelo);
    glBindVertexArray(VAO_Suelo);

    glm::vec3 Vertices[4];  // 6 vèrtexs amb X, Y i Z
    Vertices[0] = glm::vec3(-1.0, -1.0, -1.0);
    Vertices[1] = glm::vec3(-1.0, -1.0, 1.0);
    Vertices[2] = glm::vec3(1.0, -1.0, -1.0);
    Vertices[3] = glm::vec3(1.0, -1.0, 1.0);

    glGenBuffers(1, &VBO_Suelo);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Suelo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  glGenBuffers(1, &VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * homer.faces().size() * 3 * 3, homer.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_HomerColor);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerColor);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * homer.faces().size() * 3 * 3, homer.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
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
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  //Projection transform
  projLoc = glGetUniformLocation(program->programId(), "Proj");
  //View transfrom
  viewLoc = glGetUniformLocation(program->programId(), "View");
}


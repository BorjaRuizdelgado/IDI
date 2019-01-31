#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  scale = 1.0f;
  xClick = 0;
  yClick = 0;
  deltaA = (float)M_PI/180;
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
  homer.load("/home/borja/Desktop/Codi-Esquelet/models/Patricio.obj");
  iniCamera(); //inicializamos los parámetros de camara.
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers();
  rotation = 0.0;
  psi = 0.0;
  ortogonal = false;
  theta = 0.0;
  deltaFOV = (float)M_PI/50.0; //cantidad de zoom que queramos.
  viewTransform(); // calculamos parámetros de cámara.
  projectTransform();

}

void MyGLWidget::iniCamera(){
    //parámetros de cámara temporales
    //en este caso excepcional, como sabemos los puntos minimos y máximos lo calculamos a mano
    calculaCajaModelo();
    radioEsfera = glm::distance(glm::vec3(-2.5,0,-2.5), glm::vec3(2.5,1,2.5))/2;
    ra = 1.0f;
    obs = glm::vec3(0,0.25,2*radioEsfera);
    vrp = glm::vec3(0,0.25,0);
    up = glm::vec3(0,1,0);
    float d = 0;
    for (int i = 0; i < 3; i += 1){
      d = d + (obs[i] - vrp[i]) * (obs[i] - vrp[i]);
    }
    d = sqrt(d);
    zn = (d - radioEsfera) / 2.0;
    zf = d + radioEsfera;
    fov_ini = 2.0*asin(radioEsfera/d);
    FOV = fov_ini;


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

  //pintamos segundo patricio;
  modelTransform(2);
  glDrawArrays(GL_TRIANGLES, 0, homer.faces().size() * 3);

  //pintamos 3er patricio
  modelTransform(3);
  glDrawArrays(GL_TRIANGLES,0,homer.faces().size()*3);
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
      transform = glm::rotate(transform,(float)M_PI/2,glm::vec3(0,1,0));
      transform = glm::scale(transform, glm::vec3(scale));
      //movemos el modelo al centro.
      transform = glm::translate(transform,-centroBase);
      glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    }
    else if (number == 1){
        glm::mat4 transform(1.0f);
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    }
    else if (number == 2){
        //transform para patricio 2
        glm::mat4 transform (1.0f);
        transform = glm::translate(transform, glm::vec3(2,0,2));//movemos patricio al punto requerido
        transform = glm::scale(transform, glm::vec3(scale));
        //movemos el modelo al centro.
        transform = glm::rotate(transform,rotation,glm::vec3(0,1,0));
        transform = glm::translate(transform,-centroBase);
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    }
    else if (number == 3){
        //transform para patricio 2
        glm::mat4 transform (1.0f);
        transform = glm::translate(transform, glm::vec3(-2,0,-2));
        transform = glm::rotate(transform,-(float)M_PI/2,glm::vec3(0,1,0));
        transform = glm::scale(transform, glm::vec3(scale));
        //movemos el modelo al centro.
        transform = glm::rotate(transform,rotation,glm::vec3(0,1,0));
        transform = glm::translate(transform,-centroBase);
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    }
}

void MyGLWidget::projectTransform(){
    if(!ortogonal){
        glm::mat4 proj=glm::perspective(FOV,ra,zn,zf);
        glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);
    }
    else{
        float height = tan(FOV/2)*(zn + (zf-zn)/2); //hacemos una media entre el widow y el final de zf
        glm::mat4 proj=glm::ortho(-height*ra, height*ra, -height*ra, height*ra, zn, zf);
        glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);

    }

}

void MyGLWidget::viewTransform(){
    /**glm::mat4 View=glm::lookAt(obs,vrp,up);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);**/
    //Euler para calcular la cámra.
    glm::mat4 View = glm::mat4(1.0);
    //observador a distancia 1.2 radios de esfera
    View = glm::translate(glm::mat4(1.f), -obs);
    View = glm::rotate(View, -psi,  glm::vec3(0,1,0));//rotacion eje Y
    View = glm::rotate(View, theta, glm::vec3(1,0,0));//rotacion eje x
    View = glm::translate(View, -vrp);
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,&View[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
    ra = (float)w/h;
    if (ra > 1) FOV = fov_ini;
    else FOV = 2*atan(tan((fov_ini/2))/ra);
    projectTransform();
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
  case Qt::Key_Z: {

      if(FOV + deltaFOV > (float)M_PI) break; //Prevenimos que la cámara supere los 180ª
      FOV += deltaFOV;
      fov_ini = FOV;
      projectTransform();//necesitamos llamar para recalcular la transform, si no no veremos nada.
      float degrees = FOV*180/(float)M_PI;
      zoomPerformed((int)degrees);
      break;
  }
  case Qt::Key_X: {
      if(FOV - deltaFOV < 0)break;//Prevenimos que la cámara tenga grados negativos
      FOV -= deltaFOV;
      fov_ini = FOV;
      float degrees = FOV*180/(float)M_PI;
      zoomPerformed((int)degrees);
      projectTransform();//necesitamos llamar para recalcular la transform, si no no veremos nada.s
      break;
  }
  case Qt::Key_O: {
      ortogonal = !ortogonal;
      projectTransform();
      break;
  }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  //Gestionamos el movimiento del mouse
  //Hay que volver a calcular la view para que se mueva el modelo.
  makeCurrent();
  int dx = abs(e->x() - xClick);
  int dy = abs(e->y() - yClick);

  if (dx > dy){   // gir psi respecte eixY
    if (e->x() > xClick){
      psi  -= abs(e->x() - xClick) * deltaA;
      viewTransform();
    }else if (e->x() < xClick){
      psi  += abs(e->x() - xClick) * deltaA;
      viewTransform();
    }
  }else{  // gir theta respecte eixX
    if (e->y() > yClick){
      theta += abs(e->y() - yClick) * deltaA;
      viewTransform();
    }else if (e->y() < yClick){
      theta -= abs(e->y() - yClick) * deltaA;
      viewTransform();
    }
  }
  update ();

  xClick = e->x();
  yClick = e->y();
}

void MyGLWidget::createBuffers () 
{
    //Creamos suelo
    glGenVertexArrays(1, &VAO_Suelo);
    glBindVertexArray(VAO_Suelo);

    glm::vec3 Vertices[4];  // 6 vèrtexs amb X, Y i Z
    Vertices[0] = glm::vec3(-2.5, 0.0, -2.5);
    Vertices[1] = glm::vec3(-2.5, 0.0, 2.5);
    Vertices[2] = glm::vec3(2.5, 0.0, -2.5);
    Vertices[3] = glm::vec3(2.5, 0.0, 2.5);

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

void MyGLWidget::calculaCajaModelo(){
    //calculamos caja
    float xmin, xmax, ymin, ymax, zmin, zmax;

    xmin = xmax = homer.vertices()[0];
    ymin = ymax = homer.vertices()[1];
    zmin = zmax = homer.vertices()[2];
    for (unsigned int i = 3; i < homer.vertices().size(); i += 3)
    {
      if (homer.vertices()[i+0] < xmin)
        xmin = homer.vertices()[i+0];
      if (homer.vertices()[i+0] > xmax)
        xmax = homer.vertices()[i+0];
      if (homer.vertices()[i+1] < ymin)
        ymin = homer.vertices()[i+1];
      if (homer.vertices()[i+1] > ymax)
        ymax = homer.vertices()[i+1];
      if (homer.vertices()[i+2] < zmin)
        zmin = homer.vertices()[i+2];
      if (homer.vertices()[i+2] > zmax)
        zmax = homer.vertices()[i+2];
    }

    Pmin = glm::vec3 (xmin,ymin,zmin);
    Pmax = glm::vec3 (xmax,ymax,zmax);
    scale = 1/(ymax-ymin); // el 1 viene a raíz de lo que queremos que mida nuestro modelo
    centroModelo = glm::vec3 ( (xmax+xmin)/2, (ymax+ymin)/2, (zmax+zmin)/2);
    centroBase = glm::vec3((xmax+xmin)/2, ymin, (zmax+zmin)/2);
 }

void MyGLWidget::performZoom(int zoom){
    makeCurrent();
    FOV = (float)zoom*(float)M_PI/180;
    fov_ini = FOV;
    projectTransform();
    update();
}

#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  public slots:
      void performZoom(int zoom);
  signals:
      void zoomPerformed(int zoom);

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    //tratamiento de entrada de mouse
    virtual void mouseMoveEvent(QMouseEvent *event);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransform (int number);
    void projectTransform();
    void viewTransform();
    void iniCamera();
    void calculaCajaModelo();

    // attribute locations
    GLuint vertexLoc, colorLoc, projLoc, viewLoc;
    // uniform locations
    GLuint transLoc;
    // VAO i VBO names
    GLuint VAO_Homer, VBO_Homer, VBO_HomerColor, VAO_Suelo, VBO_Suelo;
    // Program
    QOpenGLShaderProgram *program;
    // Internal vars
    float scale;
    float rotation;
    float deltaA;
    float xClick, yClick;
    glm::vec3 pos;
    
    
    //camera variables
    float FOV, fov_ini, ra, zn, zf, radioEsfera, psi,theta,deltaFOV;
    bool ortogonal;
    glm::vec3 Pmin;
    glm::vec3 Pmax;
    glm::vec3 centroModelo;
    glm::vec3 obs;
    glm::vec3 vrp;
    glm::vec3 up;
    glm::vec3 centroBase;
    
    //modelo
    Model homer;
};


#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"
#include <QKeyEvent> //incluir esto si no no compila
#include "glm/gtc/matrix_transform.hpp" //incluir esto para poder hacer las transformaciones geométricas.


class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  
    
    //declarar keyPressEnvent para poderlo utilizar
    virtual void keyPressEvent (QKeyEvent * e);
    
    //declaramos función para poder hacer la transformación geometrica.
    
    virtual void modelTransform();

  private:
    void createBuffers ();
    void carregaShaders ();
    float scl;
    float vy,vx, vz; //utilizados para hacer la translación.
    
    // attribute locations
    GLuint vertexLoc;
    GLuint colorLoc;
    GLuint varLoc;
    GLuint transLoc;
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1;
};

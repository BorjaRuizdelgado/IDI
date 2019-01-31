TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += /home/borja/Desktop/Codi-Esquelet/Model/

FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h 
HEADERS += /home/borja/Desktop/Codi-Esquelet/Model/model.h

SOURCES += main.cpp MyForm.cpp \
        MyGLWidget.cpp 
SOURCES += /home/borja/Desktop/Codi-Esquelet/Model/model.cpp

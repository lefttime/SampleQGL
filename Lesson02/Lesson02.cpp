#include "Lesson02.hpp"

Lesson02::Lesson02( QWidget* parent ) : GLWidget( parent ) //QGLWidget( QGLFormat( QGL::SampleBuffers ), parent )
{
  setWindowTitle( "Lesson02" );
}

Lesson02::~Lesson02()
{
}

void Lesson02::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Lesson02::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( -1.5f, 0.0f, -6.0f );
  glBegin( GL_TRIANGLES );
  {
    glVertex3f( 0.0f, 1.0f, 0.0f );
    glVertex3f(-1.0f,-1.0f, 0.0f );
    glVertex3f( 1.0f,-1.0f, 0.0f );
  }
  glEnd();

  glTranslatef( 3.0f, 0.0f, 0.0f );
  glBegin( GL_QUADS );
  {
    glVertex3f(-1.0f, 1.0f, 0.0f );
    glVertex3f( 1.0f, 1.0f, 0.0f );
    glVertex3f( 1.0f,-1.0f, 0.0f );
    glVertex3f(-1.0f,-1.0f, 0.0f );
  }
  glEnd();
}

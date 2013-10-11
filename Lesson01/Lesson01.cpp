#include "Lesson01.hpp"

Lesson01::Lesson01( QWidget* parent ) : GLWidget( parent )
{
  setWindowTitle( "Lesson01" );
}

Lesson01::~Lesson01()
{
}

void Lesson01::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Lesson01::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
}

void Lesson01::resizeGL( int width, int height )
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

}

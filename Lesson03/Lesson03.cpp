#include "Lesson03.hpp"

Lesson03::Lesson03( QWidget* parent ) : GLWidget( parent )
{
  setWindowTitle( "Lesson03" );
}

Lesson03::~Lesson03()
{
}

void Lesson03::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Lesson03::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( -1.5f, 0.0f, -6.0f );
  glBegin( GL_TRIANGLES );
  {
    glColor3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 1.0f, 0.0f );

    glColor3f( 0.0f, 1.0f, 0.0f );
    glVertex3f(-1.0f,-1.0f, 0.0f );

    glColor3f( 0.0f, 0.0f, 1.0f );
    glVertex3f( 1.0f,-1.0f, 0.0f );
  }
  glEnd();

  glTranslatef( 3.0f, 0.0f, 0.0f );
  glColor3f( 0.5f, 0.5f, 1.0f );
  glBegin( GL_QUADS );
  {
    glVertex3f(-1.0f, 1.0f, 0.0f );
    glVertex3f( 1.0f, 1.0f, 0.0f );
    glVertex3f( 1.0f,-1.0f, 0.0f );
    glVertex3f(-1.0f,-1.0f, 0.0f );
  }
  glEnd();
}

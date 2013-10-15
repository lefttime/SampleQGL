#include "Lesson05.hpp"

class Lesson05::Lesson05Private
{
public:

  Lesson05Private( Lesson05* me ) : m_self( me ), m_rQuad( 0 ), m_rTriangle( 0 ) {
  }

  void drawTetrahedron() {
    glBegin( GL_TRIANGLES );
    {
      glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f );
      glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f(-1.0f,-1.0f, 1.0f );
      glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f,-1.0f, 1.0f );

      glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f );
      glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f,-1.0f, 1.0f );
      glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f );

      glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f );
      glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f );
      glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f(-1.0f,-1.0f,-1.0f );

      glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f );
      glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f(-1.0f,-1.0f,-1.0f );
      glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f(-1.0f,-1.0f, 1.0f );
    }
    glEnd();
  }

  void drawCube() {
    glBegin( GL_QUADS );
    {
      glColor3f( 1.0f, 0.0f, 0.0f );
      glVertex3f( 1.0f, 1.0f,-1.0f );
      glVertex3f(-1.0f, 1.0f,-1.0f );
      glVertex3f(-1.0f, 1.0f, 1.0f );
      glVertex3f( 1.0f, 1.0f, 1.0f );

      glColor3f( 1.0f, 0.5f, 0.0f );
      glVertex3f( 1.0f,-1.0f, 1.0f );
      glVertex3f(-1.0f,-1.0f, 1.0f );
      glVertex3f(-1.0f,-1.0f,-1.0f );
      glVertex3f( 1.0f,-1.0f,-1.0f );

      glColor3f( 1.0f, 0.0f, 0.0f );
      glVertex3f( 1.0f, 1.0f, 1.0f );
      glVertex3f(-1.0f, 1.0f, 1.0f );
      glVertex3f(-1.0f,-1.0f, 1.0f );
      glVertex3f( 1.0f,-1.0f, 1.0f );

      glColor3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 1.0f,-1.0f,-1.0f );
      glVertex3f(-1.0f,-1.0f,-1.0f );
      glVertex3f(-1.0f, 1.0f,-1.0f );
      glVertex3f( 1.0f, 1.0f,-1.0f );

      glColor3f( 0.0f, 0.0f, 1.0f );
      glVertex3f(-1.0f, 1.0f, 1.0f );
      glVertex3f(-1.0f, 1.0f,-1.0f );
      glVertex3f(-1.0f,-1.0f,-1.0f );
      glVertex3f(-1.0f,-1.0f, 1.0f );

      glColor3f( 1.0f, 0.0f, 1.0f );
      glVertex3f( 1.0f, 1.0f,-1.0f );
      glVertex3f( 1.0f, 1.0f, 1.0f );
      glVertex3f( 1.0f,-1.0f, 1.0f );
      glVertex3f( 1.0f,-1.0f,-1.0f );
    }
    glEnd();
  }

  Lesson05*         m_self;
  float             m_rQuad;
  float             m_rTriangle;
};

Lesson05::Lesson05( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson05Private( this ) )
{
  setWindowTitle( "Lesson05" );
}

Lesson05::~Lesson05()
{
}

void Lesson05::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Lesson05::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( -1.5f, 0.0f, -6.0f );

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glRotatef( _pd->m_rTriangle, 0, 1, 0 );
  _pd->drawTetrahedron();
  glPopMatrix();

  glLoadIdentity();
  glTranslatef( 1.5f, 0.0f, -7.0f );
  glRotatef( _pd->m_rQuad, 1, 1, 1 );
  glColor3f( 0.5f, 0.5f, 1.0f );
  _pd->drawCube();
}

void Lesson05::idleFunc()
{
  float angle = 2;
  _pd->m_rTriangle += angle;
  if( _pd->m_rTriangle >= 360 ) {
    _pd->m_rTriangle -= 360;
  }
  _pd->m_rQuad = -_pd->m_rTriangle;

  updateGL();
}

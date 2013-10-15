#include "Lesson04.hpp"

class Lesson04::Lesson04Private
{
public:

  Lesson04Private( Lesson04* me ) : m_self( me ), m_rQuad( 0 ), m_rTriangle( 0 ) {
  }

  void drawTriangle() {
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
  }

  void drawQuad() {
    glBegin( GL_QUADS );
    {
      glVertex3f(-1.0f, 1.0f, 0.0f );
      glVertex3f( 1.0f, 1.0f, 0.0f );
      glVertex3f( 1.0f,-1.0f, 0.0f );
      glVertex3f(-1.0f,-1.0f, 0.0f );
    }
    glEnd();
  }

  Lesson04*         m_self;
  float             m_rQuad;
  float             m_rTriangle;
};

Lesson04::Lesson04( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson04Private( this ) )
{
  setWindowTitle( "Lesson04" );
}

Lesson04::~Lesson04()
{
}

void Lesson04::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Lesson04::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( -1.5f, 0.0f, -6.0f );

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glRotatef( _pd->m_rTriangle, 0, 1, 0 );
  _pd->drawTriangle();
  glPopMatrix();

  glTranslatef( 3.0f, 0.0f, 0.0f );
  glRotatef( _pd->m_rQuad, 1, 0, 0 );
  glColor3f( 0.5f, 0.5f, 1.0f );
  _pd->drawQuad();
}

void Lesson04::idleFunc()
{
  float angle = 2;
  _pd->m_rTriangle += angle;
  if( _pd->m_rTriangle >= 360 ) {
    _pd->m_rTriangle -= 360;
  }
  _pd->m_rQuad = -_pd->m_rTriangle;

  updateGL();
}

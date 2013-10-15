#include "Lesson22.hpp"

#include <QPixmap>
#include <QVector3D>

class Lesson22::Lesson22Private
{
public:

  Lesson22Private( Lesson22* me ) : m_self( me ), m_rAngle(0, 0, 0) {
  }

  ~Lesson22Private() {
    m_self->deleteTexture( m_texture );
  }

  void drawCube() {
    glBegin( GL_QUADS );
    {
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f,-1.0f, 1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f, 1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f, 1.0f, 1.0f );

      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f,-1.0f,-1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f, 1.0f,-1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f,-1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f );

      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f, 1.0f,-1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f, 1.0f, 1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f,-1.0f );

      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f,-1.0f,-1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f,-1.0f,-1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f,-1.0f, 1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f,-1.0f, 1.0f );

      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f,-1.0f,-1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f,-1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f,-1.0f, 1.0f );

      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f,-1.0f,-1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f,-1.0f, 1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f, 1.0f, 1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f, 1.0f,-1.0f );
    }
    glEnd();
  }

  Lesson22*         m_self;
  GLuint            m_texture;
  QVector3D         m_rAngle;
};

Lesson22::Lesson22( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson22Private( this ) )
{
  setWindowTitle( "Lesson22" );
}

Lesson22::~Lesson22()
{
}

void Lesson22::initializeGL()
{
  glEnable( GL_TEXTURE_2D );
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  _pd->m_texture = bindTexture( QPixmap( ":/Resources/NeHe.PNG" ), GL_TEXTURE_2D );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void Lesson22::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, -5.0f );
  glRotatef( _pd->m_rAngle.x(), 1, 0, 0 );
  glRotatef( _pd->m_rAngle.y(), 0, 1, 0 );
  glRotatef( _pd->m_rAngle.z(), 0, 0, 1 );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
  _pd->drawCube();
}

void Lesson22::resizeGL(int width, int height)
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson22::idleFunc()
{
  _pd->m_rAngle += QVector3D(0.3, 0.2, 0.4);

  updateGL();
}

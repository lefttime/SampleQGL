#include "Lesson07.hpp"

#include <QPixmap>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QKeyEvent>

class Lesson07::Lesson07Private
{
public:

  Lesson07Private( Lesson07* me ) : m_self( me ) {
  }

  ~Lesson07Private() {
    m_self->deleteTexture( m_texture );
  }

  void init() {
    m_zOffset = -5.0f;
    m_bLight = true;
    m_rAngle = QVector2D(0, 0);
    m_rSpeed = QVector2D(0, 0);

    m_lAmbient[0]  = 0.5f, m_lAmbient[1]  = 0.5f, m_lAmbient[2]  = 0.5f, m_lAmbient[3]  = 1.0f;
    m_lDiffuse[0]  = 1.0f, m_lDiffuse[1]  = 1.0f, m_lDiffuse[2]  = 1.0f, m_lDiffuse[3]  = 1.0f;
    m_lPosition[0] = 0.0f, m_lPosition[1] = 0.0f, m_lPosition[2] = 2.0f, m_lPosition[3] = 1.0f;
  }

  void changeFilter() {
    m_filter = (m_filter+1) % 3;
    switch( m_filter ) {
    case 0: {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    } break;

    case 1: {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    } break;

    case 2: {
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    } break;
    }
    m_self->updateGL();
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

  Lesson07*         m_self;
  GLuint            m_texture;

  bool              m_bLight;
  QVector2D         m_rAngle;
  QVector2D         m_rSpeed;
  float             m_zOffset;

  GLuint            m_filter;
  GLfloat           m_lAmbient[4];
  GLfloat           m_lDiffuse[4];
  GLfloat           m_lPosition[4];
};

Lesson07::Lesson07( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson07Private( this ) )
{
  setWindowTitle( "Lesson07" );
  _pd->init();
}

Lesson07::~Lesson07()
{
}

void Lesson07::initializeGL()
{
  glEnable( GL_TEXTURE_2D );
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Crate.PNG" ), GL_TEXTURE_2D );

  glEnable( GL_LIGHT1 );
  glLightfv( GL_LIGHT1, GL_AMBIENT,  _pd->m_lAmbient  );
  glLightfv( GL_LIGHT1, GL_DIFFUSE,  _pd->m_lDiffuse  );
  glLightfv( GL_LIGHT1, GL_POSITION, _pd->m_lPosition );
}

void Lesson07::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, _pd->m_zOffset );

  glRotatef( _pd->m_rAngle.x(), 1, 0, 0 );
  glRotatef( _pd->m_rAngle.y(), 0, 1, 0 );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
  _pd->drawCube();
}

void Lesson07::resizeGL(int width, int height)
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson07::idleFunc()
{
  _pd->m_rAngle += _pd->m_rSpeed;
  updateGL();
}

void Lesson07::keyPressEvent( QKeyEvent* event )
{
  switch( event->key() ) {
  case Qt::Key_L: {
    _pd->m_bLight = !_pd->m_bLight;
    _pd->m_bLight ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
  } break;

  case Qt::Key_F: {
    _pd->changeFilter();
  } break;

  case Qt::Key_PageUp: {
    _pd->m_zOffset -= 0.02f;
  } break;

  case Qt::Key_PageDown: {
    _pd->m_zOffset += 0.02f;
  } break;

  case Qt::Key_Up: {
    _pd->m_rSpeed.setX( _pd->m_rSpeed.x()-0.01f );
  } break;

  case Qt::Key_Down: {
    _pd->m_rSpeed.setX( _pd->m_rSpeed.x()+0.01f );
  } break;

  case Qt::Key_Left: {
    _pd->m_rSpeed.setY( _pd->m_rSpeed.y()-0.01f );
  } break;

  case Qt::Key_Right: {
    _pd->m_rSpeed.setY( _pd->m_rSpeed.y()+0.01f );
  } break;

  default: GLWidget::keyPressEvent( event );
  }
}

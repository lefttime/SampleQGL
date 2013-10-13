#include "Lesson16.hpp"

#include <QPixmap>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QKeyEvent>

GLuint fogfilter = 0;								                // Which Fog Mode To Use 
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };	// Storage For Three Types Of Fog
GLfloat	fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f  };	// Fog Color

class Lesson16::Lesson16Private
{
public:

  Lesson16Private( Lesson16* me ) : m_self( me ) {
  }

  ~Lesson16Private() {
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

  Lesson16*         m_self;
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

Lesson16::Lesson16( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson16Private( this ) )
{
  setWindowTitle( "Lesson16" );
  _pd->init();
}

Lesson16::~Lesson16()
{
}

void Lesson16::initializeGL()
{
  glEnable( GL_TEXTURE_2D );							              // Enable Texture Mapping
  glShadeModel( GL_SMOOTH );							              // Enable Smooth Shading
  glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );					      // We'll Clear To The Color Of The Fog
  glClearDepth( 1.0f );									                // Depth Buffer Setup
  glEnable( GL_DEPTH_TEST );							              // Enables Depth Testing
  glDepthFunc( GL_LEQUAL );								              // The Type Of Depth Testing To Do
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );  // Really Nice Perspective Calculations

  glLightfv( GL_LIGHT1, GL_AMBIENT,  _pd->m_lAmbient );	// Setup The Ambient Light
  glLightfv( GL_LIGHT1, GL_DIFFUSE,  _pd->m_lDiffuse );	// Setup The Diffuse Light
  glLightfv( GL_LIGHT1, GL_POSITION, _pd->m_lPosition);	// Position The Light
  glEnable( GL_LIGHT1 );								                // Enable Light One

  glFogi( GL_FOG_MODE,  fogMode[fogfilter] );			      // Fog Mode
  glFogfv( GL_FOG_COLOR, fogColor );					          // Set Fog Color
  glFogf( GL_FOG_DENSITY, 0.35f );						          // How Dense Will The Fog Be
  glHint( GL_FOG_HINT, GL_DONT_CARE );					        // Fog Hint Value
  glFogf( GL_FOG_START, 1.0f );							            // Fog Start Depth
  glFogf( GL_FOG_END, 5.0f );							              // Fog End Depth
  glEnable( GL_FOG );									                  // Enables GL_FOG

  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Crate.PNG" ), GL_TEXTURE_2D );
}

void Lesson16::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, _pd->m_zOffset );

  glRotatef( _pd->m_rAngle.x(), 1, 0, 0 );
  glRotatef( _pd->m_rAngle.y(), 0, 1, 0 );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
  _pd->drawCube();
}

void Lesson16::resizeGL(int width, int height)
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson16::idleFunc()
{
  _pd->m_rAngle += _pd->m_rSpeed;
  updateGL();
}

void Lesson16::keyStatusChanged()
{
  if( keyStatus( Qt::Key_F ) == ON ) {
    _pd->changeFilter();
  }

  if( keyStatus( Qt::Key_G ) == ON ) {
    fogfilter = (fogfilter+1) % 3;
    glFogi( GL_FOG_MODE,  fogMode[fogfilter] );
  }

  if( keyStatus( Qt::Key_L ) == ON ) {
    _pd->m_bLight = !_pd->m_bLight;
    _pd->m_bLight ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
  }

  if( keyStatus( Qt::Key_Q ) == ON || keyStatus( Qt::Key_PageUp ) == ON ) {
    _pd->m_zOffset -= 0.02f;
  }

  if( keyStatus( Qt::Key_E ) == ON || keyStatus( Qt::Key_PageDown ) == ON ) {
    _pd->m_zOffset += 0.02f;
  }

  if( keyStatus( Qt::Key_W ) == ON || keyStatus( Qt::Key_Up ) == ON ) {
    _pd->m_rSpeed.setX( _pd->m_rSpeed.x()-0.01f );
  }

  if( keyStatus( Qt::Key_S ) == ON || keyStatus( Qt::Key_Down ) == ON ) {
    _pd->m_rSpeed.setX( _pd->m_rSpeed.x()+0.01f );
  }

  if( keyStatus( Qt::Key_A ) == ON || keyStatus( Qt::Key_Left ) == ON ) {
    _pd->m_rSpeed.setY( _pd->m_rSpeed.y()-0.01f );
  }

  if( keyStatus( Qt::Key_D ) == ON || keyStatus( Qt::Key_Right ) == ON ) {
    _pd->m_rSpeed.setY( _pd->m_rSpeed.y()+0.01f );
  }
}

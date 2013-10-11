#include "Lesson09.hpp"

const int num = 50;
typedef struct {
  GLfloat red;
  GLfloat green;
  GLfloat blue;
  GLfloat dist;
  GLfloat angle;
} Stars;
Stars star[num];

class Lesson09::Lesson09Private
{
public:

  Lesson09Private( Lesson09* me ) : m_self( me ) {
  }

  ~Lesson09Private() {
    m_self->deleteTexture( m_texture );
  }

  void init() {
    m_fZoom = -15.0f;
    m_fTilt = 90.0f;
    for( int idx = 0; idx < num; ++idx ) {
      star[idx].angle = 0.0f;
      star[idx].dist  = (float(idx)/num)*5.0f;
      star[idx].red   = qrand() % 256;
      star[idx].green = qrand() % 256;
      star[idx].blue  = qrand() % 256;
    }
  }

  void drawStar( int idx ) {
    glColor4ub( star[num-idx-1].red, star[num-idx-1].green, star[num-idx-1].blue, 255 );
    glBegin( GL_QUADS );
    {
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f, -1.0f, 0.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 0.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f,  1.0f, 0.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f,  1.0f, 0.0f );
    }
    glEnd();
  }

  Lesson09*         m_self;
  GLuint            m_texture;

  bool              m_bTwinkle;
  GLfloat           m_fZoom;
  GLfloat           m_fTilt;
  GLfloat           m_fSpin;
};

Lesson09::Lesson09( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson09Private( this ) )
{
  setWindowTitle( "Lesson09" );
  _pd->init();
}

Lesson09::~Lesson09()
{
}

void Lesson09::initializeGL()
{
  glEnable( GL_TEXTURE_2D );
  glShadeModel( GL_SMOOTH );
  qglClearColor( Qt::black );

  glClearDepth( 1.0f );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE );
  glEnable( GL_BLEND );

  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Star.png" ), GL_TEXTURE_2D );
}

void Lesson09::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
  for( int idx = 0; idx < num; ++idx ) {
    glLoadIdentity();
    glTranslatef( 0.0f, 0.0f, _pd->m_fZoom );
    glRotatef( _pd->m_fTilt, 1, 0, 0 );

    glRotatef( star[idx].angle, 0, 1, 0 );
    glTranslatef( star[idx].dist, 0.0f, 0.0f );

    glRotatef( -star[idx].angle, 0, 1, 0 );
    glRotatef( -_pd->m_fTilt, 1, 0, 0 );

    if( _pd->m_bTwinkle ) {
      _pd->drawStar( idx );
    }

    glRotatef( _pd->m_fSpin, 0, 0, 1 );
    _pd->drawStar( idx );

    _pd->m_fSpin += 0.01f;
    star[idx].angle += float(idx) / num;
    star[idx].dist -= 0.01f;

    if( star[idx].dist < 0.0f ) {
      star[idx].dist += 5.0f;
      star[idx].red   = qrand() % 256;
      star[idx].green = qrand() % 256;
      star[idx].blue  = qrand() % 256;
    }
  }
}

void Lesson09::resizeGL(int width, int height)
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson09::idleFunc()
{
  updateGL();
}

void Lesson09::keyPressEvent( QKeyEvent* event )
{
  switch( event->key() ) {
  case Qt::Key_T: {
    _pd->m_bTwinkle = !_pd->m_bTwinkle;
  } break;

  case Qt::Key_Up: {
    _pd->m_fTilt -= 0.5f;
  } break;

  case Qt::Key_Down: {
    _pd->m_fTilt += 0.5f;
  } break;

  case Qt::Key_PageUp: {
    _pd->m_fZoom -= 0.2f;
  } break;

  case Qt::Key_PageDown: {
    _pd->m_fZoom += 0.2f;
  } break;

  default: GLWidget::keyPressEvent( event );
  }
}

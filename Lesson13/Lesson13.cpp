#include "Lesson13.hpp"

GLfloat	cnt1;				// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2;				// 2nd Counter Used To Move Text & For Coloring

class Lesson13::Lesson13Private
{
public:

  Lesson13Private( Lesson13* me ) : m_self( me ) {
  }

  void init() {
    m_font.setFamily( "Courier New" );
    m_font.setPixelSize( 24 );
  }

  void drawText( int xpos, int ypos, const QString& content ) {
    m_self->renderText( xpos, ypos, content, m_font );
  }

  Lesson13*           m_self;
  QFont               m_font;
  GLuint	            m_base;
};

Lesson13::Lesson13( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson13Private( this ) )
{
  setWindowTitle( "Lesson13" );
  _pd->init();
}

Lesson13::~Lesson13()
{
}

void Lesson13::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Lesson13::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, -1.0f );

  float fRed   = qBound( 0.0f, 1.0f*float(cos(cnt1)),           1.0f );
  float fGreen = qBound( 0.0f, 1.0f*float(sin(cnt2)),           1.0f );
  float fBlue  = qBound( 0.0f, 1.0f-0.5f*float(cos(cnt1+cnt2)), 1.0f );
  glColor3f( fRed, fGreen, fBlue );

  float xRate = -0.45f+0.05f*float(cos(cnt1));
  float yRate = 0.32f*float(sin(cnt2));
  int xpos = xRate * width() + width()/2;
  int ypos = yRate * height() + height()/2;

  char content[256];
  sprintf_s( content, 256, "Active OpenGL Text With NeHe - %7.2f", cnt1 );
  _pd->drawText( xpos, ypos, content );
}

void Lesson13::idleFunc()
{
  cnt1 += 0.051f;
  cnt2 += 0.005f;
  updateGL();
}

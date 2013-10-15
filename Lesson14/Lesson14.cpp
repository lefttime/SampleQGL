#include "Lesson14.hpp"

GLYPHMETRICSFLOAT gmf[256];	// Storage For Information About Our Outline Font Characters

class Lesson14::Lesson14Private
{
public:

  Lesson14Private( Lesson14* me ) : m_self( me ) {
  }

  void init() {
    m_fRot = 0;

#ifdef Q_OS_WIN32
    QFont hFont( "Comic Sans MS", -12 );
    hFont.setBold( true );
    SelectObject( wglGetCurrentDC(), hFont.handle() );

    m_base = glGenLists( 256 );
    wglUseFontOutlines(	wglGetCurrentDC(),
                        0,								// Starting Character
                        255,							// Number Of Display Lists To Build
                        m_base,						// Starting Display Lists
                        0.0f,							// Deviation From The True Outlines
                        0.2f,							// Font Thickness In The Z Direction
                        WGL_FONT_POLYGONS,// Use Polygons, Not Lines
                        gmf );						// Address Of Buffer To Recieve Data
#endif
  }

  void drawText( const QString& content ) {
    float length = 0;								                                                      // Used To Find The Length Of The Text
    for( unsigned int loop = 0; loop < content.count(); ++loop )                          // Loop To Find Text Length
    {
      length += gmf[content.at(loop).toAscii()].gmfCellIncX;			                        // Increase Length By Each Characters Width
    }

    glTranslatef( -length/2, 0.0f, 0.0f );					                                      // Center Our Text On The Screen

    glPushAttrib( GL_LIST_BIT );							                                            // Pushes The Display List Bits
    glListBase( m_base );									                                                // Sets The Base Character to 0
    glCallLists( content.count(), GL_UNSIGNED_BYTE, content.toLocal8Bit().constData() );	// Draws The Display List Text
    glPopAttrib();                                                                        // Pops The Display List Bits
  }

  Lesson14*           m_self;
  GLuint              m_base;

  float               m_fRot;
};

Lesson14::Lesson14( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson14Private( this ) )
{
  setWindowTitle( "Lesson14" );
  _pd->init();
}

Lesson14::~Lesson14()
{
}

void Lesson14::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  glEnable(GL_LIGHT0);								// Enable Default Light (Quick And Dirty)
  glEnable(GL_LIGHTING);							// Enable Lighting
  glEnable(GL_COLOR_MATERIAL);				// Enable Coloring Of Material
}

void Lesson14::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, -10.0f );
  glRotatef( _pd->m_fRot,      1, 0, 0 );
  glRotatef( _pd->m_fRot*1.5f, 0, 1, 0 );
  glRotatef( _pd->m_fRot*1.4f, 0, 0, 1 );

  // Pulsing Colors Based On The Rotation
  float fRed   = qBound( 0.0f, 1.0f*float(cos(_pd->m_fRot/20.0f)),      1.0f );
  float fGreen = qBound( 0.0f, 1.0f*float(sin(_pd->m_fRot/25.0f)),      1.0f );
  float fBlue  = qBound( 0.0f, 1.0f-0.5f*float(cos(_pd->m_fRot/17.0f)), 1.0f );
  glColor3f( fRed, fGreen, fBlue );

  char content[256];
  sprintf_s( content, 256, "Lesson14 - %3.2f", _pd->m_fRot/50 );
  _pd->drawText( content );
}

void Lesson14::idleFunc()
{
  _pd->m_fRot += 0.5f;
  updateGL();
}

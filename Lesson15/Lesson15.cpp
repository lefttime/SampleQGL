#include "Lesson15.hpp"

GLYPHMETRICSFLOAT gmf[256];	// Storage For Information About Our Outline Font Characters

class Lesson15::Lesson15Private
{
public:

  Lesson15Private( Lesson15* me ) : m_self( me ) {
  }

  ~Lesson15Private() {
    m_self->deleteTexture( m_texture );
  }

  void init() {
    m_fRot = 0;

#ifdef Q_OS_WIN32
    HFONT	hFont = CreateFont(	-12,							          // Height Of Font
                              0,								          // Width Of Font
                              0,								          // Angle Of Escapement
                              0,								          // Orientation Angle
                              FW_BOLD,						        // Font Weight
                              FALSE,							        // Italic
                              FALSE,							        // Underline
                              FALSE,							        // Strikeout
                              SYMBOL_CHARSET,
                              OUT_TT_PRECIS,					    // Output Precision
                              CLIP_DEFAULT_PRECIS,			  // Clipping Precision
                              ANTIALIASED_QUALITY,			  // Output Quality
                              FF_DONTCARE|DEFAULT_PITCH,	// Family And Pitch
                              L"Wingdings" );				      // Font Name

    SelectObject( wglGetCurrentDC(), hFont );

    m_base = glGenLists( 256 );
    wglUseFontOutlines(	wglGetCurrentDC(),
                        0,								// Starting Character
                        255,							// Number Of Display Lists To Build
                        m_base,						// Starting Display Lists
                        0.1f,							// Deviation From The True Outlines
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

  Lesson15*           m_self;

  GLuint              m_base;
  GLuint              m_texture;

  float               m_fRot;
};

Lesson15::Lesson15( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson15Private( this ) )
{
  setWindowTitle( "Lesson15" );
  _pd->init();
}

Lesson15::~Lesson15()
{
}

void Lesson15::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  glEnable(GL_LIGHT0);								// Enable Default Light (Quick And Dirty)
  glEnable(GL_LIGHTING);							// Enable Lighting

  glEnable( GL_TEXTURE_2D );
  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Lights.PNG" ), GL_TEXTURE_2D );
  glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
  glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
  glEnable( GL_TEXTURE_GEN_S );
  glEnable( GL_TEXTURE_GEN_T );
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
}

void Lesson15::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  glTranslatef( 1.1f*float(cos(_pd->m_fRot/16.0f)), 0.8f*float(sin(_pd->m_fRot/20.0f)), -3.0f );

  glRotatef( _pd->m_fRot,      1, 1, 0 );        // Rotate On The X Axis
  glRotatef( _pd->m_fRot*1.2f, 0, 1, 0 );        // Rotate On The Y Axis
  glRotatef( _pd->m_fRot*1.4f, 0, 0, 1 );        // Rotate On The Z Axis

  glTranslatef( -0.35f, -0.35f, 0.1f );          // Center On X, Y, Z Axis

  _pd->drawText( "N" );                          // Draw A Skull And Crossbones Symbol
}

void Lesson15::idleFunc()
{
  _pd->m_fRot += 0.3f;
  updateGL();
}

#include "Lesson20.hpp"

bool	  scene;			  // Which Scene To Draw
GLfloat	roll;				  // Rolling Texture
bool	masking = true;	// Masking On/Off

class Lesson20::Lesson20Private
{
public:

  Lesson20Private( Lesson20* me ) : m_self( me ) {
  }

  ~Lesson20Private() {
    for( int idx = 0; idx < 5; ++idx ) {
      m_self->deleteTexture( m_texture[idx] );
    }
  }

  Lesson20*         m_self;
  GLuint            m_texture[5];
};

Lesson20::Lesson20( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson20Private( this ) )
{
  setWindowTitle( "Lesson20" );
}

Lesson20::~Lesson20()
{
}

void Lesson20::initializeGL()
{
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );                               // Clear The Background Color To Black
  glClearDepth( 1.0f );                                                 // Enables Clearing Of The Depth Buffer
  glEnable( GL_DEPTH_TEST );                                            // Enable Depth Testing
  glShadeModel( GL_SMOOTH );                                            // Enables Smooth Color Shading
  glEnable( GL_TEXTURE_2D );                                            // Enable 2D Texture Mapping

  _pd->m_texture[0] = bindTexture( QPixmap( ":/Resources/Logo.PNG"  ), GL_TEXTURE_2D );
  _pd->m_texture[1] = bindTexture( QPixmap( ":/Resources/Mask1.PNG" ), GL_TEXTURE_2D );
  _pd->m_texture[2] = bindTexture( QPixmap( ":/Resources/Image1.PNG"), GL_TEXTURE_2D );
  _pd->m_texture[3] = bindTexture( QPixmap( ":/Resources/Mask2.PNG" ), GL_TEXTURE_2D );
  _pd->m_texture[4] = bindTexture( QPixmap( ":/Resources/Image2.PNG"), GL_TEXTURE_2D );
}

void Lesson20::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );                 // Clear The Screen And The Depth Buffer
  glLoadIdentity();                                                     // Reset The Modelview Matrix
  glTranslatef( 0.0f, 0.0f, -2.0f );                                    // Move Into The Screen 5 Units

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture[0] );                    // Select Our Logo Texture
  glBegin( GL_QUADS );                                                  // Start Drawing A Textured Quad
  {
    glTexCoord2f( 0.0f, -roll+0.0f ); glVertex3f(-1.1f, -1.1f,  0.0f );	// Bottom Left
    glTexCoord2f( 3.0f, -roll+0.0f ); glVertex3f( 1.1f, -1.1f,  0.0f );	// Bottom Right
    glTexCoord2f( 3.0f, -roll+3.0f ); glVertex3f( 1.1f,  1.1f,  0.0f );	// Top Right
    glTexCoord2f( 0.0f, -roll+3.0f ); glVertex3f(-1.1f,  1.1f,  0.0f );	// Top Left
  }
  glEnd();                                                              // Done Drawing The Quad

  glEnable( GL_BLEND );                                                 // Enable Blending
  glDisable( GL_DEPTH_TEST );                                           // Disable Depth Testing

  // (Rs*Sr+Rd*Dr, Gs*Sg+Gd*Dg, Bs*Sb+Bd*Db, As*Sa+Ad*Da) 
  if( masking ) {                                                       // Is Masking Enabled?
    //glBlendFunc( GL_DST_COLOR, GL_ZERO );                               // Blend Screen Color With Zero (Black)
    glBlendFunc( GL_ONE, GL_ZERO );
  }

  if( scene ) {                                                         // Are We Drawing The Second Scene?
    glTranslatef( 0.0f, 0.0f, -1.0f );                                  // Translate Into The Screen One Unit
    glRotatef( roll*360, 0, 0, 1 );                                     // Rotate On The Z Axis 360 Degrees.
    if( masking ) {                                                     // Is Masking On?
      glBindTexture( GL_TEXTURE_2D, _pd->m_texture[3] );                // Select The Second Mask Texture
      glBegin( GL_QUADS );                                              // Start Drawing A Textured Quad
      {
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.1f, -1.1f, 0.0f );    // Bottom Left
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.1f, -1.1f, 0.0f );    // Bottom Right
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.1f,  1.1f, 0.0f );    // Top Right
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.1f,  1.1f, 0.0f );    // Top Left
      }
      glEnd();                                                          // Done Drawing The Quad
    }

    glBlendFunc( GL_ONE, GL_ONE );					                            // Copy Image 2 Color To The Screen
    glBindTexture( GL_TEXTURE_2D, _pd->m_texture[4] );		              // Select The Second Image Texture
    glBegin( GL_QUADS );								                                // Start Drawing A Textured Quad
    {
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	      // Bottom Left
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	      // Bottom Right
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	      // Top Right
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	      // Top Left
    }
    glEnd();										                                        // Done Drawing The Quad
  } else {												                                      // Otherwise
    if( masking ) {                                                     // Is Masking On?
      glBindTexture( GL_TEXTURE_2D, _pd->m_texture[1] );	              // Select The First Mask Texture
      glBegin( GL_QUADS );							                                // Start Drawing A Textured Quad
      {
        glTexCoord2f(roll+0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
        glTexCoord2f(roll+4.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
        glTexCoord2f(roll+4.0f, 4.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
        glTexCoord2f(roll+0.0f, 4.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
      }
      glEnd();									                                        // Done Drawing The Quad
    }

    glBlendFunc( GL_ONE, GL_ONE );					                            // Copy Image 1 Color To The Screen
    glBindTexture( GL_TEXTURE_2D, _pd->m_texture[2] );		              // Select The First Image Texture
    glBegin( GL_QUADS );								                                // Start Drawing A Textured Quad
    {
      glTexCoord2f(roll+0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);   // Bottom Left
      glTexCoord2f(roll+4.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);   // Bottom Right
      glTexCoord2f(roll+4.0f, 4.0f); glVertex3f( 1.1f,  1.1f,  0.0f);   // Top Right
      glTexCoord2f(roll+0.0f, 4.0f); glVertex3f(-1.1f,  1.1f,  0.0f);   // Top Left
    }
    glEnd();										                                        // Done Drawing The Quad
  }

  glEnable( GL_DEPTH_TEST );                                            // Enable Depth Testing
  glDisable( GL_BLEND );                                                // Disable Blending
}

void Lesson20::idleFunc()
{
  roll += 0.002f;			  // Increase Our Texture Roll Variable
  if( roll > 1.0f )	{	  // Is Roll Greater Than One
    roll -= 1.0f;			  // Subtract 1 From Roll
  }

  updateGL();
}

void Lesson20::keyStatusChanged()
{
  if( keyStatus( Qt::Key_Space ) == ON ) {
    scene = !scene;
  }

  if( keyStatus( Qt::Key_M ) == ON ) {
    masking = !masking;
  }
}

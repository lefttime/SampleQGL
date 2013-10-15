#include "Lesson17.hpp"

GLfloat	cnt1;				// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2;				// 2nd Counter Used To Move Text & For Coloring

class Lesson17::Lesson17Private
{
public:

  Lesson17Private( Lesson17* me ) : m_self( me ) {
  }

  ~Lesson17Private() {
    m_self->deleteTexture( m_texture[0] );
    m_self->deleteTexture( m_texture[1] );
    glDeleteLists( m_base, 256 );
  }

  void init() {
    buildFont();
  }

  void buildFont() {
    float	cx;											                    // Holds Our X Character Coord
    float	cy;											                    // Holds Our Y Character Coord

    m_base = glGenLists( 256 );		                    // Creating 256 Display Lists
    glBindTexture( GL_TEXTURE_2D, m_texture[0] );			// Select Our Font Texture
    for( int loop = 0; loop < 256; ++loop ) {					// Loop Through All 256 Lists
      cx = float(loop%16) / 16.0f;						        // X Position Of Current Character
      cy = float(loop/16) / 16.0f;						        // Y Position Of Current Character

      glNewList( m_base+loop, GL_COMPILE );				    // Start Building A List
      {
        glBegin( GL_QUADS );							            // Use A Quad For Each Character
        {
          glTexCoord2f( cx, 1-cy-0.0625f );			      // Texture Coord (Bottom Left)
          glVertex2i( 0, 0 );						              // Vertex Coord (Bottom Left)

          glTexCoord2f( cx+0.0625f, 1-cy-0.0625f );	  // Texture Coord (Bottom Right)
          glVertex2i( 16, 0 );						            // Vertex Coord (Bottom Right)

          glTexCoord2f( cx+0.0625f, 1-cy );			      // Texture Coord (Top Right)
          glVertex2i( 16, 16 );						            // Vertex Coord (Top Right)

          glTexCoord2f( cx, 1-cy );					          // Texture Coord (Top Left)
          glVertex2i( 0, 16 );						            // Vertex Coord (Top Left)
        }
        glEnd();									                    // Done Building Our Quad (Character)
        glTranslated( 10, 0, 0 );						          // Move To The Right Of The Character
      }
      glEndList();									                  // Done Building The Display List
    }													                        // Loop Until All 256 Are Built
  }

  void glPrint( int xpos, int ypos, char* string, int set )	{ // Where The Printing Happens
    set = qMin( set, 1 );
    glBindTexture( GL_TEXTURE_2D, m_texture[0] );			        // Select Our Font Texture
    glDisable( GL_DEPTH_TEST );							                  // Disables Depth Testing

    glMatrixMode( GL_PROJECTION );						                // Select The Projection Matrix
    glPushMatrix();										                        // Store The Projection Matrix
    glLoadIdentity();									                        // Reset The Projection Matrix
    glOrtho( 0, 640, 0, 480, -1, 1 );					                // Set Up An Ortho Screen

    glMatrixMode(GL_MODELVIEW);							                  // Select The Modelview Matrix
    glPushMatrix();										                        // Store The Modelview Matrix
    glLoadIdentity();									                        // Reset The Modelview Matrix
    glTranslated( xpos, ypos, 0 );						                // Position The Text (0,0 - Bottom Left)

    glListBase( m_base-32+(128*set) );				                // Choose The Font Set (0 or 1)
    glCallLists( strlen(string), GL_UNSIGNED_BYTE, string );  // Write The Text To The Screen

    glMatrixMode( GL_PROJECTION );						                // Select The Projection Matrix
    glPopMatrix();										                        // Restore The Old Projection Matrix

    glMatrixMode( GL_MODELVIEW );							                // Select The Modelview Matrix
    glPopMatrix();										                        // Restore The Old Projection Matrix

    glEnable( GL_DEPTH_TEST );							                  // Enables Depth Testing
  }

  Lesson17*           m_self;
  QFont               m_font;
  GLuint	            m_base;
  GLuint              m_texture[2];
};

Lesson17::Lesson17( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson17Private( this ) )
{
  setWindowTitle( "Lesson17" );
  _pd->init();
}

Lesson17::~Lesson17()
{
}

void Lesson17::initializeGL()
{
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );	// Clear The Background Color To Black
  glClearDepth( 1.0 );									  // Enables Clearing Of The Depth Buffer
  glDepthFunc( GL_LEQUAL );								// The Type Of Depth Test To Do
  glBlendFunc( GL_SRC_ALPHA,GL_ONE );			// Select The Type Of Blending
  glShadeModel( GL_SMOOTH );							// Enables Smooth Color Shading
  glEnable( GL_TEXTURE_2D );							// Enable 2D Texture Mapping

  _pd->m_texture[0] = bindTexture( QPixmap( ":/Resources/Font.PNG" ),  GL_TEXTURE_2D );
  _pd->m_texture[1] = bindTexture( QPixmap( ":/Resources/Bumps.PNG" ), GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture[0] );
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture[1] );
}

void Lesson17::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
  glLoadIdentity();									                    // Reset The Modelview Matrix
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture[1] );		// Select Our Second Texture
  glTranslatef( 0.0f, 0.0f, -5.0f );						        // Move Into The Screen 5 Units
  glRotatef( 45.0f, 0, 0, 1 );					                // Rotate On The Z Axis 45 Degrees (Clockwise)
  glRotatef( cnt1*30.0f, 1, 1, 0 );				              // Rotate On The X & Y Axis By cnt1 (Left To Right)
  glDisable( GL_BLEND );								                // Disable Blending Before We Draw In 3D
  glColor3f( 1.0f,1.0f,1.0f );					                // Bright White
  glBegin( GL_QUADS );									                // Draw Our First Texture Mapped Quad
  {
    glTexCoord2d( 0.0f, 0.0f );						              // First Texture Coord
    glVertex2f( -1.0f, 1.0f );						              // First Vertex

    glTexCoord2d( 1.0f, 0.0f );						              // Second Texture Coord
    glVertex2f( 1.0f, 1.0f);						                // Second Vertex

    glTexCoord2d( 1.0f, 1.0f );						              // Third Texture Coord
    glVertex2f( 1.0f, -1.0f );						              // Third Vertex

    glTexCoord2d( 0.0f, 1.0f );						              // Fourth Texture Coord
    glVertex2f( -1.0f, -1.0f );						              // Fourth Vertex
  }
  glEnd();											                        // Done Drawing The First Quad

  glRotatef( 90.0f, 1, 1, 0 );					                // Rotate On The X & Y Axis By 90 Degrees (Left To Right)
  glBegin( GL_QUADS );									                // Draw Our Second Texture Mapped Quad
  {
    glTexCoord2d( 0.0f, 0.0f );					                // First Texture Coord
    glVertex2f( -1.0f, 1.0f );					                // First Vertex
    glTexCoord2d( 1.0f, 0.0f );					                // Second Texture Coord
    glVertex2f( 1.0f, 1.0f );						                // Second Vertex
    glTexCoord2d( 1.0f, 1.0f );					                // Third Texture Coord
    glVertex2f( 1.0f, -1.0f );					                // Third Vertex
    glTexCoord2d( 0.0f, 1.0f );					                // Fourth Texture Coord
    glVertex2f( -1.0f, -1.0f );					                // Fourth Vertex
  }
  glEnd();											                        // Done Drawing Our Second Quad
  glEnable( GL_BLEND );									                // Enable Blending

  glLoadIdentity();									                    // Reset The View

  // Pulsing Colors Based On Text Position
  glColor3f( 1.0f*float(cos(cnt1)), 1.0f*float(sin(cnt2)), 1.0f-0.5f*float(cos(cnt1+cnt2)) );
  _pd->glPrint( int((280+250*cos(cnt1))), int(235+200*sin(cnt2)), "NeHe", 0 );		// Print GL Text To The Screen

  glColor3f( 1.0f*float(sin(cnt2)), 1.0f-0.5f*float(cos(cnt1+cnt2)), 1.0f*float(cos(cnt1)) );
  _pd->glPrint( int((280+230*cos(cnt2))), int(235+200*sin(cnt1)), "OpenGL", 1 );	// Print GL Text To The Screen

  glColor3f( 0.0f, 0.0f, 1.0f );							// Set Color To Blue
  _pd->glPrint( int(240+200*cos((cnt2+cnt1)/5)), 2, "Giuseppe D'Agata", 0 );

  glColor3f( 1.0f, 1.0f, 1.0f );							// Set Color To White
  _pd->glPrint( int(242+200*cos((cnt2+cnt1)/5)), 2, "Giuseppe D'Agata", 0 );
}

void Lesson17::idleFunc()
{
  cnt1 += 0.01f;    // Increase The First Counter
  cnt2 += 0.0081f;  // Increase The Second Counter
  updateGL();
}

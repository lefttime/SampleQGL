#include "Lesson19.hpp"

#include <QPixmap>
#include <QVector3D>

#define	MAX_PARTICLES	1000		// Number Of Particles To Create

float	slowdown = 2.0f;				// Slow Down Particles
float	xspeed;						      // Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						      // Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoom=-40.0f;				    // Used To Zoom Out

GLuint	col;						      // Current Color Selection
GLuint	delay;						    // Rainbow Effect Delay

typedef struct						    // Create A Structure For Particle
{
  bool	active;					      // Active (Yes/No)
  float	life;					        // Particle Life
  float	fade;					        // Fade Speed
  float	r;						        // Red Value
  float	g;						        // Green Value
  float	b;						        // Blue Value
  float	xpos;						      // X Position
  float	ypos;						      // Y Position
  float	zpos;						      // Z Position
  float	xi;						        // X Direction
  float	yi;						        // Y Direction
  float	zi;						        // Z Direction
  float	xg;						        // X Gravity
  float	yg;						        // Y Gravity
  float	zg;						        // Z Gravity
} particles;							    // Particles Structure

particles particle[MAX_PARTICLES];// Particle Array (Room For Particle Info)

static GLfloat colors[12][3] = { // Rainbow Of Colors
  {1.0f,0.5f,0.5f}, {1.0f,0.75f,0.5f}, {1.0f,1.0f,0.5f}, {0.75f,1.0f,0.5f},
  {0.5f,1.0f,0.5f}, {0.5f,1.0f,0.75f}, {0.5f,1.0f,1.0f}, {0.5f,0.75f,1.0f},
  {0.5f,0.5f,1.0f}, {0.75f,0.5f,1.0f}, {1.0f,0.5f,1.0f}, {1.0f,0.5f,0.75f}
};

class Lesson19::Lesson19Private
{
public:

  Lesson19Private( Lesson19* me ) : m_self( me ) {
  }

  ~Lesson19Private() {
    m_self->deleteTexture( m_texture );
  }

  void init() {
    for( int idx = 0; idx < MAX_PARTICLES; ++idx ) {
      particle[idx].active= true;								                // Make All The Particles Active
      particle[idx].life  = 1.0f;								                // Give All The Particles Full Life
      particle[idx].fade  = float(qrand()%100)/1000.0f+0.003f;	// qrandom Fade Speed
      particle[idx].r     = colors[idx*(12/MAX_PARTICLES)][0];  // Select Red Rainbow Color
      particle[idx].g     = colors[idx*(12/MAX_PARTICLES)][1];  // Select Red Rainbow Color
      particle[idx].b     = colors[idx*(12/MAX_PARTICLES)][2];  // Select Red Rainbow Color
      particle[idx].xi    = float((qrand()%50)-26.0f)*10.0f;		// qrandom Speed On X Axis
      particle[idx].yi    = float((qrand()%50)-25.0f)*10.0f;		// qrandom Speed On Y Axis
      particle[idx].zi    = float((qrand()%50)-25.0f)*10.0f;		// qrandom Speed On Z Axis
      particle[idx].xg    = 0.0f;									              // Set Horizontal Pull To Zero
      particle[idx].yg    =-0.8f;                               // Set Vertical Pull Downward
      particle[idx].zg    = 0.0f;									              // Set Pull On Z Axis To Zero
    }
  }

  void drawTriangleStrip( float xpos, float ypos, float zpos ) {
    glBegin( GL_TRIANGLE_STRIP );						                          // Build Quad From A Triangle Strip
    {
      glTexCoord2d( 1, 1 ); glVertex3f( xpos+0.5f, ypos+0.5f, zpos ); // Top Right
      glTexCoord2d( 0, 1 ); glVertex3f( xpos-0.5f, ypos+0.5f, zpos ); // Top Left
      glTexCoord2d( 1, 0 ); glVertex3f( xpos+0.5f, ypos-0.5f, zpos ); // Bottom Right
      glTexCoord2d( 0, 0 ); glVertex3f( xpos-0.5f, ypos-0.5f, zpos ); // Bottom Left
    }
    glEnd();                                                  // Done Building Triangle Strip
  }

  Lesson19*         m_self;
  GLuint            m_texture;
};

Lesson19::Lesson19( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson19Private( this ) )
{
  setWindowTitle( "Lesson19" );
  _pd->init();
}

Lesson19::~Lesson19()
{
}

void Lesson19::initializeGL()
{
  glClearDepth( 1.0f );

  glEnable( GL_TEXTURE_2D );
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

  glClearDepth( 1.0f );
  glDisable( GL_DEPTH_TEST );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA,GL_ONE );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Particle.PNG" ), GL_TEXTURE_2D );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
}

void Lesson19::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		      // Clear Screen And Depth Buffer
  glLoadIdentity();										                          // Reset The ModelView Matrix

  for( int idx = 0; idx < MAX_PARTICLES; ++idx ) {			        // Loop Through All The Particles
    if( particle[idx].active ) {                                // If The Particle Is Active
      float xpos = particle[idx].xpos;                          // Grab Our Particle X Position
      float ypos = particle[idx].ypos;                          // Grab Our Particle Y Position
      float zpos = particle[idx].zpos + zoom;                   // Particle Z Pos + Zoom

      // Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
      glColor4f( particle[idx].r, particle[idx].g, particle[idx].b, particle[idx].life );
      _pd->drawTriangleStrip( xpos, ypos, zpos );

      particle[idx].xpos += particle[idx].xi / (slowdown*1000); // Move On The X Axis By X Speed
      particle[idx].ypos += particle[idx].yi / (slowdown*1000); // Move On The Y Axis By Y Speed
      particle[idx].zpos += particle[idx].zi / (slowdown*1000); // Move On The Z Axis By Z Speed

      particle[idx].xi += particle[idx].xg;                     // Take Pull On X Axis Into Account
      particle[idx].yi += particle[idx].yg;                     // Take Pull On Y Axis Into Account
      particle[idx].zi += particle[idx].zg;                     // Take Pull On Z Axis Into Account
      particle[idx].life -= particle[idx].fade;                 // Reduce Particles Life By 'Fade'

      if( particle[idx].life < 0.0f ) {                         // If Particle Is Burned Out
        particle[idx].life = 1.0f;                              // Give It New Life
        particle[idx].fade = float(qrand()%100)/1000.0f+0.003f; // qrandom Fade Value
        particle[idx].xpos = 0.0f;                              // Center On X Axis
        particle[idx].ypos = 0.0f;                              // Center On Y Axis
        particle[idx].zpos = 0.0f;                              // Center On Z Axis
        particle[idx].xi= xspeed + float((qrand()%60)-32.0f);   // X Axis Speed And Direction
        particle[idx].yi= yspeed + float((qrand()%60)-30.0f);   // Y Axis Speed And Direction
        particle[idx].zi= float((qrand()%60)-30.0f);            // Z Axis Speed And Direction
        particle[idx].r = colors[col][0];                       // Select Red From Color Table
        particle[idx].g = colors[col][1];                       // Select Green From Color Table
        particle[idx].b = colors[col][2];                       // Select Blue From Color Table
      }

      // If Number Pad 8 And Y Gravity Is Less Than 1.5 Increase Pull Upwards
      if( keyStatus( Qt::Key_8 ) == ON && ( particle[idx].yg < 1.5f ) ) {
        particle[idx].yg += 0.01f;
      }

      // If Number Pad 2 And Y Gravity Is Greater Than -1.5 Increase Pull Downwards
      if( keyStatus( Qt::Key_2 ) == ON && ( particle[idx].yg > -1.5f ) ) {
        particle[idx].yg -= 0.01f;
      }

      // If Number Pad 6 And X Gravity Is Less Than 1.5 Increase Pull Right
      if( keyStatus( Qt::Key_6 ) == ON && ( particle[idx].xg < 1.5f ) ) {
        particle[idx].xg += 0.01f;
      }

      // If Number Pad 4 And X Gravity Is Greater Than -1.5 Increase Pull Left
      if( keyStatus( Qt::Key_4 ) == ON && ( particle[idx].xg > -1.5f ) ) {
        particle[idx].xg -= 0.01f;
      }

      if( keyStatus( Qt::Key_Tab ) == ON ) {                  // Tab Key Causes A Burst
        particle[idx].xpos = 0.0f;								            // Center On X Axis
        particle[idx].ypos = 0.0f;								            // Center On Y Axis
        particle[idx].zpos = 0.0f;								            // Center On Z Axis
        particle[idx].xi   = float((qrand()%50)-26.0f)*10.0f;	// qrandom Speed On X Axis
        particle[idx].yi   = float((qrand()%50)-25.0f)*10.0f;	// qrandom Speed On Y Axis
        particle[idx].zi   = float((qrand()%50)-25.0f)*10.0f;	// qrandom Speed On Z Axis
      }
    }
  }
}

void Lesson19::idleFunc()
{
  updateGL();
}

void Lesson19::keyStatusChanged()
{
  if( keyStatus( Qt::Key_Plus ) == ON ) {
    if( slowdown > 1.0f ) {
      slowdown -= 0.01f;
    }
  }

  if( keyStatus( Qt::Key_Minus ) == ON ) {
    if( slowdown < 4.0f ) {
      slowdown += 0.01f;
    }
  }

  if( keyStatus( Qt::Key_Space ) == ON ) {
    col = (col+1) % 12;
  }

  if( keyStatus( Qt::Key_Q ) == ON || keyStatus( Qt::Key_PageUp ) == ON ) {
    zoom -= 1.0f;
  }

  if( keyStatus( Qt::Key_E ) == ON || keyStatus( Qt::Key_PageDown ) == ON ) {
    zoom += 1.0f;
  }

  if( keyStatus( Qt::Key_W ) == ON || keyStatus( Qt::Key_Up ) == ON ) {
    if( yspeed < 200 ) {
      yspeed += 2.0f;
    }
  }

  if( keyStatus( Qt::Key_S ) == ON || keyStatus( Qt::Key_Down ) == ON ) {
    if( yspeed > -200 ) {
      yspeed -= 2.0f;
    }
  }

  if( keyStatus( Qt::Key_A ) == ON || keyStatus( Qt::Key_Left ) == ON ) {
    if( xspeed > -200) {
      xspeed -= 2.0f;
    }
  }

  if( keyStatus( Qt::Key_D ) == ON || keyStatus( Qt::Key_Right ) == ON ) {
    if( xspeed < 200 ) {
      xspeed += 2.0f;
    }
  }
}

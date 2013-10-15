#include "Lesson23.hpp"

int		part1;                                                  // Start Of Disc
int		part2;                                                  // End Of Disc
int		p1 = 0;                                                 // Increase 1
int		p2 = 1;                                                 // Increase 2

GLuint object = 1;                                            // Which Object To Draw
GLfloat	xrot;                                                 // X Rotation
GLfloat	yrot;                                                 // Y Rotation
GLfloat xspeed;                                               // X Rotation Speed
GLfloat yspeed;                                               // Y Rotation Speed
GLfloat	z = -10.0f;                                           // Depth Into The Screen

bool light;
GLuint filter;                                                // Which Filter To Use
GLUquadricObj* quadratic;                                     // Storage For Our Quadratic Objects

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

class Lesson23::Lesson23Private
{
public:

  Lesson23Private( Lesson23* me ) : m_self( me ) {
  }

  ~Lesson23Private() {
    for( int idx = 0; idx < 6; ++idx ) {
      m_self->deleteTexture( m_texture[idx] );
    }
  }

  void buildTexture() {
    glGenTextures( 6, &m_texture[0] );					// Create Three Textures (For Two Images)

    QImage textureImage[2];
    textureImage[0] = m_self->convertToGLFormat( QImage( ":/Resources/BG.PNG" ) );
    textureImage[1] = m_self->convertToGLFormat( QImage( ":/Resources/Reflect.PNG" ) );
    for( int loop = 0; loop < 2; ++loop ) {
      // Create Nearest Filtered Texture
      glBindTexture( GL_TEXTURE_2D, m_texture[loop] );	// Gen Tex 0 and 1
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
      glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage[loop].width(), textureImage[loop].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage[loop].bits() );

      // Create Linear Filtered Texture
      glBindTexture( GL_TEXTURE_2D, m_texture[loop+2] );	// Gen Tex 2 and 3 4
      glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
      glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
      glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage[loop].width(), textureImage[loop].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage[loop].bits() );

      // Create MipMapped Texture
      glBindTexture( GL_TEXTURE_2D, m_texture[loop+4]);	// Gen Tex 4 and 5
      glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
      gluBuild2DMipmaps( GL_TEXTURE_2D, 3, textureImage[loop].width(), textureImage[loop].height(), GL_RGBA, GL_UNSIGNED_BYTE, textureImage[loop].bits() );
    }
  }

  void drawCube() {
    glBegin( GL_QUADS );
    {
      // Front Face
      glNormal3f( 0.0f, 0.0f, 0.5f);
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f, -1.0f,  1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f,  1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f,  1.0f,  1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f,  1.0f,  1.0f );

      // Back Face
      glNormal3f( 0.0f, 0.0f,-0.5f);
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f, -1.0f, -1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f,  1.0f, -1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f,  1.0f, -1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );

      // Top Face
      glNormal3f( 0.0f, 0.5f, 0.0f);
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f,  1.0f, -1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f,  1.0f,  1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f,  1.0f,  1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f,  1.0f, -1.0f );

      // Bottom Face
      glNormal3f( 0.0f,-0.5f, 0.0f);
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f, -1.0f, -1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f,  1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f, -1.0f,  1.0f );

      // Right Face
      glNormal3f( 0.5f, 0.0f, 0.0f);
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f,  1.0f, -1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f,  1.0f,  1.0f );
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f,  1.0f );

      // Left Face
      glNormal3f(-0.5f, 0.0f, 0.0f);
      glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-1.0f, -1.0f, -1.0f );
      glTexCoord2f( 1.0f, 0.0f ); glVertex3f(-1.0f, -1.0f,  1.0f );
      glTexCoord2f( 1.0f, 1.0f ); glVertex3f(-1.0f,  1.0f,  1.0f );
      glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-1.0f,  1.0f, -1.0f );
    }
    glEnd();
  }

  Lesson23*         m_self;
  GLuint            m_texture[6];
};

Lesson23::Lesson23( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson23Private( this ) )
{
  setWindowTitle( "Lesson23" );
}

Lesson23::~Lesson23()
{
}

void Lesson23::initializeGL()
{
  glEnable( GL_TEXTURE_2D );                                  // Enable Texture Mapping
  _pd->buildTexture();

  glShadeModel( GL_SMOOTH );                                  // Enable Smooth Shading
  glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );                     // Black Background
  glClearDepth( 1.0f );									                      // Depth Buffer Setup
  glEnable( GL_DEPTH_TEST );                                  // Enables Depth Testing
  glDepthFunc( GL_LEQUAL );                                   // The Type Of Depth Testing To Do
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );        // Really Nice Perspective Calculations

  glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );           // Setup The Ambient Light
  glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );           // Setup The Diffuse Light
  glLightfv( GL_LIGHT1, GL_POSITION,LightPosition);           // Position The Light
  glEnable( GL_LIGHT1 );                                      // Enable Light One

  quadratic = gluNewQuadric();                                // Create A Pointer To The Quadric Object (Return 0 If No Memory)
  gluQuadricNormals( quadratic, GLU_SMOOTH );                 // Create Smooth Normals 
  gluQuadricTexture( quadratic, GL_TRUE );                    // Create Texture Coords 

  glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );      // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
  glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );      // Set The Texture Generation Mode For T To Sphere Mapping (NEW)
}

void Lesson23::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );       // Clear The Screen And The Depth Buffer
  glLoadIdentity();                                           // Reset The View

  glTranslatef( 0.0f, 0.0f, z );

  glEnable( GL_TEXTURE_GEN_S );                               // Enable Texture Coord Generation For S (NEW)
  glEnable( GL_TEXTURE_GEN_T );                               // Enable Texture Coord Generation For T (NEW)

   // This Will Select The Sphere Map
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture[filter+(filter+1)]);
  glPushMatrix();
  glRotatef( xrot, 1, 0, 0 );
  glRotatef( yrot, 0, 1, 0 );
  switch( object ) {
  case 0: _pd->drawCube(); break;

  case 1: {
    glTranslatef( 0.0f, 0.0f, -1.5f );                        // Center The Cylinder
    gluCylinder( quadratic, 1.0f, 1.0f, 3.0f, 32, 32 );       // A Cylinder With A Radius Of 0.5 And A Height Of 2
  } break;

  // Draw A Sphere With A Radius Of 1 And 16 Longitude And 16 Latitude Segments
  case 2: gluSphere( quadratic, 1.3f, 32, 32 ); break;

  case 3: {
    glTranslatef( 0.0f, 0.0f, -1.5f );                        // Center The Cone
    gluCylinder( quadratic, 1.0f, 0.0f, 3.0f, 32, 32 );       // A Cone With A Bottom Radius Of .5 And A Height Of 2
  } break;
  };

  glPopMatrix();
  glDisable( GL_TEXTURE_GEN_S );
  glDisable( GL_TEXTURE_GEN_T );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture[filter*2] );   // This Will Select The BG Maps...
  glPushMatrix();
  glTranslatef( 0.0f, 0.0f, -24.0f );
  glBegin( GL_QUADS );
  {
    glNormal3f( 0.0f, 0.0f, 1.0f );
    glTexCoord2f( 0.0f, 0.0f ); glVertex3f(-13.3f, -10.0f, 10.0f );
    glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 13.3f, -10.0f, 10.0f );
    glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 13.3f,  10.0f, 10.0f );
    glTexCoord2f( 0.0f, 1.0f ); glVertex3f(-13.3f,  10.0f, 10.0f );
  }
  glEnd();
  glPopMatrix();
}

void Lesson23::idleFunc()
{
  if( (keyStatus( Qt::Key_Q ) == ON || keyStatus( Qt::Key_PageUp ) == ON) ) {
    z -= 0.2f;
  }

  if( (keyStatus( Qt::Key_E ) == ON || keyStatus( Qt::Key_PageDown ) == ON) ) {
    z += 0.2f;
  }

  if( (keyStatus( Qt::Key_D ) == ON || keyStatus( Qt::Key_Right ) == ON) ) {
    yspeed += 0.01f;
  }

  if( (keyStatus( Qt::Key_A ) == ON || keyStatus( Qt::Key_Left ) == ON) ) {
    yspeed -= 0.01f;
  }

  if( (keyStatus( Qt::Key_S ) == ON || keyStatus( Qt::Key_Down ) == ON) ) {
    xspeed += 0.01f;
  }

  if( (keyStatus( Qt::Key_W ) == ON || keyStatus( Qt::Key_Up ) == ON) ) {
    xspeed -= 0.01f;
  }

  xrot += xspeed;
  yrot += yspeed;

  updateGL();
}

void Lesson23::keyStatusChanged()
{
  if( keyStatus( Qt::Key_L ) == ON ) {
    light = !light;
    light ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
  }

  if( keyStatus( Qt::Key_F ) == ON ) {
    filter = (filter+1) % 3;
  }

  if( keyStatus( Qt::Key_Space ) == ON ) {
    object = (object+1) % 4;
  }
}

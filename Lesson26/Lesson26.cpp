#include "Lesson26.hpp"

// Light Parameters
static GLfloat LightAmb[] = { 0.7f, 0.7f, 0.7f, 1.0f };       // Ambient Light
static GLfloat LightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f };       // Diffuse Light
static GLfloat LightPos[] = { 4.0f, 4.0f, 6.0f, 1.0f };       // Light Position

GLUquadricObj* q;										                          // Quadratic For Drawing A Sphere

GLfloat xrot = 0.0f;                                          // X Rotation
GLfloat yrot = 0.0f;                                          // Y Rotation
GLfloat xrotspeed = 0.0f;                                     // X Rotation Speed
GLfloat yrotspeed = 0.0f;                                     // Y Rotation Speed
GLfloat zoom = -7.0f;                                         // Depth Into The Screen
GLfloat fHeight = 2.0f;                                        // fHeight Of Ball From Floor

class Lesson26::Lesson26Private
{
public:

  Lesson26Private( Lesson26* me ) : m_self( me ) {
  }

  ~Lesson26Private() {
    for( int idx = 0; idx < 3; ++idx ) {
      m_self->deleteTexture( m_texture[idx] );
    }
  }

  void drawObject() {
    glColor3f( 1.0f, 1.0f, 1.0f );                            // Set Color To White
    glBindTexture( GL_TEXTURE_2D, m_texture[1] );             // Select Texture 2 (1)
    gluSphere( q, 0.35f, 32, 16 );                            // Draw First Sphere

    glBindTexture( GL_TEXTURE_2D, m_texture[2] );             // Select Texture 3 (2)
    glColor4f( 1.0f, 1.0f, 1.0f, 0.4f );                      // Set Color To White With 40% Alpha
    glEnable( GL_BLEND );                                     // Enable Blending
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );                      // Set Blending Mode To Mix Based On SRC Alpha
    glEnable( GL_TEXTURE_GEN_S );                             // Enable Sphere Mapping
    glEnable( GL_TEXTURE_GEN_T );                             // Enable Sphere Mapping

    gluSphere( q, 0.35f, 32, 16 );                            // Draw Another Sphere Using New Texture

    // Textures Will Mix Creating A MultiTexture Effect (Reflection)
    glDisable( GL_TEXTURE_GEN_S );                            // Disable Sphere Mapping
    glDisable( GL_TEXTURE_GEN_T );                            // Disable Sphere Mapping
    glDisable( GL_BLEND );                                    // Disable Blending
  }

  void drawFloor() {
    glBindTexture( GL_TEXTURE_2D, m_texture[0] );             // Select Texture 1 (0)
    glBegin( GL_QUADS );                                      // Begin Drawing A Quad
    {
      glNormal3f( 0.0, 1.0, 0.0 );                            // Normal Pointing Up
      glTexCoord2f( 0.0f, 1.0f );                             // Bottom Left Of Texture
      glVertex3f(-2.0, 0.0, 2.0 );                            // Bottom Left Corner Of Floor

      glTexCoord2f( 0.0f, 0.0f );                             // Top Left Of Texture
      glVertex3f(-2.0, 0.0,-2.0 );                            // Top Left Corner Of Floor

      glTexCoord2f( 1.0f, 0.0f );                             // Top Right Of Texture
      glVertex3f( 2.0, 0.0,-2.0 );                            // Top Right Corner Of Floor

      glTexCoord2f( 1.0f, 1.0f );                             // Bottom Right Of Texture
      glVertex3f( 2.0, 0.0, 2.0 );                            // Bottom Right Corner Of Floor
    }
    glEnd();                                                  // Done Drawing The Quad
  }

  Lesson26*         m_self;
  GLuint            m_texture[3];
};

Lesson26::Lesson26( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson26Private( this ) )
{
  setWindowTitle( "Lesson26" );
}

Lesson26::~Lesson26()
{
}

void Lesson26::initializeGL()
{
  glShadeModel( GL_SMOOTH );                                  // Enable Smooth Shading
  glClearColor( 0.2f, 0.5f, 1.0f, 1.0f );                     // Background
  glClearDepth( 1.0f );                                       // Depth Buffer Setup
  glClearStencil( 0 );                                        // Clear The Stencil Buffer To 0
  glEnable( GL_DEPTH_TEST );                                  // Enables Depth Testing
  glDepthFunc( GL_LEQUAL );                                   // The Type Of Depth Testing To Do
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );        // Really Nice Perspective Calculations
  glEnable( GL_TEXTURE_2D );                                  // Enable 2D Texture Mapping

  glLightfv( GL_LIGHT0, GL_AMBIENT, LightAmb );               // Set The Ambient Lighting For Light0
  glLightfv( GL_LIGHT0, GL_DIFFUSE, LightDif );               // Set The Diffuse Lighting For Light0
  glLightfv( GL_LIGHT0, GL_POSITION, LightPos);               // Set The Position For Light0

  glEnable( GL_LIGHT0 );                                      // Enable Light 0
  glEnable( GL_LIGHTING );                                    // Enable Lighting

  q = gluNewQuadric();                                        // Create A New Quadratic
  gluQuadricNormals( q, GL_SMOOTH );                          // Generate Smooth Normals For The Quad
  gluQuadricTexture( q, GL_TRUE );                            // Enable Texture Coords For The Quad

  _pd->m_texture[0] = bindTexture( QPixmap( ":/Resources/Envwall.PNG" ), GL_TEXTURE_2D );
  _pd->m_texture[1] = bindTexture( QPixmap( ":/Resources/Ball.PNG" ), GL_TEXTURE_2D );
  _pd->m_texture[2] = bindTexture( QPixmap( ":/Resources/Envroll.PNG" ), GL_TEXTURE_2D );

  glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );      // Set Up Sphere Mapping
  glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );      // Set Up Sphere Mapping
}

void Lesson26::paintGL()
{
  // Clear Screen, Depth Buffer & Stencil Buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

  // Clip Plane Equations
  double eqr[] = { 0.0f,-1.0f, 0.0f, 0.0f };                  // Plane Equation To Use For The Reflected Objects
  glLoadIdentity();                                           // Reset The Modelview Matrix

  glTranslatef( 0.0f,-0.6f, zoom );                           // Zoom And Raise Camera Above The Floor (Up 0.6 Units)
  glColorMask( 0, 0, 0, 0 );                                  // Set Color Mask

  glEnable( GL_STENCIL_TEST );                                // Enable Stencil Buffer For "marking" The Floor
  glStencilFunc( GL_ALWAYS, 1, 1 );	                          // Always Passes, 1 Bit Plane, 1 As Mask
  glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );                // We Set The Stencil Buffer To 1 Where We Draw Any Polygon

  // Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
  // Replace If Test Passes
  glDisable( GL_DEPTH_TEST );                                 // Disable Depth Testing
  _pd->drawFloor();                                           // Draw The Floor (Draws To The Stencil Buffer)

  // We Only Want To Mark It In The Stencil Buffer
  glEnable( GL_DEPTH_TEST );                                  // Enable Depth Testing
  glColorMask( 1, 1, 1, 1 );                                  // Set Color Mask to TRUE, TRUE, TRUE, TRUE
  glStencilFunc( GL_EQUAL, 1, 1 );                            // We Draw Only Where The Stencil Is 1

  // (I.E. Where The Floor Was Drawn)
  glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );                   // Don't Change The Stencil Buffer
  glEnable( GL_CLIP_PLANE0 );                                 // Enable Clip Plane For Removing Artifacts

  // (When The Object Crosses The Floor)
  glClipPlane( GL_CLIP_PLANE0, eqr );                         // Equation For Reflected Objects
  glPushMatrix();                                             // Push The Matrix Onto The Stack
  glScalef( 1.0f, -1.0f, 1.0f );                              // Mirror Y Axis
  glLightfv( GL_LIGHT0, GL_POSITION, LightPos );              // Set Up Light0
  glTranslatef( 0.0f, fHeight, 0.0f );                        // Position The Object
  glRotatef( xrot, 1, 0, 0 );                                 // Rotate Local Coordinate System On X Axis
  glRotatef( yrot, 0, 1, 0 );                                 // Rotate Local Coordinate System On Y Axis

  _pd->drawObject();                                          // Draw The Sphere (Reflection)

  glPopMatrix();                                              // Pop The Matrix Off The Stack

  glDisable( GL_CLIP_PLANE0 );                                // Disable Clip Plane For Drawing The Floor
  glDisable( GL_STENCIL_TEST );                               // We Don't Need The Stencil Buffer Any More (Disable)

  glLightfv( GL_LIGHT0, GL_POSITION, LightPos );              // Set Up Light0 Position
  glEnable( GL_BLEND );                                       // Enable Blending (Otherwise The Reflected Object Wont Show)
  glDisable( GL_LIGHTING );                                   // Since We Use Blending, We Disable Lighting
  glColor4f( 1.0f, 1.0f, 1.0f, 0.8f );                        // Set Color To White With 80% Alpha
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );        // Blending Based On Source Alpha And 1 Minus Dest Alpha

  _pd->drawFloor();                                           // Draw The Floor To The Screen

  glEnable( GL_LIGHTING );                                    // Enable Lighting
  glDisable( GL_BLEND );                                      // Disable Blending

  glTranslatef( 0.0f, fHeight, 0.0f );                        // Position The Ball At Proper fHeight
  glRotatef( xrot, 1, 0, 0 );                                 // Rotate On The X Axis
  glRotatef( yrot, 0, 1, 0 );                                 // Rotate On The Y Axis
  _pd->drawObject();                                          // Draw The Ball
}

void Lesson26::idleFunc()
{
  xrot += xrotspeed;                                          // Update X Rotation Angle By xrotspeed
  yrot += yrotspeed;                                          // Update Y Rotation Angle By yrotspeed

  if( keyStatus( Qt::Key_A ) == ON ) {
    zoom += 0.05f;
  }

  if( keyStatus( Qt::Key_Z ) == ON ) {
    zoom -= 0.05f;
  }

  if( keyStatus( Qt::Key_Up ) == ON ) {
    xrotspeed -= 0.08f;
  }

  if( keyStatus( Qt::Key_Down ) == ON ) {
    xrotspeed += 0.08f;
  }

  if( keyStatus( Qt::Key_Left ) == ON ) {
    yrotspeed -= 0.08f;
  }

  if( keyStatus( Qt::Key_Right ) == ON ) {
    yrotspeed += 0.08f;
  }

  if( keyStatus( Qt::Key_PageUp ) == ON ) {
    fHeight += 0.03f;
  }

  if( keyStatus( Qt::Key_PageDown ) == ON ) {
    fHeight -= 0.03f;
  }

  updateGL();
}

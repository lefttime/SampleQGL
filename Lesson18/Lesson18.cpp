#include "Lesson18.hpp"

#include <QPixmap>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QKeyEvent>

int	part1;				        // Start Of Disc
int	part2;				        // End Of Disc
int	p1 = 0;				        // Increase 1
int	p2 = 1;				        // Increase 2

GLuint object = 0;			  // Which Object To Draw (NEW)
GLUquadricObj* quadratic;	// Storage For Our Quadratic Objects

class Lesson18::Lesson18Private
{
public:

  Lesson18Private( Lesson18* me ) : m_self( me ) {
  }

  ~Lesson18Private() {
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

  Lesson18*         m_self;
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

Lesson18::Lesson18( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson18Private( this ) )
{
  setWindowTitle( "Lesson18" );
  _pd->init();
}

Lesson18::~Lesson18()
{
  gluDeleteQuadric( quadratic );
}

void Lesson18::initializeGL()
{
  glEnable( GL_TEXTURE_2D );
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Wall.PNG" ), GL_TEXTURE_2D );

  glEnable( GL_LIGHT1 );
  glLightfv( GL_LIGHT1, GL_AMBIENT,  _pd->m_lAmbient  );
  glLightfv( GL_LIGHT1, GL_DIFFUSE,  _pd->m_lDiffuse  );
  glLightfv( GL_LIGHT1, GL_POSITION, _pd->m_lPosition );

  quadratic = gluNewQuadric();							  // Create A Pointer To The Quadric Object (Return 0 If No Memory)
  gluQuadricNormals( quadratic, GLU_SMOOTH );	// Create Smooth Normals
  gluQuadricTexture( quadratic, GL_TRUE );		// Create Texture Coords
}

void Lesson18::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, _pd->m_zOffset );

  glRotatef( _pd->m_rAngle.x(), 1, 0, 0 );
  glRotatef( _pd->m_rAngle.y(), 0, 1, 0 );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
  
  switch( object ) {
  case 0: _pd->drawCube(); break;

  case 1: {
    glTranslatef( 0.0f, 0.0f, -1.5f );					        // Center The Cylinder
    gluCylinder( quadratic, 1.0f, 1.0f, 3.0f, 32, 32);	// A Cylinder With A Radius Of 0.5 And A Height Of 2
  } break;

  case 2: {
    gluDisk( quadratic, 0.5f, 1.5f, 32, 32 );				    // Draw A Disc (CD Shape) With An Inner Radius Of 0.5, And An Outer Radius Of 2.  Plus A Lot Of Segments ;)
  } break;

  case 3: {
    gluSphere( quadratic, 1.3f, 32, 32 );				        // Draw A Sphere With A Radius Of 1 And 16 Longitude And 16 Latitude Segments
  } break;

  case 4: {
    glTranslatef( 0.0f, 0.0f, -1.5f );					        // Center The Cone
    gluCylinder( quadratic, 1.0f, 0.0f, 3.0f, 32, 32 ); // A Cone With A Bottom Radius Of .5 And A Height Of 2
  } break;

  case 5: {
    part1 += p1;
    part2 += p2;
    if( part1 > 359 ) {									                // 360 Degrees
      p1 = 0;
      p2 = 1;
      part1 = 0;
      part2 = 0;
    }
    if( part2 > 359 )	{								                  // 360 Degrees
      p1 = 1;
      p2 = 0;
    }
    gluPartialDisk( quadratic, 0.5f, 1.5f, 32, 32, part1, part2-part1 );	// A Disk Like The One Before
  } break;
  }
}

void Lesson18::resizeGL( int width, int height )
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson18::idleFunc()
{
  _pd->m_rAngle += _pd->m_rSpeed;
  updateGL();
}

void Lesson18::keyStatusChanged()
{
  if( keyStatus( Qt::Key_F ) == ON ) {
    _pd->changeFilter();
  }

  if( keyStatus( Qt::Key_L ) == ON ) {
    _pd->m_bLight = !_pd->m_bLight;
    _pd->m_bLight ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
  }

  if( keyStatus( Qt::Key_Space ) == ON ) {
    object = (object+1) % 6;
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

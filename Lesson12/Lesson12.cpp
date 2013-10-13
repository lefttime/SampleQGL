#include "Lesson12.hpp"

static GLfloat boxcol[5][3] = {
  {1.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}
};

static GLfloat topcol[5][3] = {
  {0.5f, 0.0f, 0.0f}, {0.5f, 0.25f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}, {0.0f, 0.5f, 0.5f}
};

class Lesson12::Lesson12Private
{
public:

  Lesson12Private( Lesson12* me ) : m_self( me ) {
  }

  ~Lesson12Private() {
    m_self->deleteTexture( m_texture );
  }

  void init() {
    m_rAngle = QVector3D(0, 0, 0);
  }

  void buidLists() {
    m_dlBox = glGenLists( 2 );
    glNewList( m_dlBox, GL_COMPILE );
    {
      glBegin( GL_QUADS );
      {
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  1.0f, -1.0f, -1.0f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  1.0f, -1.0f,  1.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f,  1.0f );

        glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f,  1.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f, -1.0f,  1.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f,  1.0f,  1.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f,  1.0f,  1.0f );

        glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  1.0f,  1.0f, -1.0f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  1.0f, -1.0f, -1.0f );

        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f, -1.0f, -1.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f,  1.0f, -1.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f(  1.0f,  1.0f,  1.0f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f(  1.0f, -1.0f,  1.0f );

        glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f,  1.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f,  1.0f,  1.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
      }
      glEnd();
    }
    glEndList();

    m_dlTop = m_dlBox + 1;

    glNewList( m_dlTop, GL_COMPILE );
    {
      glBegin( GL_QUADS );
      {
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f,  1.0f, -1.0f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f,  1.0f,  1.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f(  1.0f,  1.0f,  1.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f(  1.0f,  1.0f, -1.0f );
      }
      glEnd();
    }
    glEndList();
  }

  Lesson12*           m_self;

  GLuint              m_dlBox;
  GLuint              m_dlTop;
  GLuint              m_texture;

  QVector3D           m_rAngle;

};

Lesson12::Lesson12( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson12Private( this ) )
{
  setWindowTitle( "Lesson12" );
  _pd->init();
}

Lesson12::~Lesson12()
{
}

void Lesson12::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0, 0, 0, 0 );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  glEnable( GL_TEXTURE_2D );
  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Cube.png" ), GL_TEXTURE_2D );

  glEnable( GL_LIGHT0 );
  //glEnable( GL_LIGHTING );
  //glEnable( GL_COLOR_MATERIAL );
  _pd->buidLists();
}

void Lesson12::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );

  for( int idy = 1; idy < 6; ++idy ) {
    for( int idx = 0; idx < idy; ++idx ) {
      glLoadIdentity();
      glTranslatef( 1.4f+(float(idx)*2.8f)-(float(idy)*1.4f), ((6.0f-float(idy))*2.4f)-7.0f, -20.0f );

      glRotatef( 45.0f-(2.0f*idy)+_pd->m_rAngle.x(), 1, 0, 0 );
      glRotatef( 45.0f+_pd->m_rAngle.y(), 0, 1, 0 );

      glColor3fv( boxcol[idy-1] );
      glCallList( _pd->m_dlBox );

      glColor3fv( topcol[idy-1] );
      glCallList( _pd->m_dlTop );
    }
  }
}

void Lesson12::resizeGL(int width, int height)
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson12::keyStatusChanged()
{
  if( keyStatus( Qt::Key_W ) == ON || keyStatus( Qt::Key_Up ) == ON ) {
    _pd->m_rAngle.setX( _pd->m_rAngle.x()-2 );
  }

  if( keyStatus( Qt::Key_S ) == ON || keyStatus( Qt::Key_Down ) == ON ) {
    _pd->m_rAngle.setX( _pd->m_rAngle.x()+2 );
  }

  if( keyStatus( Qt::Key_A ) == ON || keyStatus( Qt::Key_Left ) == ON ) {
    _pd->m_rAngle.setY( _pd->m_rAngle.y()-2 );
  }

  if( keyStatus( Qt::Key_D ) == ON || keyStatus( Qt::Key_Right ) == ON ) {
    _pd->m_rAngle.setY( _pd->m_rAngle.y()+2 );
  }
  updateGL();
}

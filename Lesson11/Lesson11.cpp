#include "Lesson11.hpp"

#include <QVector>
#include <QVector3D>

const int sideLength = 45;

class Lesson11::Lesson11Private
{
public:

  Lesson11Private( Lesson11* me ) : m_self( me ) {
  }

  ~Lesson11Private() {
    m_self->deleteTexture( m_texture );
  }

  void init() {
    m_wiggleCount = 0;
    m_rAngle = QVector3D(0, 0, 0);
    for( int idx = 0; idx < sideLength; ++idx ) {
      for( int idy = 0; idy < sideLength; ++idy ) {
        m_points[idx][idy][0] = idx/5.0f-4.5f;
        m_points[idx][idy][1] = idy/5.0f-4.5f;
        m_points[idx][idy][2] = sin((((idx/5.0f)*40.0f)/360.0f)*3.141592654f*2.0f);
      }
    }
  }

  void drawMesh() {
    float float_x, float_y, float_xb, float_yb;

    glBegin( GL_QUADS );
    {
      for( int idx = 0; idx < sideLength-1; ++idx ) {
        for( int idy = 0; idy < sideLength-1; ++idy ) {
          float_x = float(idx)  / 44.0f;
          float_y = float(idy)  / 44.0f;
          float_xb= float(idx+1)/ 44.0f;
          float_yb= float(idy+1)/ 44.0f;

          glTexCoord2f( float_x, float_y );
          glVertex3f( m_points[idx][idy][0], m_points[idx][idy][1], m_points[idx][idy][2] );

          glTexCoord2f( float_x, float_yb );
          glVertex3f( m_points[idx][idy+1][0], m_points[idx][idy+1][1], m_points[idx][idy+1][2] );

          glTexCoord2f( float_xb, float_yb );
          glVertex3f( m_points[idx+1][idy+1][0], m_points[idx+1][idy+1][1], m_points[idx+1][idy+1][2] );

          glTexCoord2f( float_xb, float_y );
          glVertex3f( m_points[idx+1][idy][0], m_points[idx+1][idy][1], m_points[idx+1][idy][2] );
        }
      }
    }
    glEnd();
  }

  Lesson11*           m_self;

  GLuint              m_texture;
  QVector3D           m_rAngle;

  float               m_points[sideLength][sideLength][3];
  int                 m_wiggleCount;
};

Lesson11::Lesson11( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson11Private( this ) )
{
  setWindowTitle( "Lesson11" );
  _pd->init();
}

Lesson11::~Lesson11()
{
}

void Lesson11::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0, 0, 0, 0 );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  glEnable( GL_TEXTURE_2D );
  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Tim.png" ), GL_TEXTURE_2D );

  glPolygonMode( GL_BACK, GL_FILL );
  glPolygonMode( GL_FRONT, GL_LINE );
}

void Lesson11::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, -12.0f );
  glRotatef( _pd->m_rAngle.x(), 1, 0, 0 );
  glRotatef( _pd->m_rAngle.y(), 0, 1, 0 );
  glRotatef( _pd->m_rAngle.z(), 0, 0, 1 );

  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );
  _pd->drawMesh();
}

void Lesson11::resizeGL(int width, int height)
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
}

void Lesson11::idleFunc()
{
  if( _pd->m_wiggleCount == 2 ) {
    for( int idy = 0; idy < sideLength; ++idy ) {
      float hold = _pd->m_points[0][idy][2];
      for( int idx = 0; idx < sideLength-1; ++idx ) {
        _pd->m_points[idx][idy][2] = _pd->m_points[idx+1][idy][2];
      }
      _pd->m_points[sideLength-1][idy][2] = hold;
    }
    _pd->m_wiggleCount = 0;
  }
  ++_pd->m_wiggleCount;

  _pd->m_rAngle += QVector3D(0.3f, 0.2f, 0.4f);
  updateGL();
}

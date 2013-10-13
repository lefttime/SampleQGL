#include "Lesson10.hpp"

#include <QFile>
#include <QTextStream>

const float piover180 = 0.0174532925f;

typedef struct tagVERTEX        // Build Our Vertex Structure
{
  float x, y, z;                // 3D Coordinates
  float u, v;                   // Texture Coordinates
} VERTEX;                       // Call It VERTEX

typedef struct tagTRIANGLE      // Build Our Triangle Structure
{
  VERTEX vertex[3];             // Array Of Three Vertices
} TRIANGLE;                     // Call It TRIANGLE

typedef struct tagSECTOR				// Build Our Sector Structure
{
  int numtriangles;						  // Number Of Triangles In Sector
  TRIANGLE* triangle;						// Pointer To Array Of Triangles
} SECTOR;								        // Call It SECTOR

class Lesson10::Lesson10Private
{
public:

  Lesson10Private( Lesson10* me ) : m_self( me ) {
  }

  void init() {
    m_rAngle = QVector2D(0, 0);
    m_vPosition = QVector3D(0, 0, 0);

    m_bBlend = false;
    m_zOffset = 0;
    m_fHeading = 0;
    m_fWalkbias = 0;
    m_fLookupdown = 0;
    m_fWalkbiasangle = 0;
    setupWorld();
  }

  void setupWorld() {
    m_sector.numtriangles = 0;

    QFile hFile( ":/Resources/World.txt" );
    if( hFile.open( QFile::ReadOnly ) ) {
      QTextStream in( &hFile );

      extractTriangleCount( in );
      m_sector.triangle = new TRIANGLE[ m_sector.numtriangles ];
      extractTriangles( in );

      hFile.close();
    }
  }

  void extractTriangleCount( QTextStream& in ) {
    QString content;
    while( !in.atEnd() ) {
      content = in.readLine();
      if( content.contains( "NUMPOLLIES" ) ) {
        m_sector.numtriangles = content.trimmed().split( QRegExp( "\\s+" ) ).last().toInt();
        break;
      }
    }
  }

  void extractTriangles( QTextStream& in ) {
    int vIdx = 0;
    int tIdx = 0;
    QString content;
    QStringList coordInfo;
    while( !in.atEnd() ) {
      content = in.readLine();
      coordInfo = content.trimmed().split( QRegExp( "\\s+" ) );
      if( coordInfo.count() != 5 || coordInfo.contains( "//" ) ) {
        continue;
      }

      m_sector.triangle[tIdx].vertex[vIdx].x = coordInfo.at( 0 ).toDouble();
      m_sector.triangle[tIdx].vertex[vIdx].y = coordInfo.at( 1 ).toDouble();
      m_sector.triangle[tIdx].vertex[vIdx].z = coordInfo.at( 2 ).toDouble();
      m_sector.triangle[tIdx].vertex[vIdx].u = coordInfo.at( 3 ).toDouble();
      m_sector.triangle[tIdx].vertex[vIdx].v = coordInfo.at( 4 ).toDouble();
      if( ++vIdx > 2 ) {
        vIdx = 0;
        ++tIdx;
      }
    }
  }

  void drawWorld() {
    GLfloat x_m, y_m, z_m, u_m, v_m;                          // Floating Point For Temp X, Y, Z, U And V Vertices
    int numtriangles = m_sector.numtriangles;                 // Get The Number Of Triangles In Sector 1

    // Process Each Triangle
    for( int loop_m = 0; loop_m < numtriangles; ++loop_m )    // Loop Through All The Triangles
    {
      glBegin( GL_TRIANGLES );                                  // Start Drawing Triangles
      {
        glNormal3f( 0.0f, 0.0f, 1.0f);                        // Normal Pointing Forward
        x_m = m_sector.triangle[loop_m].vertex[0].x;          // X Vertex Of 1st Point
        y_m = m_sector.triangle[loop_m].vertex[0].y;          // Y Vertex Of 1st Point
        z_m = m_sector.triangle[loop_m].vertex[0].z;          // Z Vertex Of 1st Point
        u_m = m_sector.triangle[loop_m].vertex[0].u;          // U Texture Coord Of 1st Point
        v_m = m_sector.triangle[loop_m].vertex[0].v;          // V Texture Coord Of 1st Point
        glTexCoord2f( u_m, v_m ); glVertex3f( x_m, y_m, z_m );// Set The TexCoord And Vertice

        x_m = m_sector.triangle[loop_m].vertex[1].x;          // X Vertex Of 2nd Point
        y_m = m_sector.triangle[loop_m].vertex[1].y;          // Y Vertex Of 2nd Point
        z_m = m_sector.triangle[loop_m].vertex[1].z;          // Z Vertex Of 2nd Point
        u_m = m_sector.triangle[loop_m].vertex[1].u;          // U Texture Coord Of 2nd Point
        v_m = m_sector.triangle[loop_m].vertex[1].v;          // V Texture Coord Of 2nd Point
        glTexCoord2f( u_m, v_m ); glVertex3f( x_m, y_m, z_m );// Set The TexCoord And Vertice

        x_m = m_sector.triangle[loop_m].vertex[2].x;          // X Vertex Of 3rd Point
        y_m = m_sector.triangle[loop_m].vertex[2].y;          // Y Vertex Of 3rd Point
        z_m = m_sector.triangle[loop_m].vertex[2].z;          // Z Vertex Of 3rd Point
        u_m = m_sector.triangle[loop_m].vertex[2].u;          // U Texture Coord Of 3rd Point
        v_m = m_sector.triangle[loop_m].vertex[2].v;          // V Texture Coord Of 3rd Point
        glTexCoord2f( u_m, v_m ); glVertex3f( x_m, y_m, z_m );// Set The TexCoord And Vertice
      }
      glEnd();                                                // Done Drawing Triangles
    }
  }

  Lesson10*         m_self;
  SECTOR            m_sector;

  GLuint            m_texture;

  QVector2D         m_rAngle;
  QVector3D         m_vPosition;

  bool              m_bBlend;
  float             m_zOffset;
  float             m_fHeading;
  float             m_fWalkbias;
  float             m_fLookupdown;
  float             m_fWalkbiasangle;
};

Lesson10::Lesson10( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson10Private( this ) )
{
  setWindowTitle( "Lesson10" );
  _pd->init();
}

Lesson10::~Lesson10()
{
}

void Lesson10::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  glEnable( GL_TEXTURE_2D );
  _pd->m_texture = bindTexture( QPixmap( ":/Resources/Mud.png" ), GL_TEXTURE_2D );
}

void Lesson10::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear Screen And Depth Buffer
  glLoadIdentity();                                       // Reset The Current Matrix
  GLfloat xtrans = -_pd->m_vPosition.x();                 // Used For Player Translation On The X Axis
  GLfloat ztrans = -_pd->m_vPosition.z();                 // Used For Player Translation On The Z Axis
  GLfloat ytrans = -_pd->m_fWalkbias - 0.25f;             // Used For Bouncing Motion Up And Down
  GLfloat sceneroty = 360.0f - _pd->m_rAngle.y();         // 360 Degree Angle For Player Direction

  glRotatef( _pd->m_fLookupdown, 1, 0, 0 );               // Rotate Up And Down To Look Up And Down
  glRotatef( sceneroty, 0, 1, 0 );                        // Rotate Depending On Direction Player Is Facing

  glTranslatef( xtrans, ytrans, ztrans );                 // Translate The Scene Based On Player Position
  glBindTexture( GL_TEXTURE_2D, _pd->m_texture );         // Select A Texture Based On filter
  _pd->drawWorld();
}

void Lesson10::resizeGL( int width, int height )
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

}

void Lesson10::keyStatusChanged()
{
  if( keyStatus( Qt::Key_B ) == ON ) {
    _pd->m_bBlend = !_pd->m_bBlend;
    _pd->m_bBlend ? glEnable( GL_BLEND ) : glDisable( GL_BLEND );
    _pd->m_bBlend ? glDisable( GL_DEPTH_TEST ) : glEnable( GL_DEPTH_TEST );
  }

  if( keyStatus( Qt::Key_W ) == ON || keyStatus( Qt::Key_Up ) == ON ) {
    _pd->m_vPosition.setX( _pd->m_vPosition.x()-(float)sin( _pd->m_fHeading*piover180 )*0.05f );
    _pd->m_vPosition.setZ( _pd->m_vPosition.z()-(float)cos( _pd->m_fHeading*piover180 )*0.05f );
    if( _pd->m_fWalkbiasangle >= 359.0f ) {
      _pd->m_fWalkbiasangle = 0.0f;
    } else {
      _pd->m_fWalkbiasangle += 10;
    }
    _pd->m_fWalkbias = (float)sin( _pd->m_fWalkbiasangle * piover180 )/20.0f;
  }

  if( keyStatus( Qt::Key_S ) == ON || keyStatus( Qt::Key_Down ) == ON ) {
    _pd->m_vPosition.setX( _pd->m_vPosition.x()+(float)sin( _pd->m_fHeading*piover180 )*0.05f );
    _pd->m_vPosition.setZ( _pd->m_vPosition.z()+(float)cos( _pd->m_fHeading*piover180 )*0.05f );
    if( _pd->m_fWalkbiasangle <= 1.0f ) {
      _pd->m_fWalkbiasangle = 359.0f;
    } else {
      _pd->m_fWalkbiasangle -= 10;
    }
    _pd->m_fWalkbias = (float)sin( _pd->m_fWalkbiasangle * piover180 )/20.0f;
  }

  if( keyStatus( Qt::Key_A ) == ON || keyStatus( Qt::Key_Left ) == ON ) {
    _pd->m_fHeading += 1.0f;
    _pd->m_rAngle.setY( _pd->m_fHeading );
  }

  if( keyStatus( Qt::Key_D ) == ON || keyStatus( Qt::Key_Right ) == ON ) {
    _pd->m_fHeading -= 1.0f;
    _pd->m_rAngle.setY( _pd->m_fHeading );
  }

  if( keyStatus( Qt::Key_Q ) == ON || keyStatus( Qt::Key_PageUp ) == ON ) {
    _pd->m_zOffset -= 0.02f;
    _pd->m_fLookupdown -= 1.0f;
  }

  if( keyStatus( Qt::Key_E ) == ON || keyStatus( Qt::Key_PageDown ) == ON ) {
    _pd->m_zOffset += 0.02f;
    _pd->m_fLookupdown += 1.0f;
  }

  updateGL();
}

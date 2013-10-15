#include "Lesson24.hpp"

int fScroll;
int maxtokens;
int swidth;
int sheight;

typedef struct
{
  GLubyte* imageData;
  GLuint   bpp;
  GLuint   width;
  GLuint   height;
  GLuint   texID;
} TextureImage;

TextureImage textures[1];

class Lesson24::Lesson24Private
{
public:

  Lesson24Private( Lesson24* me ) : m_self( me ) {
  }

  ~Lesson24Private() {
    glDeleteLists( m_base, 256 );
  }

  void init() {
    readExtensionInfo();
  }

  void readExtensionInfo() {
    m_extInfo = QString( (char*)glGetString( GL_EXTENSIONS ) ).trimmed().split( " " );
    maxtokens = m_extInfo.count();
  }

  void drawLegend() {
    glColor3f( 1.0f, 0.5f, 0.5f );
    drawText( 50, 16, 1, "Renderer" );
    drawText( 80, 48, 1, "Vendor" );
    drawText( 66, 80, 1, "Version" );

    glColor3f( 1.0f, 0.7f, 0.4f );
    drawText( 200, 16, 1, (char*)glGetString( GL_RENDERER ) );
    drawText( 200, 48, 1, (char*)glGetString( GL_VENDOR ) );
    drawText( 200, 80, 1, (char*)glGetString( GL_VERSION ) );

    glColor3f( 0.5f, 0.5f, 1.0f );
    drawText( 192, 432, 1, "NeHe Productions" );
  }

  void drawFrame() {
    glColor3f( 1.0f, 1.0f, 1.0f );
    glBegin( GL_LINE_STRIP );
    {
      glVertex2d( 639, 417 );
      glVertex2d(   0, 417 );
      glVertex2d(   0, 480 );
      glVertex2d( 639, 480 );
      glVertex2d( 639, 128 );
    }
    glEnd();
    glBegin( GL_LINE_STRIP );
    {
      glVertex2d(   0, 128 );
      glVertex2d( 639, 128 );
      glVertex2d( 639,   1 );
      glVertex2d(   0,   1 );
      glVertex2d(   0, 417 );
    }
    glEnd();
  }

  void drawExtensionInfo() {
    for( int idx = 1; idx <= maxtokens; ++idx ) {
      // Print Current Extension Number
      glColor3f( 0.5f, 1.0f, 0.5f );                            // Set Color To Bright Green
      drawText( 0, 96+(idx*32)-fScroll, 0, QString::number( idx ) );

      // Print The Current Token (Parsed Extension Name)
      glColor3f( 1.0f, 1.0f, 0.5f );                            // Set Color To Yellow
      drawText( 50, 96+(idx*32)-fScroll, 0, m_extInfo.at( idx-1 ) );
    }
  }

  void drawText( GLint xpos, GLint ypos, int set, const QString& content ) {
    glEnable( GL_TEXTURE_2D );
    glLoadIdentity();

    glTranslated( xpos, ypos, 0 );
    glListBase( m_base - 32 + (128*set) );

    glScalef( 1.0f, 2.0f, 1.0f );

    glCallLists( content.count(), GL_UNSIGNED_BYTE, content.toLocal8Bit().constData() );
    glDisable( GL_TEXTURE_2D );
  }

  bool loadTGA( TextureImage* texture ) {
    GLubyte TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    GLubyte TGAcompare[12];
    GLubyte header[6];
    GLuint bytesPerPixel;
    GLuint imageSize;
    GLuint temp;
    GLuint type = GL_RGBA;

    QFile hFile( ":/Resources/Font.tga" );
    if( !hFile.open( QFile::ReadOnly ) ) {
      return false;
    }

    QDataStream in( &hFile );
    if( in.readRawData( (char*)TGAcompare, sizeof( TGAcompare ) ) != sizeof( TGAcompare ) ||
        memcmp( TGAheader, TGAcompare, sizeof(TGAheader) ) != 0 ||
        in.readRawData( (char*)header, sizeof( header ) ) != sizeof( header ) ) {
      hFile.close();
      return false;
    }

    texture->width = header[1] * 256 + header[0];
    texture->height= header[3] * 256 + header[2];
    if( texture->width <= 0 || texture->height <= 0 || (header[4] != 24 && header[4] != 32 ) ) {
      hFile.close();
      return false;
    }

    texture->bpp = header[4];
    bytesPerPixel = texture->bpp / 8;
    imageSize = texture->width * texture->height * bytesPerPixel;
    texture->imageData = (GLubyte*)malloc( imageSize );
    if( texture->imageData == NULL ||
        in.readRawData( (char*)texture->imageData, imageSize ) != imageSize ) {
      if( texture->imageData != NULL ) {
        free( texture->imageData );
      }
      hFile.close();
      return false;
    }

    for( GLuint idx = 0; idx < int(imageSize); idx += bytesPerPixel ) {
      temp = texture->imageData[idx];
      texture->imageData[idx] = texture->imageData[idx+2];
      texture->imageData[idx+2] = temp;
    }
    hFile.close();

    glGenTextures( 1, &texture[0].texID );
    glBindTexture( GL_TEXTURE_2D, texture[0].texID );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    if( texture[0].bpp == 24 ) {
      type = GL_RGB;
    }
    glTexImage2D( GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData );
  }

  void buildFont() {
    m_base = glGenLists( 256 );
    glBindTexture( GL_TEXTURE_2D, textures[0].texID );
    for( int loop1 = 0; loop1 < 256; ++loop1 ) {
      float cx = float(loop1%16) / 16.0f;
      float cy = float(loop1/16) / 16.0f;

      glNewList( m_base+loop1, GL_COMPILE );
      {
        glBegin( GL_QUADS );
        {
          glTexCoord2f( cx, 1.0f-cy-0.0625f );
          glVertex2d( 0, 16 );

          glTexCoord2f( cx+0.0625f, 1.0f-cy-0.0625f );
          glVertex2i( 16, 16 );

          glTexCoord2f( cx+0.0625f, 1.0f-cy-0.001f );
          glVertex2i( 16, 0 );

          glTexCoord2f( cx, 1.0f-cy-0.001f );
          glVertex2i( 0, 0 );
        }
        glEnd();
        glTranslated( 14, 0, 0 );
      }
      glEndList();
    }
  }

  Lesson24*         m_self;
  GLuint            m_base;
  QStringList       m_extInfo;
};

Lesson24::Lesson24( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson24Private( this ) )
{
  setWindowTitle( "Lesson24" );
  _pd->init();
}

Lesson24::~Lesson24()
{
}

void Lesson24::initializeGL()
{
  if( !_pd->loadTGA( &textures[0] ) ) {
    return;
  }

  _pd->buildFont();

  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

  glClearDepth( 1.0f );
  glBindTexture( GL_TEXTURE_2D, textures[0].texID );
}

void Lesson24::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  _pd->drawLegend();

  glLoadIdentity();

  _pd->drawFrame();

  glScissor( 1, int(0.135416f*sheight), swidth-2, int(0.597916f*sheight) );
  glEnable( GL_SCISSOR_TEST );

  _pd->drawExtensionInfo();

  glDisable( GL_SCISSOR_TEST );                               // Disable Scissor Testing
}

void Lesson24::resizeGL( int width, int height )
{
  swidth = width;                                             // Set Scissor Width To Window Width
  sheight= height;                                            // Set Scissor Height To Window Height

  glViewport( 0, 0, width, height );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho( 0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void Lesson24::idleFunc()
{
  // If So, Decrease 'fScroll' Moving Screen Down
  if( (keyStatus( Qt::Key_W ) == ON || keyStatus( Qt::Key_Up ) == ON) && (fScroll > 0 ) ) {
    fScroll -= 2;
  }

  // If So, Increase 'fScroll' Moving Screen Up
  if( (keyStatus( Qt::Key_S ) == ON || keyStatus( Qt::Key_Down ) == ON) && (fScroll < 32*(maxtokens-9)) ) {
    fScroll += 2;
  }

  updateGL();
}

void Lesson24::keyStatusChanged()
{
  if( keyStatus( Qt::Key_Home ) == ON ) {
    fScroll = 0;
  }

  if( keyStatus( Qt::Key_End ) == ON ) {
    fScroll = 32 * (maxtokens-9);
  }
}

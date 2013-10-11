#include "GLWidget.hpp"

#include <QTimer>

class GLWidget::GLWidgetPrivate
{
public:

  GLWidgetPrivate( GLWidget* me ) : m_self( me ) {
  }

  void init() {
    QObject::connect( &m_timer, SIGNAL( timeout() ), m_self, SLOT( idleFunc() ) );
    m_timer.start();
  }

  GLWidget*         m_self;
  QTimer            m_timer;
};

GLWidget::GLWidget( QWidget* parent )
  : QGLWidget( QGLFormat( QGL::SampleBuffers ), parent ), _pd( new GLWidgetPrivate( this ) )
{
  setCursor( Qt::OpenHandCursor );
  _pd->init();
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
  return QSize( 50, 50 );
}

QSize GLWidget::sizeHint() const
{
  return QSize( 640, 480 );
}

void GLWidget::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

  glClearDepth( 1.0f );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );

  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void GLWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
}

void GLWidget::resizeGL( int width, int height )
{
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

}

void GLWidget::keyPressEvent( QKeyEvent* event )
{
  switch( event->key() ) {
  case Qt::Key_F12: {
    isFullScreen() ? setWindowState( Qt::WindowNoState ) : setWindowState( Qt::WindowFullScreen );
  } break;
  }
}

void GLWidget::mousePressEvent( QMouseEvent* event )
{
  setCursor( Qt::ClosedHandCursor );
}

void GLWidget::mouseReleaseEvent( QMouseEvent* event )
{
  setCursor( Qt::OpenHandCursor );
}

void GLWidget::idleFunc()
{
}

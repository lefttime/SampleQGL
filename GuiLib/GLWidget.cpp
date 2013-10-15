#include "GLWidget.hpp"

#include <QMap>
#include <QTimer>
#include <QtDebug>

class GLWidget::GLWidgetPrivate
{
public:

  GLWidgetPrivate( GLWidget* me ) : m_self( me ) {
  }

  void init() {
    m_self->makeCurrent();

    QObject::connect( &m_timer, SIGNAL( timeout() ), m_self, SLOT( idleFunc() ) );
    m_timer.start();
  }

  GLWidget*                   m_self;
  QTimer                      m_timer;
  QMap<int, GLWidget::Status> m_keyStatus;
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

GLWidget::Status GLWidget::keyStatus( Qt::Key key ) const
{
  if( _pd->m_keyStatus.contains( key ) ) {
    return _pd->m_keyStatus[key];
  }
  return GLWidget::OFF;
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

void GLWidget::setTimeInterval( int ms )
{
  _pd->m_timer.setInterval( ms );
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
  if( event->key() == Qt::Key_F12 ) {
    isFullScreen() ? setWindowState( Qt::WindowNoState ) : setWindowState( Qt::WindowFullScreen );
  } else if( event->key() == Qt::Key_Escape ) {
    this->close();
  } else {
    if( !event->isAutoRepeat() && _pd->m_keyStatus[event->key()]==OFF ){
      _pd->m_keyStatus[event->key()] = GLWidget::ON;
      keyStatusChanged();
    }
  }
  QGLWidget::keyPressEvent( event );
}

void GLWidget::keyReleaseEvent( QKeyEvent* event )
{
  if( _pd->m_keyStatus[event->key()]==ON && !event->isAutoRepeat() ){
    _pd->m_keyStatus[event->key()] = GLWidget::OFF;
  }
  QGLWidget::keyReleaseEvent( event );
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

void GLWidget::keyStatusChanged()
{
}

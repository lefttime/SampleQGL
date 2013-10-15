#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include "guilib_global.h"
#include <QtOpenGL>
#include <GL/GLU.h>
#include <QGLWidget>

class GUILIB_EXPORT GLWidget : public QGLWidget
{
  Q_OBJECT;

public:

  enum Status { OFF, ON };

  GLWidget( QWidget* parent=0 );
  virtual ~GLWidget();

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

  Status keyStatus( Qt::Key key ) const;

protected:

  void setTimeInterval( int ms );

  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );

protected slots:

  virtual void idleFunc();
  virtual void keyStatusChanged();

private:
  
  class GLWidgetPrivate;
  QScopedPointer<GLWidgetPrivate>         _pd;
};

#endif // GLWIDGET_HPP
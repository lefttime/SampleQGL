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

  GLWidget( QWidget* parent=0 );
  virtual ~GLWidget();

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

protected:

  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );

protected slots:

  virtual void idleFunc();

private:
  
  class GLWidgetPrivate;
  QScopedPointer<GLWidgetPrivate>         _pd;

};

#endif // GLWIDGET_HPP
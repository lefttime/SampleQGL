#ifndef LESSON10_H
#define LESSON10_H

#include "lesson10_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON10_EXPORT Lesson10 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson10( QWidget* parent=0 );
  ~Lesson10();

protected:

  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );

private:

  class Lesson10Private;
  QScopedPointer<Lesson10Private>         _pd;
};

#endif // LESSON10_H
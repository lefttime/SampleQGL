#ifndef LESSON09_HPP
#define LESSON09_HPP

#include "lesson09_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON09_EXPORT Lesson09 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson09( QWidget* parent=0 );
  ~Lesson09();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyPressEvent( QKeyEvent* event );

private:

  class Lesson09Private;
  QScopedPointer<Lesson09Private>         _pd;
};

#endif // LESSON09_HPP

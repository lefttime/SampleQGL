#ifndef LESSON14_HPP
#define LESSON14_HPP

#include "lesson14_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON14_EXPORT Lesson14 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson14( QWidget* parent=0 );
  ~Lesson14();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

private:

  class Lesson14Private;
  QScopedPointer<Lesson14Private>         _pd;
};

#endif // LESSON14_HPP
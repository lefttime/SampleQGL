#ifndef LESSON22_HPP
#define LESSON22_HPP

#include "lesson22_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON22_EXPORT Lesson22 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson22( QWidget* parent=0 );
  ~Lesson22();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

private:

  class Lesson22Private;
  QScopedPointer<Lesson22Private>         _pd;
};

#endif // LESSON22_HPP
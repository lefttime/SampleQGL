#ifndef LESSON06_HPP
#define LESSON06_HPP

#include "lesson06_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON06_EXPORT Lesson06 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson06( QWidget* parent=0 );
  ~Lesson06();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

private:

  class Lesson06Private;
  QScopedPointer<Lesson06Private>         _pd;
};

#endif // LESSON06_HPP
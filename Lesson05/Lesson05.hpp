#ifndef LESSON05_HPP
#define LESSON05_HPP

#include "lesson05_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON05_EXPORT Lesson05 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson05( QWidget* parent=0 );
  ~Lesson05();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

private:

  class Lesson05Private;
  QScopedPointer<Lesson05Private>         _pd;

};

#endif // LESSON05_HPP
#ifndef LESSON04_HPP
#define LESSON04_HPP

#include "lesson04_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON04_EXPORT Lesson04 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson04( QWidget* parent=0 );
  ~Lesson04();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

private:

  class Lesson04Private;
  QScopedPointer<Lesson04Private>         _pd;

};

#endif // LESSON04_HPP

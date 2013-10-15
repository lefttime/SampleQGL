#ifndef LESSON26_HPP
#define LESSON26_HPP

#include "lesson26_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON26_EXPORT Lesson26 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson26( QWidget* parent=0 );
  ~Lesson26();

protected:

  virtual void paintGL();
  virtual void initializeGL();

  void idleFunc();

private:

  class Lesson26Private;
  QScopedPointer<Lesson26Private>         _pd;
};

#endif // LESSON26_HPP
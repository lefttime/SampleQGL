#ifndef LESSON15_HPP
#define LESSON15_HPP

#include "lesson15_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON15_EXPORT Lesson15 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson15( QWidget* parent=0 );
  ~Lesson15();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

private:

  class Lesson15Private;
  QScopedPointer<Lesson15Private>         _pd;
};

#endif // LESSON15_HPP
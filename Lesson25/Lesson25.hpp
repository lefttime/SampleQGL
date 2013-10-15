#ifndef LESSON25_HPP
#define LESSON25_HPP

#include "lesson25_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON25_EXPORT Lesson25 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson25( QWidget* parent=0 );
  ~Lesson25();

protected:

  virtual void paintGL();
  virtual void initializeGL();

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson25Private;
  QScopedPointer<Lesson25Private>         _pd;
};

#endif // LESSON25_HPP
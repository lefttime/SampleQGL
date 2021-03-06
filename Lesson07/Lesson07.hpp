#ifndef LESSON07_HPP
#define LESSON07_HPP

#include "lesson07_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON07_EXPORT Lesson07 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson07( QWidget* parent=0 );
  ~Lesson07();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson07Private;
  QScopedPointer<Lesson07Private>         _pd;
};

#endif // LESSON07_HPP

#ifndef LESSON20_HPP
#define LESSON20_HPP

#include "lesson20_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON20_EXPORT Lesson20 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson20( QWidget* parent=0 );
  ~Lesson20();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson20Private;
  QScopedPointer<Lesson20Private>         _pd;
};

#endif // LESSON20_HPP
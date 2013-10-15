#ifndef LESSON23_HPP
#define LESSON23_HPP

#include "lesson23_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON23_EXPORT Lesson23 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson23( QWidget* parent=0 );
  ~Lesson23();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson23Private;
  QScopedPointer<Lesson23Private>         _pd;
};

#endif // LESSON23_HPP
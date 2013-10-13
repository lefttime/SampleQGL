#ifndef LESSON08_HPP
#define LESSON08_HPP

#include "lesson08_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON08_EXPORT Lesson08 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson08( QWidget* parent=0 );
  ~Lesson08();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson08Private;
  QScopedPointer<Lesson08Private>         _pd;
};

#endif // LESSON08_HPP

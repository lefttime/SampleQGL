#ifndef LESSON19_HPP
#define LESSON19_HPP

#include "lesson19_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON19_EXPORT Lesson19 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson19( QWidget* parent=0 );
  ~Lesson19();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson19Private;
  QScopedPointer<Lesson19Private>         _pd;
};

#endif // LESSON19_HPP

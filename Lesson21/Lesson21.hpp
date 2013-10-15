#ifndef LESSON21_HPP
#define LESSON21_HPP

#include "lesson21_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON21_EXPORT Lesson21 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson21( QWidget* parent=0 );
  ~Lesson21();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson21Private;
  QScopedPointer<Lesson21Private>         _pd;
};

#endif // LESSON21_HPP
#ifndef LESSON11_HPP
#define LESSON11_HPP

#include "lesson11_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON11_EXPORT Lesson11 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson11( QWidget* parent=0 );
  ~Lesson11();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

private:

  class Lesson11Private;
  QScopedPointer<Lesson11Private>         _pd;
};

#endif // LESSON11_HPP

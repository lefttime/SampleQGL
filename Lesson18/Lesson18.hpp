#ifndef LESSON18_HPP
#define LESSON18_HPP

#include "lesson18_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON18_EXPORT Lesson18 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson18( QWidget* parent=0 );
  ~Lesson18();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson18Private;
  QScopedPointer<Lesson18Private>         _pd;
};

#endif // LESSON18_HPP
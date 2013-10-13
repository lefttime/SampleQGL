#ifndef LESSON16_HPP
#define LESSON16_HPP

#include "lesson16_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON16_EXPORT Lesson16 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson16( QWidget* parent=0 );
  ~Lesson16();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson16Private;
  QScopedPointer<Lesson16Private>         _pd;
};

#endif // LESSON16_HPP
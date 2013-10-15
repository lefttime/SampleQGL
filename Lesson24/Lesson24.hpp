#ifndef LESSON24_HPP
#define LESSON24_HPP

#include "lesson24_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON24_EXPORT Lesson24 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson24( QWidget* parent=0 );
  ~Lesson24();

protected:

  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL( int width, int height );

  void idleFunc();

  virtual void keyStatusChanged();

private:

  class Lesson24Private;
  QScopedPointer<Lesson24Private>         _pd;
};

#endif // LESSON24_HPP
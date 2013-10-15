#ifndef LESSON12_HPP
#define LESSON12_HPP

#include "lesson12_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON12_EXPORT Lesson12 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson12( QWidget* parent=0 );
  ~Lesson12();

protected:

  void initializeGL();
  void paintGL();

  virtual void keyStatusChanged();

private:

  class Lesson12Private;
  QScopedPointer<Lesson12Private>         _pd;
};

#endif // LESSON12_HPP
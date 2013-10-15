#ifndef LESSON01_HPP
#define LESSON01_HPP

#include "lesson01_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON01_EXPORT Lesson01 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson01( QWidget* parent=0 );
  ~Lesson01();

protected:

  virtual void paintGL();
  virtual void initializeGL();
};

#endif // LESSON01_HPP
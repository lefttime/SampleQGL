#ifndef LESSON02_HPP
#define LESSON02_HPP

#include "lesson02_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON02_EXPORT Lesson02 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson02( QWidget* parent=0 );
  ~Lesson02();

protected:

  void initializeGL();
  void paintGL();
};

#endif // Lesson02_HPP
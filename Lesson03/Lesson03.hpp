#ifndef LESSON03_HPP
#define LESSON03_HPP

#include "lesson03_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON03_EXPORT Lesson03 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson03( QWidget* parent=0 );
  ~Lesson03();

protected:

  void initializeGL();
  void paintGL();
};

#endif // LESSON03_HPP
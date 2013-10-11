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
  void resizeGL( int width, int height );
};

#endif // LESSON03_HPP

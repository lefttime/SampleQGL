#include <QApplication>
#include <time.h>

#include "Lesson01/Lesson01.hpp"
#include "Lesson02/Lesson02.hpp"
#include "Lesson03/Lesson03.hpp"
#include "Lesson04/Lesson04.hpp"
#include "Lesson05/Lesson05.hpp"
#include "Lesson06/Lesson06.hpp"
#include "Lesson07/Lesson07.hpp"
#include "Lesson08/Lesson08.hpp"
#include "Lesson09/Lesson09.hpp"
#include "Lesson10/Lesson10.hpp"
#include "Lesson11/Lesson11.hpp"
#include "Lesson12/Lesson12.hpp"

int main( int argc, char* argv[] )
{
  qsrand( (unsigned)time( 0 ) );
  QApplication app( argc, argv );
  
  Lesson12 sample;
  sample.show();

  return app.exec();
}

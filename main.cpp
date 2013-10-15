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
#include "Lesson13/Lesson13.hpp"
#include "Lesson14/Lesson14.hpp"
#include "Lesson15/Lesson15.hpp"
#include "Lesson16/Lesson16.hpp"
#include "Lesson17/Lesson17.hpp"
#include "Lesson18/Lesson18.hpp"
#include "Lesson19/Lesson19.hpp"
#include "Lesson20/Lesson20.hpp"
#include "Lesson21/Lesson21.hpp"
#include "Lesson22/Lesson22.hpp"
#include "Lesson23/Lesson23.hpp"
#include "Lesson24/Lesson24.hpp"
#include "Lesson25/Lesson25.hpp"
#include "Lesson26/Lesson26.hpp"

int main( int argc, char* argv[] )
{
  qsrand( (unsigned)time( 0 ) );
  QApplication app( argc, argv );
  
  Lesson26 sample;
  sample.show();

  return app.exec();
}

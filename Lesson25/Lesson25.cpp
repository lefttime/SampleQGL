#include "Lesson25.hpp"

GLfloat xrot;
GLfloat yrot;
GLfloat zrot;								                                  // X, Y & Z Rotation

GLfloat xspeed;
GLfloat yspeed;
GLfloat zspeed;                                               // X, Y & Z Spin Speed

GLfloat cx;
GLfloat cy;
GLfloat cz = -15;                                             // X, Y & Z Position

int key  = 1;                                                 // Used To Make Sure Same Morph Key Is Not Pressed
int step = 0;
int steps= 200;                                               // Step Counter And Maximum Number Of Steps
bool morph = FALSE;                                           // Default morph To False (Not Morphing)

typedef struct {                                              // Structure For 3D Points
  float	x, y, z;                                              // X, Y & Z Points
} VERTEX;                                                     // Called VERTEX

typedef struct {                                              // Structure For An Object
  int verts;                                                  // Number Of Vertices For The Object
  VERTEX* points;                                             // One Vertice (Vertex x,y & z)
} OBJECT;                                                     // Called OBJECT

int maxver;                                                   // Will Eventually Hold The Maximum Number Of Vertices
OBJECT morph1;
OBJECT morph2;
OBJECT morph3;
OBJECT morph4;                                                // Our 4 Morphable Objects (morph1,2,3 & 4)
OBJECT helper;
OBJECT* sour;
OBJECT* dest;                                                 // Helper Object, Source Object, Destination Object

class Lesson25::Lesson25Private
{
public:

  Lesson25Private( Lesson25* me ) : m_self( me ) {
  }

  ~Lesson25Private() {
    objfree( &morph1 );                                       // Jump To Code To Release morph1 Allocated Ram
    objfree( &morph2 );                                       // Jump To Code To Release morph2 Allocated Ram
    objfree( &morph3 );                                       // Jump To Code To Release morph3 Allocated Ram
    objfree( &morph4 );                                       // Jump To Code To Release morph4 Allocated Ram
    objfree( &helper );                                       // Jump To Code To Release helper Allocated Ram
  }

  void objallocate( OBJECT* k,int n ) {                       // Allocate Memory For Each Object And Defines points
    k->points = (VERTEX*)malloc( sizeof(VERTEX)*n );          // Sets points Equal To VERTEX * Number Of Vertices
  }                                                           // (3 Points For Each Vertice)

  void objfree( OBJECT* k ) {                                 // Frees The Object (Releasing The Memory)
    free( k->points );                                        // Frees Points
  }

  void readstr( FILE* f, char* string ) {                     // Reads A String From File (f)
    do {
      fgets( string, 255, f );                                // Gets A String Of 255 Chars Max From f (File)
    } while((string[0] == '/') || (string[0] == '\n'));       // Until End Of Line Is Reached
    return;
  }

  void objload( char* name, OBJECT* k ) {                     // Loads Object From File (name)
    int		ver;                                                // Will Hold Vertice Count
    FILE* filein;                                             // Filename To Open
    char	oneline[255];                                       // Holds One Line Of Text (255 Chars Max)

    QFile hFile( name );
    hFile.open( QFile::ReadOnly );
    QTextStream in( &hFile );

    // CTRL Z Symbolizes End Of File In Translated Mode
    ver = in.readLine().split( QRegExp( "\\s+" ) )[1].toInt();
    k->verts = ver;                                           // Sets Objects verts Variable To Equal The Value Of ver
    objallocate( k, ver );                                    // Jumps To Code That Allocates Ram To Hold The Object

    for( int idx = 0; idx < ver; ++idx ) {                    // Loops Through The Vertices
      QStringList coordInfo = in.readLine().trimmed().split( QRegExp( "\\s+" ) );
      k->points[idx].x = coordInfo[0].toDouble();             // Sets Objects (k) points.x Value To rx
      k->points[idx].y = coordInfo[1].toDouble();             // Sets Objects (k) points.y Value To ry
      k->points[idx].z = coordInfo[2].toDouble();             // Sets Objects (k) points.z Value To rz
    }

    if( ver > maxver ) {
      maxver = ver;                                           // If ver Is Greater Than maxver Set maxver Equal To ver
    }
  }                                                           // Keeps Track Of Highest Number Of Vertices Used In Any Of The

  // Objects
  VERTEX calculate( int idx )                                 // Calculates Movement Of Points During Morphing
  {
    VERTEX ver;                                               // Temporary Vertex Called a
    ver.x = (sour->points[idx].x - dest->points[idx].x) / steps; 
    ver.y = (sour->points[idx].y - dest->points[idx].y) / steps; 
    ver.z = (sour->points[idx].z - dest->points[idx].z) / steps; 
    return ver;                                               // Return The Results
  }                                                           // This Makes Points Move At A Speed So They All Get To Their

  Lesson25*         m_self;
};

Lesson25::Lesson25( QWidget* parent ) : GLWidget( parent ), _pd( new Lesson25Private( this ) )
{
  setWindowTitle( "Lesson25" );
}

Lesson25::~Lesson25()
{
}

void Lesson25::initializeGL()
{
  glBlendFunc( GL_SRC_ALPHA, GL_ONE );                        // Set The Blending Function For Translucency
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );                     // This Will Clear The Background Color To Black
  glClearDepth( 1.0f );                                       // Enables Clearing Of The Depth Buffer
  glDepthFunc( GL_LESS );                                     // The Type Of Depth Test To Do
  glEnable( GL_DEPTH_TEST );                                  // Enables Depth Testing
  glShadeModel( GL_SMOOTH );                                  // Enables Smooth Color Shading
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );        // Really Nice Perspective Calculations

  maxver = 0;                                                 // Sets Max Vertices To 0 By Default
  _pd->objload( ":/Resources/Sphere.txt",&morph1 );           // Load The First Object Into morph1 From File sphere.txt
  _pd->objload( ":/Resources/Torus.txt", &morph2 );           // Load The Second Object Into morph2 From File torus.txt
  _pd->objload( ":/Resources/Tube.txt",  &morph3 );           // Load The Third Object Into morph3 From File tube.txt

  _pd->objallocate( &morph4, 486 );                           // Manually Reserver Ram For A 4th 468 Vertice Object (morph4)
  for( int i = 0; i < 486; ++i ) {                            // Loop Through All 468 Vertices
    morph4.points[i].x = ((float)(rand()%14000)/1000) - 7;    // morph4 x Point Becomes A Random Float Value From -7 to 7
    morph4.points[i].y = ((float)(rand()%14000)/1000) - 7;    // morph4 y Point Becomes A Random Float Value From -7 to 7
    morph4.points[i].z = ((float)(rand()%14000)/1000) - 7;    // morph4 z Point Becomes A Random Float Value From -7 to 7
  }

  _pd->objload( ":/Resources/Sphere.txt", &helper );           // Load sphere.txt Object Into Helper (Used As Starting Point)
  sour = dest = &morph1;                                      // Source & Destination Are Set To Equal First Object (morph1)
}

void Lesson25::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );       // Clear The Screen And The Depth Buffer
  glLoadIdentity();                                           // Reset The View
  glTranslatef( cx, cy, cz );                                 // Translate The The Current Position To Start Drawing
  glRotatef( xrot, 1, 0, 0 );                                 // Rotate On The X Axis By xrot
  glRotatef( yrot, 0, 1, 0 );                                 // Rotate On The Y Axis By yrot
  glRotatef( zrot, 0, 0, 1 );                                 // Rotate On The Z Axis By zrot

  xrot += xspeed;
  yrot += yspeed;
  zrot += zspeed;                                             // Increase xrot,yrot & zrot by xspeed, yspeed & zspeed

  GLfloat tx, ty, tz;                                         // Temp X, Y & Z Variables
  VERTEX q;                                                   // Holds Returned Calculated Values For One Vertex

  glBegin( GL_POINTS );                                       // Begin Drawing Points

  // Loop Through All The Verts Of morph1 (All Objects Have
  // The Same Amount Of Verts For Simplicity, Could Use maxver Also)
  for( int idx = 0; idx < morph1.verts; ++idx ) {
    if( morph ) {                                             // If morph Is True Calculate Movement Otherwise Movement=0
      q = _pd->calculate( idx );
    } else {
      q.x = q.y = q.z = 0;
    }

    helper.points[idx].x -= q.x;                              // Subtract q.x Units From helper.points[i].x (Move On X Axis)
    helper.points[idx].y -= q.y;                              // Subtract q.y Units From helper.points[i].y (Move On Y Axis)
    helper.points[idx].z -= q.z;                              // Subtract q.z Units From helper.points[i].z (Move On Z Axis)
    tx = helper.points[idx].x;                                // Make Temp X Variable Equal To Helper's X Variable
    ty = helper.points[idx].y;                                // Make Temp Y Variable Equal To Helper's Y Variable
    tz = helper.points[idx].z;                                // Make Temp Z Variable Equal To Helper's Z Variable

    glColor3f( 0.0f, 1.0f, 1.0f );                            // Set Color To A Bright Shade Of Off Blue
    glVertex3f( tx, ty, tz );                                 // Draw A Point At The Current Temp Values (Vertex)
    glColor3f( 0.0f,0.5f,1.0f );                              // Darken Color A Bit
    tx -= 2 * q.x;
    ty -= 2 * q.y;
    ty -= 2 * q.y;                                            // Calculate Two Positions Ahead
    glVertex3f( tx, ty, tz );                                 // Draw A Second Point At The Newly Calculate Position
    glColor3f( 0.0f, 0.0f, 1.0f );                            // Set Color To A Very Dark Blue
    tx -= 2 * q.x;
    ty -= 2 * q.y;
    ty -= 2 * q.y;                                              // Calculate Two More Positions Ahead
    glVertex3f( tx, ty, tz );                                 // Draw A Third Point At The Second New Position
  }                                                           // This Creates A Ghostly Tail As Points Move
  glEnd();                                                    // Done Drawing Points

  // If We're Morphing And We Haven't Gone Through All 200 Steps Increase Our Step Counter
  // Otherwise Set Morphing To False, Make Source=Destination And Set The Step Counter Back To Zero.
  if( morph && step<=steps ) {
    ++step;
  } else {
    morph= FALSE;
    sour = dest;
    step = 0;
  }
}

void Lesson25::idleFunc()
{
  if( keyStatus( Qt::Key_PageUp ) == ON ) {
    zspeed += 0.1f;                                          // Increase zspeed
  }

  if( keyStatus( Qt::Key_PageDown ) == ON ) {
    zspeed -= 0.1f;                                          // Decrease zspeed
  }

  if( keyStatus( Qt::Key_Up ) == ON ) {
    xspeed -= 0.1f;                                          // Decrease xspeed
  }

  if( keyStatus( Qt::Key_Down ) == ON ) {
    xspeed += 0.1f;                                          // Increase xspeed
  }

  if( keyStatus( Qt::Key_Right ) == ON ) {
    yspeed += 0.1f;                                          // Increase yspeed
  }

  if( keyStatus( Qt::Key_Left ) == ON ) {
    yspeed -= 0.1f;                                          // Decrease yspeed
  }

  if( keyStatus( Qt::Key_Q ) == ON ) {
    cz -= 0.1f;                                              // Move Object Away From Viewer
  }

  if( keyStatus( Qt::Key_Z ) == ON ) {
    cz += 0.1f;                                              // Move Object Towards Viewer
  }

  if( keyStatus( Qt::Key_W ) == ON ) {
    cy += 0.1f;                                              // Move Object Up
  }

  if( keyStatus( Qt::Key_S ) == ON ) {
    cy -= 0.1f;                                              // Move Object Down
  }

  if( keyStatus( Qt::Key_D ) == ON ) {
    cx += 0.1f;                                              // Move Object Right
  }

  if( keyStatus( Qt::Key_A ) == ON ) {
    cx -= 0.1f;                                              // Move Object Left
  }

  updateGL();
}

void Lesson25::keyStatusChanged()
{
  if( keyStatus( Qt::Key_1 ) == ON && (key!=1) && !morph ) {
    key = 1;                                                  // Sets key To 1 (To Prevent Pressing 1 2x In A Row)
    morph = TRUE;                                             // Set morph To True (Starts Morphing Process)
    dest = &morph1;                                           // Destination Object To Morph To Becomes morph1
  }

  if( keyStatus( Qt::Key_2 ) == ON && (key!=2) && !morph ) {
    key = 2;                                                  // Sets key To 2 (To Prevent Pressing 2 2x In A Row)
    morph = TRUE;                                             // Set morph To True (Starts Morphing Process)
    dest = &morph2;                                           // Destination Object To Morph To Becomes morph2
  }

  if( keyStatus( Qt::Key_3 ) == ON && (key!=3) && !morph ) {
    key = 3;                                                  // Sets key To 3 (To Prevent Pressing 3 2x In A Row)
    morph = TRUE;                                             // Set morph To True (Starts Morphing Process)
    dest = &morph3;                                           // Destination Object To Morph To Becomes morph3
  }

  if( keyStatus( Qt::Key_4 ) == ON && (key!=4) && !morph ) {
    key = 4;                                                  // Sets key To 4 (To Prevent Pressing 4 2x In A Row)
    morph = TRUE;                                             // Set morph To True (Starts Morphing Process)
    dest = &morph4;                                           // Destination Object To Morph To Becomes morph4
  }
}
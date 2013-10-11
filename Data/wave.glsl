/* !!GLSL Vertex Shader */

uniform float AnimStep;

void main()
{  
  vec4 tmp = gl_Vertex;

  tmp.y = ( sin(AnimStep + (tmp.x / 5.0) ) + sin(AnimStep + (tmp.z / 4.0) ) ) * 2.5;
 
  // Setting of the output position of the vertex 
  gl_Position = gl_ModelViewProjectionMatrix * tmp;
  
  // Texture coordinates 
  gl_TexCoord[0] = gl_MultiTexCoord0;
}
// ProyectoFinal-CasaSimpson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProyectoFinal-CasaSimpson.h"
// omiTest.cpp : Defines the entry point for the console application.
//

float incX = 0.1;
float incY = 0.1;
float decY = -0.1;
float decX = -0.1;
GLfloat vertex[8][3] = {
  { 0, 0, 0 },
  { 1, 0, 0 },
  { 1, 1, 0 },
  { 0, 1, 0 },
  { 0, 0, 1 },
  { 1, 0, 1 },
  { 1, 1, 1 },
  { 0, 1, 1 }
};
GLfloat normal[6][3] = {
  { 0, 0, -1 },
  { -1, 0, 0 },
  { 0, 0, 1 },
  { 1, 0, 0 },
  { 0, -1, 0 },
  { 0, 1, 0 },
};
GLint face[6][4] = {
  { 3, 2, 1, 0 },
  { 7, 3, 0, 4 },
  { 4, 5, 6, 7 },
  { 1, 2, 6, 5 },
  { 0, 1, 5, 4 },
  { 2, 3, 7, 6 },
};
GLfloat l0ambI = 0.4;
GLfloat l0diffI = 0.4;
GLfloat l0specI = 0.4;
GLfloat l1diffI = 0.2;
GLfloat l1specI = 0.2;
GLfloat l2diffI = 0.4;
GLfloat l2specI = 0.2;
GLfloat l3diffI = 0.4;
GLfloat l3specI = 0.2;
GLfloat position0[] = { 0.0, 0.0, 2.0, 1.0 };
GLfloat position1[] = { 0.0, -5.0, 0.0, 1.0 };
GLfloat angle[1] = { 10 };
GLfloat exponent[1] = { 50.0 };
GLfloat dir[3] = { 0.0, -10, 0.0 };

ObjModel obj("pruebas/prueba_lowpoly2_shrunk.obj");
void init(void) {
  // white light
  // Set light position: at location or at infinity
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  // User defines intensities
  // TODO varible controlled intensities
  GLfloat amb0[] = { l0ambI, l0ambI, l0ambI, 1 };
  GLfloat diff0[] = { l0diffI, l0diffI, l0diffI, 1 };
  GLfloat spec0[] = { l0specI, l0specI, l0specI, 1 };
  // Attach to appropriate light
  // glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);

  glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

  // red light
  // Set light position: at location or at infinity
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  // User defines intensities
  GLfloat ambNeutr[] = { l1diffI, l1diffI, l1diffI, 1 };
  // TODO varible controlled intensities
  GLfloat diff1[] = { l1diffI, l1diffI, l1diffI, 1 };
  GLfloat spec1[] = { l1specI, l1specI, l1specI, 1 };
  GLfloat aten[] = { 0.005f };
  // Attach to appropriate light
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
  glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, aten);
  glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, aten);

  // green light
  GLfloat position2[] = { 0.0, -3.0, 3.0, 0.0 };
  // Set light position: at location or at infinity
  glLightfv(GL_LIGHT2, GL_POSITION, position2);
  // User defines intensities
  // TODO varible controlled intensities
  GLfloat diff2[] = { 0, l2diffI, 0, 1 };
  GLfloat spec2[] = { 0, l2specI, 0, 1 };
  // Attach to appropriate light

  glLightfv(GL_LIGHT2, GL_AMBIENT, ambNeutr);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, diff2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, spec2);

  // blue light
  GLfloat position3[] = { 3.0, 0.0, 3.0, 0.0 };
  // Set light position: at location or at infinity
  glLightfv(GL_LIGHT3, GL_POSITION, position3);
  // User defines intensities
  // TODO varible controlled intensities
  GLfloat diff3[] = { 0, 0, l3diffI, 1 };
  GLfloat spec3[] = { 0, 0, l2specI, 1 };
  // Attach to appropriate light

  glLightfv(GL_LIGHT3, GL_AMBIENT, ambNeutr);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, diff3);
  glLightfv(GL_LIGHT3, GL_SPECULAR, spec3);

  ////Set light properties...
  // GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
  ////and create two lights at two positions
  // GLfloat light_pos0[] = { 1.0, 1.0, 1.0, 0.0 };
  // GLfloat light_pos1[] = { -1.0, -1.0, 1.0, 0.0 };

  // Set clear (background) color
  glClearColor(0.2, 0.2, 0.2, 0.0);

  ////Finish setting up the two lights (position,
  //// and component values (specular and diffuse))
  // glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  // glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

  // glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
  // glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
  // glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
  GLfloat fogColor[] = { 0.2f, 0.2f, 0.2f };
  // Enable lighting
  glEnable(GL_LIGHTING);
  // Activate (enable) individual lights
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  /*glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);*/
  // Set shading model to use
  glShadeModel(GL_SMOOTH);
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_LINEAR);   // GL_EXP, GL_EXP2, GL_LINEAR
  glFogfv(GL_FOG_COLOR, fogColor);  // RGBA color
  glFogf(GL_FOG_DENSITY, 0);        // 0.0 to 1.0
  glFogf(GL_FOG_START, 15);
  glFogf(GL_FOG_END, 50.0);
  // calculate by pixel (GL_NICEST) or by vertex (GL_FASTEST)
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  // Enable depth testing (for hidden surface removal)
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
}
float prodPunto(float vectorA[3], float vectorB[3]) {
  return vectorA[0] * vectorB[0] + vectorA[1] * vectorB[1] +
    vectorA[2] * vectorB[2];
}
GLfloat magnitude(GLfloat* v1) {
  return sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
}
float* normalize(float vectorA[3]) {
  float mag = magnitude(vectorA);
  vectorA[0] /= mag;
  vectorA[1] /= mag;
  vectorA[2] /= mag;
  return vectorA;
}
// calculate the cross product of two vectors
float* prodCruz(float vectorA[3], float vectorB[3]) {
  float normal[3] = { vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1],
    vectorA[2] * vectorB[0] - vectorA[0] * vectorB[2],
    vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0] };
  return normal;
}
// check if a point is part of a plane
void Normal(float v1[3], float v2[3], float v3[3], float(&t)[3]) {
  float vA[3] = { v1[0] - v2[0],v1[1] - v2[1] ,v1[2] - v2[2] };
  float vB[3] = { v3[0] - v2[0],v3[1] - v2[1] ,v3[2] - v2[2] };

  //printf(" vA %f %f %f \n", vA[0], vA[1], vA[2]);
  //printf(" vB %f %f %f \n", vB[0], vB[1], vB[2]);
  //dont know why tjis one doesnt need the same reference treatment?
  //my guess is that since normal doesnt initialize the array from prodCruz it gets cleaned when going up the heap ?
  float* pc = prodCruz(vA, vB);
  t[0] = pc[0];
  t[1] = pc[1];
  t[2] = pc[2];
}


void cuboDeLista() {
  for (size_t i = 0; i < sizeof(face) / sizeof(face[0]); i++) {
    glBegin(GL_QUADS);
    for (size_t j = 0; j < 4; j++) {
      glVertex3fv(vertex[face[i][j]]);
      glNormal3fv(normal[i]);
    }
    glEnd();
  }
}

bool aut, spheric;
void cuboNormAut(bool spheric) {
  for (size_t i = 0; i < sizeof(face) / sizeof(face[0]); i++) {
    glBegin(GL_QUADS);
    for (size_t j = 0; j < 4; j++) {
      glVertex3fv(vertex[face[i][j]]);
      if (spheric) {
        float pm[3] = {
          vertex[face[i][j]][0] + 0.5f*(vertex[face[i][(j + 1) % 4]][0] - vertex[face[i][j]][0]),
          vertex[face[i][j]][1] + 0.5f*(vertex[face[i][(j + 1) % 4]][1] - vertex[face[i][j]][1]),
          vertex[face[i][j]][2] + 0.5f*(vertex[face[i][(j + 1) % 4]][2] - vertex[face[i][j]][2])
        };
        float vm[3] = {
          pm[0] - 0.5,
          pm[1] - 0.5,
          pm[2] - 0.5,
        };


        glNormal3fv(normalize(vm));


      }
      else {
        float t[3] = { 0.0,0.0,0.0 };
        Normal(vertex[face[i][1]], vertex[face[i][0]], vertex[face[i][2]], t);
        glNormal3fv(normalize(t));
      }
    }
    glEnd();
  }
}


void emerald() {
  // Define material properties
  GLfloat mat_spec[] = { 0.63, 0.727811, 0.633, 1 };
  GLfloat mat_shiny[] = { 0.6 * 128 };
  GLfloat mat_surf[] = { 0.0215, 0.1745, 0.0215, 1.0 };
  GLfloat mat_def[] = { 0.07568, 0.61424, 0.07568, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void jade() {
  // Define material properties
  GLfloat mat_spec[] = { 0.316228, 0.316228, 0.316228, 1 };
  GLfloat mat_shiny[] = { 0.1 * 128 };
  GLfloat mat_surf[] = { 0.135, 0.2225, 0.1575, 1.0 };
  GLfloat mat_def[] = { 0.54, 0.89, 0.63, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void obsidian() {
  // Define material properties
  GLfloat mat_spec[] = { 0.332741, 0.328634, 0.346435, 1 };
  GLfloat mat_shiny[] = { 0.3 * 128 };
  GLfloat mat_surf[] = { 0.05375, 0.05, 0.06625, 1.0 };
  GLfloat mat_def[] = { 0.18275, 0.17, 0.22525, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void brass() {
  // Define material properties
  GLfloat mat_spec[] = { 0.992157, 0.941176, 0.807843, 1 };
  GLfloat mat_shiny[] = { 0.21794872 * 128 };
  GLfloat mat_surf[] = { 0.329412, 0.223529, 0.027451, 1.0 };
  GLfloat mat_def[] = { 0.780392, 0.568627, 0.113725, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void bronze() {
  // Define material properties
  GLfloat mat_spec[] = { 0.393548, 0.271906, 0.166721, 1 };
  GLfloat mat_shiny[] = { 0.2 * 128 };
  GLfloat mat_surf[] = { 0.2125, 0.1275, 0.054, 1.0 };
  GLfloat mat_def[] = { 0.714, 0.4284, 0.18144, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void chrome() {
  // Define material properties
  GLfloat mat_spec[] = { 0.774597, 0.774597, 0.774597, 1 };
  GLfloat mat_shiny[] = { 0.6 * 128 };
  GLfloat mat_surf[] = { 0.25, 0.25, 0.25, 1.0 };
  GLfloat mat_def[] = { 0.4, 0.4, 0.4, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void copper() {
  // Define material properties
  GLfloat mat_spec[] = { 0.256777, 0.137622, 0.086014, 1 };
  GLfloat mat_shiny[] = { 0.1 * 128 };
  GLfloat mat_surf[] = { 0.19125, 0.0735, 0.0225, 1.0 };
  GLfloat mat_def[] = { 0.7038, 0.27048, 0.0828, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void gold() {
  // Define material properties
  GLfloat mat_spec[] = { 0.628281, 0.555802, 0.366065, 1 };
  GLfloat mat_shiny[] = { 0.4 * 128 };
  GLfloat mat_surf[] = { 0.24725, 0.1995, 0.0745, 1.0 };
  GLfloat mat_def[] = { 0.75164, 0.60648, 0.22648, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void silver() {
  // Define material properties
  GLfloat mat_spec[] = { 0.508273, 0.508273, 0.508273, 1 };
  GLfloat mat_shiny[] = { 0.4 * 128 };
  GLfloat mat_surf[] = { 0.19225, 0.19225, 0.19225, 1.0 };
  GLfloat mat_def[] = { 0.50754, 0.50754, 0.50754, 1.0 };
  // Set material properties, as defined above
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_def);
}
void drawObjects() {
  copper();
  obj.renderObject();
}
double incR = 0;
static bool rotate;
void display(void) {
  // Clear the buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // ROtar
  if (::rotate) {
    incR += 0.1;
  }
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  // glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glPushMatrix();
  glRotated(incR, 0.0, 1.0, 0.0);
  // Get model - from library
  /*glutSolidTeapot(0.80);*/
  drawObjects();
  glPopMatrix();
  glFlush();
}

void reshape(int w, int h) {
  // Set the viewport size, based on function input
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  // Set the projection matrix based on input size
  glMatrixMode(GL_PROJECTION);
  // First set as identity
  glLoadIdentity();
  // Then set perpective projection parameters based
  // on aspect ratio
  gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 0.10, 100.0);

  // Set the model view matrix to identity
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set the "look at" point
  gluLookAt(0.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    // Use "ESC" key to exit
  case'l':
    spheric = true;

    break;
  case 'L':
    spheric = false;

    break;
  case 'p':
    aut = true;
    break;
  case 'P':
    aut = false;
    break;
  case 'k':
    glShadeModel(GL_SMOOTH);
    break;
  case 'K':
    glShadeModel(GL_FLAT);
    break;
    // turn lights on and off'
  case 'f':
    glEnable(GL_FOG);
    break;
  case 'F':
    glDisable(GL_FOG);
    break;
  case 'a':
    // incR = 0;
    ::rotate = !::rotate;
    break;
  case 'q':
    glEnable(GL_LIGHT0);
    break;
  case 'w':
    glEnable(GL_LIGHT1);
    break;
  case 'e':
    glEnable(GL_LIGHT2);
    break;
  case 'r':
    glEnable(GL_LIGHT3);
    break;
  case 'Q':
    glDisable(GL_LIGHT0);
    break;
  case 'W':
    glDisable(GL_LIGHT1);
    break;
  case 'E':
    glDisable(GL_LIGHT2);
    break;
  case 'R':
    glDisable(GL_LIGHT3);
    break;
    // light0 movement
  case 'c':
    position0[0] += incX;
    break;
  case 's':
    position0[1] += incY;
    break;
  case 'x':
    position0[1] += decY;
    break;
  case 'z':
    position0[0] += decX;
    break;
  case 27:
    exit(0);
    break;
  }
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  // window size
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(100, 100);
  // create the window
  glutCreateWindow("More Light test");
  // addit init
  init();
  // Assign  the function used in events
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  // Let start glut loop
  glutMainLoop();
  return 0;
}



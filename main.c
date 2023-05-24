#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dg.h>
#include <stdio.h>
#include "noise.h"

static void init(void);
/* TODO : gérer le retaillage de la fenêtre */
/* static void resize(int width, int height); */
static void draw(void);
static void sortie(void);

static GLuint _wW = 640, _wH = 480;
static GLuint _sphereId = 0;
static GLuint _pId = 0;

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "Ateliers API8 - modélisation", GL4DW_POS_CENTERED, GL4DW_POS_CENTERED,
			 _wW, _wH, GL4DW_OPENGL | GL4DW_RESIZABLE | GL4DW_SHOWN)) {
    fprintf(stderr, "Erreur lors de la création de la fenêtre\n");
    return 1;
  }
  init();
  atexit(sortie);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}

void init(void) {

  initNoiseTextures();
  glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
  _sphereId = gl4dgGenSpheref(10, 10);
  _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/perlin.fs", NULL);
}

void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);
  glUniform1f(glGetUniformLocation(_pId, "weight"), 1.1);
  /* glUniform1f(glGetUniformLocation(_pId, "zoom"), 5.5f); */
  /* glUniform1f(glGetUniformLocation(_pId, "zoom"), 35.5f); */
  glUniform1f(glGetUniformLocation(_pId, "zoom"), 35.5f);
  useNoiseTextures(_pId, 0);
  gl4dgDraw(_sphereId);
  unuseNoiseTextures(0);
  
  glUseProgram(0);
}

void sortie(void) {
  freeNoiseTextures();
  gl4duClean(GL4DU_ALL);
}

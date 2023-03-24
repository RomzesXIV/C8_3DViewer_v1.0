#include "parser.h"

#include <string.h>

#include "model_operations.h"

int Parse(const char* path, Vertex* v, Surface* s) {
  int err = ALL_GOOD;
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    // printf("can't open file\n");
    return ERROR_OPENING_FILE;
  }
  err = VertexInit(v);
  int err1 = SurfaceInit(s);
  if (err == ALL_GOOD && err1 == ALL_GOOD) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;  // ssize_t
    int problem_line_number = 0;
    ssize_t xxx = -1;  // добавил, иначе не работает ниже -1
    while ((read = getline(&line, &len, file)) != xxx && err == ALL_GOOD) {
      if (line[0] == 'v' && line[1] == ' ') {
        // printf("sslol");
        err = GetVertex(line, v);
        err = err == ALL_GOOD ? ALL_GOOD : problem_line_number;
      } else if (line[0] == 'f') {
        err = GetSurface(line, s);
        err = SurfaceResize(s);
      }
      ++problem_line_number;
    }

    free(line);
  }

  fclose(file);
  Normalize(v);
  return err;
}

int GetSurface(char* line, Surface* s) {
  int err = ALL_GOOD;
  Polygon p;
  err = PolygonInit(&p);
  char* ptr = line;
  while (*ptr != '\0' && *ptr != '\n') {
    // ++ptr;
    // printf("%c", *ptr);
    while (*ptr < '0' && *ptr > '9') ++ptr;
    int temp = 0;
    int numb = sscanf(ptr, "%u", &temp);
    if (numb > 0) p.data[++p.pos] = (GLuint)abs(temp - 1);
    PolygonResize(&p);
    ++ptr;
    while (*ptr != ' ' && *ptr != '\0' && *ptr != '\n') ++ptr;
  }
  s->polygons[++s->pos] = p;
  return err;
}

int GetVertex(char* line, Vertex* v) {
  int err = ALL_GOOD;
  double x = 0, y = 0, z = 0;
  int cord_qua = sscanf(line, "v %lf %lf %lf", &x, &y, &z);
  if (cord_qua == 3) {
    v->data[++v->pos] = (GLfloat)x;
    v->data[++v->pos] = (GLfloat)y;
    v->data[++v->pos] = (GLfloat)z;
    MaxCoordSet(v, x, y, z);
    VertexResize(v);
  } else {
    err = 0;
  }
  return err;
}

void MaxCoordSet(Vertex* v, float x, float y, float z) {
  v->max_coord = v->max_coord < fabs(x) ? fabs(x) : v->max_coord;
  v->max_coord = v->max_coord < fabs(y) ? fabs(y) : v->max_coord;
  v->max_coord = v->max_coord < fabs(z) ? fabs(z) : v->max_coord;
}

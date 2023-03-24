#include "model.h"

int VertexInit(Vertex* v) {
  int err = -1;
  v->size = VERTEX_SIZE;
  v->pos = -1;
  v->max_coord = -INFINITY;
  v->data = (GLfloat*)calloc(VERTEX_SIZE, sizeof(GLfloat));
  if (v->data == NULL) err = MEMORY_ERROR;
  return err;
}

int VertexResize(Vertex* v) {
  int err = -1;
  if (v->size - v->pos <= 4) {
    v->data = realloc(v->data, 2 * v->size * sizeof(GLfloat));
    if (v->data != NULL) err = MEMORY_ERROR;
    v->size += v->size;
    // printf("resize, new size %lu\n",v->size);
  }
  return err;
}
int PolygonInit(Polygon* p) {
  int err = -1;
  p->size = POLYGON_SIZE;
  p->pos = -1;
  p->data = calloc(POLYGON_SIZE, sizeof(GLuint));
  if (p->data == NULL) err = MEMORY_ERROR;
  return err;
}

int PolygonResize(Polygon* p) {
  int err = -1;
  if (p->size - p->pos <= 2) {
    //  printf("pol resize old size = %zu ", p->size);
    p->data = realloc(p->data, 2 * p->size * sizeof(GLuint));
    p->size += p->size;
    // printf("new size = %zu\n", p->size);
  }
  if (p->data == NULL) err = MEMORY_ERROR;
  return err;
}

int SurfaceInit(Surface* s) {
  int err = -1;
  s->polygons = calloc(SURFACE_SIZE, sizeof(Polygon));
  s->pos = -1;
  s->size = SURFACE_SIZE;
  return err;
}
int SurfaceResize(Surface* s) {
  int err = -1;
  if (s->size - s->pos <= 5) {
    s->polygons = realloc(s->polygons, 2 * s->size * sizeof(Polygon));
    s->size += s->size;
    // printf("surface resize = %zu\n", s->size);
  }

  if (s->polygons == NULL) err = MEMORY_ERROR;
  return err;
}

// void VertexPrint(Vertex v) {
//   printf("VERTEX:\n");
//   int i = 0;
//   while (i < v.pos && v.pos >= 0) {
//     printf("%f %f %f\n", v.data[i], v.data[i + 1], v.data[i + 2]);
//     i += 3;
//   }
// }

// void SurfacePrint(Surface s) {
//   printf("SURFACE:\n");
//   for (int i = 0; i <= s.pos; ++i) {
//     for (int j = 0; j <= s.polygons[i].pos; ++j) {
//       j == s.polygons[i].pos ? printf("%d\n", s.polygons[i].data[j])
//                              : printf("%d ", s.polygons[i].data[j]);
//     }
//   }
// }

void FreeVertex(Vertex* v) {
  free(v->data);
  v->data = NULL;
}
void FreeSurface(Surface* s) {
  for (int i = 0; i <= s->pos; ++i) free(s->polygons[i].data);
  free(s->polygons);
  s->polygons = NULL;
}

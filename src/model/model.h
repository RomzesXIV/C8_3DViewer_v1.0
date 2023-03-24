#ifndef model_h
#define model_h
#ifdef __cplusplus
extern "C" {
#endif
#define VERTEX_SIZE 33
#define POLYGON_SIZE 6
#define SURFACE_SIZE 50
#define MEMORY_ERROR -2
#define ALL_GOOD -1
#ifdef __linux__
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * \brief Структура для хранения точек
 */
typedef struct {
  GLfloat *data;
  size_t size;
  GLint pos;
  GLfloat max_coord;
} Vertex;
/**
 * \brief Структура для хранения индексов вершин полигона
 */
typedef struct {
  GLuint *data;
  size_t size;
  GLint pos;
} Polygon;
/**
 * \brief Структура для хранения полигонов
 */
typedef struct {
  Polygon *polygons;
  size_t size;
  int pos;
} Surface;
/**
 * Инициализация экземпляра <Surface>
 */
int SurfaceInit(Surface *s);
/**
 * Увеличение размера экземпляра <Surface>
 */
int SurfaceResize(Surface *s);

/**
 * Инициализация экземпляра <Vertex>
 */
int VertexInit(Vertex *v);
/**
 * Увеличение размера экземпляра <Vertex>
 */
int VertexResize(Vertex *v);
/**
 * Инициализация экземпляра <Polygon>
 */
int PolygonInit(Polygon *p);
/**
 * Увеличение размера экземпляра <Polygon>
 */
int PolygonResize(Polygon *p);
// /**
//  * Печать экземпляра <Vertex>
//  */
// void VertexPrint(Vertex v);
// /**
//  * Печать экземпляра <Surface>
//  */
// void SurfacePrint(Surface s);
/**
 * Освобождение памяти занимаемой экземпляром <Vertex>
 */
void FreeVertex(Vertex *v);
/**
 * Освобождение памяти занимаемой экземпляром <Surface>
 */
void FreeSurface(Surface *s);

#ifdef __cplusplus
}
#endif
#endif /* model_h */

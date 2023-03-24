#include "model_operations.h"

void Normalize(Vertex* v) {
  for (int i = 0; i <= v->pos; ++i) v->data[i] /= v->max_coord;
}
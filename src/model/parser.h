#define _GNU_SOURCE  // добавил, иначе гетлайн не принимает
#ifndef parser_h
#define parser_h
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#include "model.h"

#define ERROR_OPENING_FILE -3
/**
 * \brief Сравнение поданых значений \param x, \param y, \param z с значениями
 * \param v и запись максимального значения оси \param v Структура точки
 * используемая для хранения максимального значения осей \param x Ось X \param y
 * Ось Y \param z Ось Z
 */
void MaxCoordSet(Vertex* v, float x, float y, float z);
/**
 * \brief Считывает из строки точку
 * \param line Входная строка
 * \param v Элемент массива для записи точки
 */
int GetVertex(char* line, Vertex* v);
/**
 * \brief Считывавает из строки полигон
 * \param line Входная строка
 * \param s Элемент массива для записи полигона
 */
int GetSurface(char* line, Surface* s);
/**
 * \brief Читает файл и заполняет массив точкек и полигонов
 * \param path Путь к файлу .obj
 * \param v Массив для записи точек
 * \param s Массив для записи полигонов
 */
int Parse(const char* path, Vertex* v, Surface* s);
#endif /* parser_h */

#ifdef __cplusplus
}
#endif

#ifndef MODELDATA_H
#define MODELDATA_H
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLWidget>

#include "../../model/model.h"
/**
 * \brief Класс модели. Содержит в себе информацию по точкам и полигонам. А так
 * же функции преобразования модельно-видовой матрицы
 */
class ModelData {
 public:
  /**
   * Конструктор класса
   * \param Путь к файлу модели
   */
  ModelData(QString path);
  /**
   * Деструктор класса
   */
  ~ModelData();

  QString path_;                ///< Путь к файлу модели
  Vertex v_;                    ///< Массив точек
  Surface s_;                   ///< Массив полигонов
  int err_;                     ///< Флаг ошибки чтения
  GLfloat scale_;               ///< Масштаб
  QMatrix4x4 modelViewMatrix_;  ///< Модельно-видовая матрица
  /**
   * Поворот объекта
   */
  void RotateModel(GLfloat x, GLfloat y, GLfloat z);
  /**
   * Изменение масштаба
   */
  void ScaleModel(GLfloat scale_change);
  /**
   * Изменение масштаба
   */
  void ScaleModelFromForm(GLfloat scale);
  /**
   * Смещение объекта
   */
  void MoveModel(GLfloat x, GLfloat y, GLfloat z);
  /**
   * Получение имени файла из хранимого пути
   */
  QString GetFileName();
};

#endif  // MODELDATA_H

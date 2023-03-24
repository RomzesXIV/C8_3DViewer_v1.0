#ifndef VIEWER_H
#define VIEWER_H
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "model_data.h"
#include "settings_widget.h"
// #include "../../model/model.h"
/**
 * \brief Отрисовка окна внутри главной формы для отображения модели
 */
class Viewer : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  Viewer(QWidget* parent = nullptr);
  ~Viewer();

 private:
  /**
   * Инициализация окна и установка первичных настроек
   */
  void initializeGL() override;
  /**
   * Установка размера области просмотра
   */
  void resizeGL(int w, int h) override;
  /**
   * Отрисовка модели
   */
  void paintGL() override;
  /**
   * Инициализация шейдеров
   */
  void initShaders();
  /**
   * Выделение памяти под модель
   */
  void InitModel();

  /**
   * Обработка нажатия пкм
   */
  void mousePressEvent(QMouseEvent* mo) override;
  /**
   * Обработка перемещения мыши с нажатой пкм
   */
  void mouseMoveEvent(QMouseEvent* mo) override;
  /**
   * Обработка вращения колесика мыши
   */
  void wheelEvent(QWheelEvent* event) override;

 private:
  QMatrix4x4 projection_matrix_;  ///< Матрица проекции перспективы
  QOpenGLShaderProgram* program_;  ///< Шейдерная программа
  QOpenGLBuffer vertex_buffer_;    ///< Буфер точек
  QPoint pos_;  ///< Позиция нажатия пкм в окне отображения модели
  float x_rot_,
      y_rot_;  ///< Смещение модели на координатах окна отображения модели
  QVector4D bckgrnd_color_;  ///< Цвет фона
  QSettings* settings;  ///< Экземпляр настроек отображения моделей

  QVector4D background_color_;  ///< Цвет фона
  QVector4D line_color_;        ///< Цвет линий
  QVector4D vertex_color_;      ///< Цвет точек
  int vertex_type_;             ///< Тип точек
  int line_type_;               ///< Тип линии
  float vertex_size_;           ///< Размер точек
  float line_width_;            ///< Ширина линий
  int projection_type_;         ///< Тип проекции

 public:
  /**
   *Загрузка модели по указанному пути
   */
  int LoadModel(QString path);
  ModelData* md_ = NULL;  ///< Создание экземпляра модели
  SettingsWidget* sw_;  ///< Создание экземпляра окна настроек
  /**
   * Загрузка файла настроек
   */
  void LoadSettings();
};

#endif  // VIEWER_H
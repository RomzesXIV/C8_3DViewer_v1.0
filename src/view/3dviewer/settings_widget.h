#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QDialog>
#include <QSettings>
#include <QVector4D>

namespace Ui {
class SettingsWidget;
}
/**
 * \brief Класс конфигурационого окна
 */
class SettingsWidget : public QDialog {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget *parent = nullptr);
  ~SettingsWidget();

 public:
  Ui::SettingsWidget *ui;  ///< Окно настроек
 private:
  QColor background_color_;  ///< Цвет фона
  QColor line_color_;        ///< Цвет линий
  QColor vertex_color_;      ///< Цвет точек
  QSettings *settings;  ///< Экземпляр для хранения и загрузки настроек
  int line_type_;  ///< Тип линии. Пунктир или сплошная
  int vertex_type_;  ///< Тип точек. Квадратная, круг или отсутсвует
  float line_width_;     ///< Толщина линий
  float vertex_size_;    ///< Размер точек
  int projection_type_;  ///< Тип проекции
  /**
   * Сохранение настроек
   */
  void SaveSettings();
  /**
   * Загрузка настроек
   */
  void LoadSettings();
  /**
   * Получение значения цветов заданных на форме
   */
  void LoadColors();
  /**
   * Считывание данных с формы, определение выбранных параметров
   */
  void LoadCheckboxes();
  // protected:
  //     void closeEvent(QCloseEvent *event);

 public slots:
  /**
   * Считывание данных с формы, слайдеры вбора цветов
   */
  void SlotSliderValueChanged();
  /**
   * Действия по нажатию кнопки применения изменений
   */
  void SlotApplyBtnClicked();
  /**
   * Считывание данных с формы, определение выбранных пунктов
   */
  void SlotCheckBoxChecked();
  /**
   * Действия по нажатию кнопки отмены
   */
  void SlotCancelBtnClicked();
  // signals:
  //     void WidgetClosed();
};

#endif  // SETTINGS_WIDGET_H

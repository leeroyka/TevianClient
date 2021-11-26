#ifndef TEVIANCLIENT_DOMAIN_FACE_HPP
#define TEVIANCLIENT_DOMAIN_FACE_HPP

#include <QString>

namespace Domain {

class Face
{
public:
  /*!
   * \brief Face Конструктор установки параметров прямоугольника лица
   * \param x Координата x
   * \param y Координата y
   * \param height Высота
   * \param width Ширина
   */
  Face(qint32 x, qint32 y, qint32 height, qint32 width);

  /*!
   * \brief setGender Установка пола
   * \param gender пол
   */
  void setGender(QString gender);

  /*!
   * \brief setAge Установка возраста
   * \param mean Средний возраст
   * \param variance погрешность
   */
  void setAge(qreal mean, qreal variance);

  /*!
   * \brief getX Получить координату x
   * \return Координата x
   */
  qint32 getX() const;

  /*!
   * \brief getY Получить координату y
   * \return Координата y
   */
  qint32 getY() const;

  /*!
   * \brief getHeight Получить высоту
   * \return Высота
   */
  qint32 getHeight() const;

  /*!
   * \brief getWidth Получить ширину
   * \return Ширина
   */
  qint32 getWidth() const;

  /*!
   * \brief getGender Получить пол
   * \return Пол
   */
  QString getGender() const;

  /*!
   * \brief getAge Получить возраст
   * \return Возраст. Формат (Среднее+-погрешность)
   */
  QString getAge() const;

private:
  qint32  mX;           ///< Координата x
  qint32  mY;           ///< Координата у
  qint32  mheight;      ///< Высота
  qint32  mWidth;       ///< Ширина
  QString mGender;      ///< Пол
  qreal   mAge;         ///< Возраст средний
  qreal   mVarianceAge; ///< Погрешность возраста
};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_FACE_HPP

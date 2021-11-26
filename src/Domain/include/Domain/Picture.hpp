#ifndef TEVIANCLIENT_DOMAIN_PICTURE_HPP
#define TEVIANCLIENT_DOMAIN_PICTURE_HPP

#include <Domain/Face.hpp>

#include <QVector>

#include <memory>

namespace Domain {

class Picture
{
public:
  /*!
   * \brief Picture конструктор по умолчанию
   */
  Picture();

  /*!
   * \brief getFaces получить вектор лиц
   * \return указатель на вектор содержащий лица
   */
  std::shared_ptr<QVector<Face>> getFaces() const;

  /*!
   * \brief getPictureName Получить название изображения
   * \return Название изображения
   */
  QString getPictureName() const;

  /*!
   * \brief addFace Добавить лицо
   * \param face лицо
   */
  void addFace(const Face& face);

  /*!
   * \brief setErrorString установить сообщение об ошибке
   * \param errorMessage сообщение содержащее ошибку
   */
  void setErrorString(const QString& errorMessage);

  /*!
   * \brief proccessingSuccesful Установка успешной обработки
   */
  void proccessingSuccesful();

  /*!
   * \brief proccessingFailed Установка не удачной обработки
   */
  void proccessingFailed();

  /*!
   * \brief setPictureName Установить название изображения
   * \param name название изображения
   */
  void setPictureName(const QString& name);

private:
  std::shared_ptr<QVector<Face>> mFaces;       ///< указатель на вектор лиц
  QString                        mPictureName; ///< название изображения
  bool                           mIsProcessed; ///< успешная ли обработка
  QString                        mErrorString; ///< сообщение об ошибке
};

} // namespace Domain

#endif// TEVIANCLIENT_DOMAIN_PICTURE_HPP

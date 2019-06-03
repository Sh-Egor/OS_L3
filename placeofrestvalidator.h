#ifndef PLACEOFRESTVALIDATOR_H
#define PLACEOFRESTVALIDATOR_H

#include <QObject>
#include <QValidator>

class PlaceOfRestValidator : public QValidator
{
    Q_OBJECT

public:
    PlaceOfRestValidator(QObject *parent);
    ~PlaceOfRestValidator();

    /*!
    * Функция-валидатор для введенного места отдыха.
    * \param [in] input пользователький ввод
    * \param [in] pos позиция курсора
    * \return код результата проверки строки из QValidator::State
    */
    QValidator::State validate(QString & input, int & pos ) const;

private:
    
};

#endif // PLACEOFRESTVALIDATOR_H

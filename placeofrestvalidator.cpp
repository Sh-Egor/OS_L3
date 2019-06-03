#include "placeofrestvalidator.h"

PlaceOfRestValidator::PlaceOfRestValidator(QObject *parent)
    : QValidator(parent)
{

}

PlaceOfRestValidator::~PlaceOfRestValidator()
{

}

/*!
* Функция-валидатор для введенного места отдыха.
* \param [in] input пользователький ввод
* \param [in] pos позиция курсора
* \return код результата проверки строки из QValidator::State
*/
QValidator::State PlaceOfRestValidator::validate(QString & input, int & pos ) const
{
    //если что-то введено и первый введенный символ не заглавная
    if (input.length() > 0 && !input.at(0).isUpper())
        return QValidator::Intermediate;

    return QValidator::Acceptable;
}
#include "journey.h"

/*!
* Конструктор по умолчанию класса - записи справочника туриста
*/
Journey::Journey()
{
    // инициализация QTextCodec
    QTextCodec* c = QTextCodec::codecForLocale();

    // инициализация полей класса стандартными значениями
    data.kindOfRecreationIndex = 0;
    data.countryIndex = 0;
    data.recreationPlace = c->toUnicode("Катманду");
    data.ticketCost = 3000;
    data.duration = 2;
    data.NeedVisa = false;

    //ID будет заполнен при добавлении в БД
}

/*!
* Конструктор с параметрами класса - записи справочника туриста
* вызывается при инициалиации массива данных записей.
* \param [in] kind вид отдыха (индекс)
* \param [in] country страна отдыха	(индекс)
* \param [in] place место отдыха
* \param [in] cost стоимость отдыха
* \param [in] durat длительность отдыха
* \param [in] visa флаг необходимости визы
*/
Journey::Journey(int kind, int country, QString place, int cost, int durat, bool visa)
{
    //присваиваем полям класса переданные значения
    data.kindOfRecreationIndex = kind;
    data.countryIndex = country;
    data.recreationPlace = place;
    data.ticketCost = cost;
    data.duration = durat;
    data.NeedVisa = visa;
    
}

/*!
* Деструктор класса - записи
*/
Journey::~Journey()
{

}

/*!
* Оператор присваивания
* \param [in] other правый операнд (что присваиваем)
* \return ссылка на присвоенную запись
*/
Journey& Journey::operator= (const Journey &other)
{
    //присваиваем левому операнду значения полей правого
    this->data.kindOfRecreationIndex = other.data.kindOfRecreationIndex;
    this->data.countryIndex          = other.data.countryIndex;
    this->data.recreationPlace       = other.data.recreationPlace;
    this->data.ticketCost            = other.data.ticketCost;
    this->data.duration              = other.data.duration;
    this->data.NeedVisa              = other.data.NeedVisa;

    this->data.ID = other.data.ID; //не забываем про ID

    return *this;
}

/*!
* Оператор сравнения "равно"
* \param [in] other правый операнд
* \return результат сравнения
*/
bool Journey::operator== (const Journey &other) const
{
    return (this->data.kindOfRecreationIndex == other.data.kindOfRecreationIndex &&
        this->data.countryIndex              == other.data.countryIndex		     &&
        this->data.recreationPlace           == other.data.recreationPlace	     &&
        this->data.ticketCost                == other.data.ticketCost            &&
        this->data.duration                  == other.data.duration              &&
        this->data.NeedVisa                  == other.data.NeedVisa              &&
        this->data.ID                        == other.data.ID);
}

/*!                                                                                                 
* Оператор сравнения "не равно"
* \param [in] other правый операнд
* \return результат сравнения
*/
bool Journey::operator!= (const Journey &other) const                                                   
{
    //истинно, если не равно
    return !(*this == other);
}

/*!
* Оператор сравнения "меньше"
* \param [in] other правый операнд
* \return результат сравнения
*/
bool Journey::operator< (const Journey &other) const
{
    //Записи упорядочиваются по следующим полям: вид отдыха, страна, стоимость путевки
    //Внимние! Сортируем по индексам, а не по алфавиту

    //если вид отдыха строго меньше
    if (data.kindOfRecreationIndex < other.data.kindOfRecreationIndex) 
    {
        return true;
    }
    //иначе если равны, смотрим на все остальное
    else if (data.kindOfRecreationIndex == other.data.kindOfRecreationIndex)  
    {
        //если страна строго меньше, остальное не важно
        if (data.countryIndex < other.data.countryIndex)  
        {
            return true;
        }
        //страны равны, смотрим на стоимость
        else if (data.countryIndex == other.data.countryIndex)  
        {
            // если стоимость меньше
            if (data.ticketCost < other.data.ticketCost)
            {
                return true;
            }
        }
    }

    //иначе не меньше
    return false;   
}

/*!
* Оператор сравнения "меньше или равно"
* \param [in] other правый операнд
* \return результат сравнения
*/
bool Journey::operator<= (const Journey &other) const
{
    //Внимание! Здесь равно "сортировочное". совпадение не полное!

    //если меньше или важные для сортировки поля совпадают - true
    return (*this < other ||
             this->data.kindOfRecreationIndex == other.data.kindOfRecreationIndex &&
             this->data.countryIndex == other.data.countryIndex &&
             this->data.ticketCost == other.data.ticketCost);
}

/*!
* Оператор сравнения "больше"
* \param [in] other правый операнд
* \return результат сравнения
*/
bool Journey::operator> (const Journey &other) const
{
    //истинно, если не меньше или равно
    return !(*this <= other);
}

/*!
* Оператор сравнения "больше или равно"
* \param [in] other правый операнд
* \return результат сравнения
*/
bool Journey::operator>= (const Journey &other) const
{
    //истинно, если не меньше или некоторые поля равны
    return !(*this < other) ||
            (this->data.kindOfRecreationIndex == other.data.kindOfRecreationIndex &&
             this->data.countryIndex == other.data.countryIndex &&
             this->data.ticketCost == other.data.ticketCost);
}

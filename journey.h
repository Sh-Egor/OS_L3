#ifndef JOURNEY_H
#define JOURNEY_H

#include <QTextCodec>

struct journeyRecord
{ 
    int kindOfRecreationIndex; //индекс вида отдыха
    int countryIndex; //индекс страны
    QString recreationPlace; //место отдыха
    int ticketCost; //стоимость билета
    int duration; //длительность отдыха
    bool NeedVisa; //нужна ли виза

    int ID; //идентификатор данной записи
};

class Journey
{

public:
    /*!
    * Конструктор по умолчанию класса - записи справочника туриста
    */
    Journey();

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
    Journey(int kind, int country, QString place, int cost, int durat, bool visa);

    /*!
    * Деструктор класса - записи
    */
    ~Journey();                         

    journeyRecord data;

    /*!
    * Оператор присваивания 
    * \param [in] other правый операнд (что присваиваем)
    * \return ссылка на присвоенную запись
    */
    Journey& operator= (const Journey &other);

    /*!
    * Оператор сравнения "равно"
    * \param [in] other правый операнд
    * \return результат сравнения
    */
    bool operator== (const Journey &other) const;

    /*!
    * Оператор сравнения "не равно"
    * \param [in] other правый операнд
    * \return результат сравнения
    */
    bool operator!= (const Journey &other) const;

    /*!
    * Оператор сравнения "меньше"
    * \param [in] other правый операнд
    * \return результат сравнения
    */
    bool operator<  (const Journey &other) const;

    /*!
    * Оператор сравнения "меньше или равно"
    * \param [in] other правый операнд
    * \return результат сравнения
    */
    bool operator<= (const Journey &other) const;

    /*!
    * Оператор сравнения "больше"
    * \param [in] other правый операнд
    * \return результат сравнения
    */
    bool operator>  (const Journey &other) const;

    /*!
    * Оператор сравнения "больше или равно"
    * \param [in] other правый операнд
    * \return результат сравнения
    */
    bool operator>= (const Journey &other) const;

};

#endif // JOURNEY_H

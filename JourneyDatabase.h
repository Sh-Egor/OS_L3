#pragma once

#include <QMap>      
#include <QFile>
#include <QDatastream>
#include <QVector>
#include <QList>
#include <QtWidgets/QMessageBox>
#include "journey.h"
#include <Windows.h>
#include <QString>

enum queries {
    //здесь запросы
    _count = 1,
    _append = 2,
    _remove = 3,
    _update = 4,
    _record = 5,
    _records = 6,
    _clear = 7,
    _isModified = 8,
    _close = 9,
    _save = 10

};


struct newRecordData
{
    int new_id;
    int pos; //позиция записи в порядке сортировки
};

//структура со сведениями для добавления записи в браузер
struct browserItemData
{
    int kindIndex; //индекс вида отдыха
    QString place; //место отдыха
    int cost; //стоимость отдыха
    int ID; //идентификатор записи
};

class JourneyDatabase
{

public:

    /*!
    * Конструктор по умолчанию базы данных
    */
    JourneyDatabase(HANDLE h);

    /*!
    * Деструктор базы данных
    */
    ~JourneyDatabase();

    /*!
    * Функция получения количества записей
    * \return количество записей в БД
    */
    int count() const;
                                      
    /*!
    * Добавляет запись record в БД, присваивает ей ID
    * \param [in|out] record запись
    * \return позиция записи в соответствии с порядком сортировки
    */
    //int append(Journey& record);
    newRecordData append(journeyRecord record);

    /*!
    * Удаляет запись с заданным ID из БД
    * \param [in] id ID удаляемой записи
    */
    void remove(unsigned int id);

    /*!
    * Изменяет запись в БД
    * \param [in] id идентификатор записи
    * \param [in] name имя (идентификатор поля) записи
    * \param [in] value новое значение поля (в строковом формате)
    * \return новая позиция записи в соответствии с порядком сортировки
    */
    //int update(unsigned int id, const QString &name, const QString &value);
    int update(unsigned int id, const QString name, const QString value);

    /*!
    * Возвращает запись по ID для чтения 
    * \param [in] id ID записи
    * \param [out] record ссылка на место для записи
    */
    //void record(unsigned int id, Journey& record);
    journeyRecord record(unsigned int id);
    
    /*!
    * Возвращает вектор структур с информацией для добавления записей в браузер
    * \return вектор структур browserItemData
    */
    int records(browserItemData *items) const;

    /*!
    * Загружает данные из файла
    * \return флаг успешности
    */
    bool load();

    /*!
    * Сохраняет данные в файл
    * \return флаг успешности
    */
    bool save() const;

    /*!
    * Уничтожает все данные в БД
    */
    void clear();

    /*!
    * Сообщает, была ли изменена БД со времени последнего сохранения
    * \return true - есть несохраненные изменения. иначе false
    */
    bool isModified() const;

private:
    HANDLE hPipe;
    
};

#include "JourneyDatabase.h"

/*!
* Конструктор по умолчанию базы данных
*/
JourneyDatabase::JourneyDatabase(HANDLE h)
{
    hPipe = h;
}

/*!
* Деструктор базы данных
*/
JourneyDatabase::~JourneyDatabase()
{
}

/*!
* Функция получения количества записей
* \return количество записей в БД
*/
int JourneyDatabase::count() const
{
    //просто узнаем количество элементов в контейнере
    DWORD read;
    queries query = _count;
    WriteFile(hPipe, &query, sizeof(query), &read, nullptr);

    int cnt;
    DWORD written;
    ReadFile(hPipe, &cnt, sizeof(cnt), &written, nullptr);
    return cnt;
}

/*!
* Добавляет запись record в БД, присваивает ей ID
* \param [in|out] record запись
* \return позиция записи в соответствии с порядком сортировки
*/
newRecordData JourneyDatabase::append(journeyRecord record)
//int JourneyDatabase::append(Journey& record)
{
    DWORD read, written;
    queries query = _append;
    WriteFile(hPipe, &query, sizeof(query), &read, nullptr);

    Journey temp;
    newRecordData recordData;

    WriteFile(hPipe, &temp.data.kindOfRecreationIndex, sizeof(int), &written,nullptr);
    WriteFile(hPipe, &temp.data.countryIndex, sizeof(int), &written, nullptr);

    int str_size = temp.data.recreationPlace.size() + 1;
    WriteFile(hPipe, &str_size, sizeof(int), &written, nullptr);
    WriteFile(hPipe, temp.data.recreationPlace.data(), str_size*sizeof(QChar), &written, nullptr);

    WriteFile(hPipe, &temp.data.ticketCost, sizeof(int), &written, nullptr);
    WriteFile(hPipe, &temp.data.duration, sizeof(int), &written, nullptr);
    WriteFile(hPipe, &temp.data.NeedVisa, sizeof(bool), &written, nullptr);
    WriteFile(hPipe, &temp.data.ID, sizeof(int), &written, nullptr);

    ReadFile(hPipe, &recordData.new_id, sizeof(int), &written,nullptr);
    ReadFile(hPipe, &recordData.pos, sizeof(int), &written, nullptr);

    return recordData;

}



/*!
* Удаляет запись с заданным ID из БД
* \param [in] id ID удаляемой записи
*/
void JourneyDatabase::remove(unsigned int id)
{
    DWORD read;
    queries query = _remove;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    DWORD written;
    WriteFile(hPipe, &id, sizeof(int), &written, NULL);

    bool s;
    ReadFile(hPipe, &s, sizeof(bool), &written, NULL);
}

/*!
* Изменяет запись в БД
* \param [in] id идентификатор записи
* \param [in] name имя (идентификатор поля) записи
* \param [in] value новое значение поля (в строковом формате)
* \return новая позиция записи в соответствии с порядком сортировки
*/
int JourneyDatabase::update(unsigned int id, const QString name, const QString value)
{
    DWORD read, written;
    queries query = _update;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    WriteFile(hPipe, &id, sizeof(int), &written, NULL);

    int str_size = name.size() + 1;
    WriteFile(hPipe, &str_size, sizeof(int), &written, NULL);
    WriteFile(hPipe, name.data(), str_size*sizeof(QChar), &written, NULL);

    str_size = value.size() + 1;
    WriteFile(hPipe, &str_size, sizeof(int), &written, NULL);
    WriteFile(hPipe, value.data(), str_size*sizeof(QChar), &written, NULL);

    int s;
    ReadFile(hPipe, &s, sizeof(s), &written, NULL);

    return s;
    
}

/*!
* Возвращает запись по ID для чтения
* \param [in] id ID записи
* \param [out] record ссылка на место для записи
*/
journeyRecord JourneyDatabase::record(unsigned int id)
{
    DWORD read, written;
    queries query = _record;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    WriteFile(hPipe, &id, sizeof(int), &written, NULL);

    journeyRecord rec;

    ReadFile(hPipe, &rec.kindOfRecreationIndex, sizeof(int), &read, NULL);
    ReadFile(hPipe, &rec.countryIndex, sizeof(int), &read, NULL);

    int str_size;
    ReadFile(hPipe, &str_size, sizeof(int), &read, NULL);
    rec.recreationPlace.resize(str_size - 1);
    ReadFile(hPipe, rec.recreationPlace.data(), str_size*sizeof(QChar), &read, NULL);

    ReadFile(hPipe, &rec.ticketCost, sizeof(int), &read, NULL);
    ReadFile(hPipe, &rec.duration, sizeof(int), &read, NULL);
    ReadFile(hPipe, &rec.NeedVisa, sizeof(bool), &read, NULL);
    ReadFile(hPipe, &rec.ID, sizeof(int), &read, NULL);

    return rec;
    
}

/*!
* Возвращает вектор структур с информацией для добавления записей в браузер
* \return вектор структур browserItemData
*/
int JourneyDatabase::records(browserItemData *temp) const
{
    DWORD read, written;
    queries query = _records;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    int size;
    ReadFile(hPipe, &size, sizeof(int), &read, NULL);

    for (int i = 0; i < size; i++) {
        ReadFile(hPipe, &temp[i].kindIndex, sizeof(int), &read, NULL);

        int str_size;
        ReadFile(hPipe, &str_size, sizeof(int), &read, NULL);
        temp[i].place.resize(str_size - 1);
        ReadFile(hPipe, temp[i].place.data(), str_size*sizeof(QChar), &read, NULL);

        ReadFile(hPipe, &temp[i].cost, sizeof(int), &read, NULL);
        ReadFile(hPipe, &temp[i].ID, sizeof(int), &read, NULL);
    }

    return size;
}

/*!
* Загружает данные из файла
* \return флаг успешности
*/
bool JourneyDatabase::load()
{
    return true;
}

/*!
* Сохраняет данные в файл
* \return флаг успешности
*/
bool JourneyDatabase::save() const
{
    
    DWORD read, written;
    queries query = _save;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    bool s;
    ReadFile(hPipe, &s, sizeof(bool), &written, NULL);
    return s;
}

/*!
* Уничтожает все данные в БД
*/
void JourneyDatabase::clear()
{
    DWORD read, written;
    queries query = _clear;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    bool s;
    ReadFile(hPipe, &s, sizeof(bool), &written, NULL);

}

/*!
* Сообщает, была ли изменена БД со времени последнего сохранения
* \return true - есть несохраненные изменения. иначе false
*/
bool JourneyDatabase::isModified() const
{
    DWORD read, written;
    queries query = _isModified;
    WriteFile(hPipe, &query, sizeof(query), &read, NULL);

    bool s;
    ReadFile(hPipe, &s, sizeof(bool), &written, NULL);
    return s;
}


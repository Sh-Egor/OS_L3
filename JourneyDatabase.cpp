#include "JourneyDatabase.h"

/*!
* ����������� �� ��������� ���� ������
*/
JourneyDatabase::JourneyDatabase(HANDLE h)
{
    hPipe = h;
}

/*!
* ���������� ���� ������
*/
JourneyDatabase::~JourneyDatabase()
{
}

/*!
* ������� ��������� ���������� �������
* \return ���������� ������� � ��
*/
int JourneyDatabase::count() const
{
    //������ ������ ���������� ��������� � ����������
    DWORD read;
    queries query = _count;
    WriteFile(hPipe, &query, sizeof(query), &read, nullptr);

    int cnt;
    DWORD written;
    ReadFile(hPipe, &cnt, sizeof(cnt), &written, nullptr);
    return cnt;
}

/*!
* ��������� ������ record � ��, ����������� �� ID
* \param [in|out] record ������
* \return ������� ������ � ������������ � �������� ����������
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
* ������� ������ � �������� ID �� ��
* \param [in] id ID ��������� ������
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
* �������� ������ � ��
* \param [in] id ������������� ������
* \param [in] name ��� (������������� ����) ������
* \param [in] value ����� �������� ���� (� ��������� �������)
* \return ����� ������� ������ � ������������ � �������� ����������
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
* ���������� ������ �� ID ��� ������
* \param [in] id ID ������
* \param [out] record ������ �� ����� ��� ������
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
* ���������� ������ �������� � ����������� ��� ���������� ������� � �������
* \return ������ �������� browserItemData
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
* ��������� ������ �� �����
* \return ���� ����������
*/
bool JourneyDatabase::load()
{
    return true;
}

/*!
* ��������� ������ � ����
* \return ���� ����������
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
* ���������� ��� ������ � ��
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
* ��������, ���� �� �������� �� �� ������� ���������� ����������
* \return true - ���� ������������� ���������. ����� false
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


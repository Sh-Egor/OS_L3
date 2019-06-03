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
    //����� �������
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
    int pos; //������� ������ � ������� ����������
};

//��������� �� ���������� ��� ���������� ������ � �������
struct browserItemData
{
    int kindIndex; //������ ���� ������
    QString place; //����� ������
    int cost; //��������� ������
    int ID; //������������� ������
};

class JourneyDatabase
{

public:

    /*!
    * ����������� �� ��������� ���� ������
    */
    JourneyDatabase(HANDLE h);

    /*!
    * ���������� ���� ������
    */
    ~JourneyDatabase();

    /*!
    * ������� ��������� ���������� �������
    * \return ���������� ������� � ��
    */
    int count() const;
                                      
    /*!
    * ��������� ������ record � ��, ����������� �� ID
    * \param [in|out] record ������
    * \return ������� ������ � ������������ � �������� ����������
    */
    //int append(Journey& record);
    newRecordData append(journeyRecord record);

    /*!
    * ������� ������ � �������� ID �� ��
    * \param [in] id ID ��������� ������
    */
    void remove(unsigned int id);

    /*!
    * �������� ������ � ��
    * \param [in] id ������������� ������
    * \param [in] name ��� (������������� ����) ������
    * \param [in] value ����� �������� ���� (� ��������� �������)
    * \return ����� ������� ������ � ������������ � �������� ����������
    */
    //int update(unsigned int id, const QString &name, const QString &value);
    int update(unsigned int id, const QString name, const QString value);

    /*!
    * ���������� ������ �� ID ��� ������ 
    * \param [in] id ID ������
    * \param [out] record ������ �� ����� ��� ������
    */
    //void record(unsigned int id, Journey& record);
    journeyRecord record(unsigned int id);
    
    /*!
    * ���������� ������ �������� � ����������� ��� ���������� ������� � �������
    * \return ������ �������� browserItemData
    */
    int records(browserItemData *items) const;

    /*!
    * ��������� ������ �� �����
    * \return ���� ����������
    */
    bool load();

    /*!
    * ��������� ������ � ����
    * \return ���� ����������
    */
    bool save() const;

    /*!
    * ���������� ��� ������ � ��
    */
    void clear();

    /*!
    * ��������, ���� �� �������� �� �� ������� ���������� ����������
    * \return true - ���� ������������� ���������. ����� false
    */
    bool isModified() const;

private:
    HANDLE hPipe;
    
};

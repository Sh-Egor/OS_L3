#ifndef JOURNEY_H
#define JOURNEY_H

#include <QTextCodec>

struct journeyRecord
{ 
    int kindOfRecreationIndex; //������ ���� ������
    int countryIndex; //������ ������
    QString recreationPlace; //����� ������
    int ticketCost; //��������� ������
    int duration; //������������ ������
    bool NeedVisa; //����� �� ����

    int ID; //������������� ������ ������
};

class Journey
{

public:
    /*!
    * ����������� �� ��������� ������ - ������ ����������� �������
    */
    Journey();

    /*!
    * ����������� � ����������� ������ - ������ ����������� �������
    * ���������� ��� ������������ ������� ������ �������.
    * \param [in] kind ��� ������ (������)	
    * \param [in] country ������ ������	(������)
    * \param [in] place ����� ������
    * \param [in] cost ��������� ������
    * \param [in] durat ������������ ������
    * \param [in] visa ���� ������������� ����
    */
    Journey(int kind, int country, QString place, int cost, int durat, bool visa);

    /*!
    * ���������� ������ - ������
    */
    ~Journey();                         

    journeyRecord data;

    /*!
    * �������� ������������ 
    * \param [in] other ������ ������� (��� �����������)
    * \return ������ �� ����������� ������
    */
    Journey& operator= (const Journey &other);

    /*!
    * �������� ��������� "�����"
    * \param [in] other ������ �������
    * \return ��������� ���������
    */
    bool operator== (const Journey &other) const;

    /*!
    * �������� ��������� "�� �����"
    * \param [in] other ������ �������
    * \return ��������� ���������
    */
    bool operator!= (const Journey &other) const;

    /*!
    * �������� ��������� "������"
    * \param [in] other ������ �������
    * \return ��������� ���������
    */
    bool operator<  (const Journey &other) const;

    /*!
    * �������� ��������� "������ ��� �����"
    * \param [in] other ������ �������
    * \return ��������� ���������
    */
    bool operator<= (const Journey &other) const;

    /*!
    * �������� ��������� "������"
    * \param [in] other ������ �������
    * \return ��������� ���������
    */
    bool operator>  (const Journey &other) const;

    /*!
    * �������� ��������� "������ ��� �����"
    * \param [in] other ������ �������
    * \return ��������� ���������
    */
    bool operator>= (const Journey &other) const;

};

#endif // JOURNEY_H

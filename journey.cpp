#include "journey.h"

/*!
* ����������� �� ��������� ������ - ������ ����������� �������
*/
Journey::Journey()
{
    // ������������� QTextCodec
    QTextCodec* c = QTextCodec::codecForLocale();

    // ������������� ����� ������ ������������ ����������
    data.kindOfRecreationIndex = 0;
    data.countryIndex = 0;
    data.recreationPlace = c->toUnicode("��������");
    data.ticketCost = 3000;
    data.duration = 2;
    data.NeedVisa = false;

    //ID ����� �������� ��� ���������� � ��
}

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
Journey::Journey(int kind, int country, QString place, int cost, int durat, bool visa)
{
    //����������� ����� ������ ���������� ��������
    data.kindOfRecreationIndex = kind;
    data.countryIndex = country;
    data.recreationPlace = place;
    data.ticketCost = cost;
    data.duration = durat;
    data.NeedVisa = visa;
    
}

/*!
* ���������� ������ - ������
*/
Journey::~Journey()
{

}

/*!
* �������� ������������
* \param [in] other ������ ������� (��� �����������)
* \return ������ �� ����������� ������
*/
Journey& Journey::operator= (const Journey &other)
{
    //����������� ������ �������� �������� ����� �������
    this->data.kindOfRecreationIndex = other.data.kindOfRecreationIndex;
    this->data.countryIndex          = other.data.countryIndex;
    this->data.recreationPlace       = other.data.recreationPlace;
    this->data.ticketCost            = other.data.ticketCost;
    this->data.duration              = other.data.duration;
    this->data.NeedVisa              = other.data.NeedVisa;

    this->data.ID = other.data.ID; //�� �������� ��� ID

    return *this;
}

/*!
* �������� ��������� "�����"
* \param [in] other ������ �������
* \return ��������� ���������
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
* �������� ��������� "�� �����"
* \param [in] other ������ �������
* \return ��������� ���������
*/
bool Journey::operator!= (const Journey &other) const                                                   
{
    //�������, ���� �� �����
    return !(*this == other);
}

/*!
* �������� ��������� "������"
* \param [in] other ������ �������
* \return ��������� ���������
*/
bool Journey::operator< (const Journey &other) const
{
    //������ ��������������� �� ��������� �����: ��� ������, ������, ��������� �������
    //�������! ��������� �� ��������, � �� �� ��������

    //���� ��� ������ ������ ������
    if (data.kindOfRecreationIndex < other.data.kindOfRecreationIndex) 
    {
        return true;
    }
    //����� ���� �����, ������� �� ��� ���������
    else if (data.kindOfRecreationIndex == other.data.kindOfRecreationIndex)  
    {
        //���� ������ ������ ������, ��������� �� �����
        if (data.countryIndex < other.data.countryIndex)  
        {
            return true;
        }
        //������ �����, ������� �� ���������
        else if (data.countryIndex == other.data.countryIndex)  
        {
            // ���� ��������� ������
            if (data.ticketCost < other.data.ticketCost)
            {
                return true;
            }
        }
    }

    //����� �� ������
    return false;   
}

/*!
* �������� ��������� "������ ��� �����"
* \param [in] other ������ �������
* \return ��������� ���������
*/
bool Journey::operator<= (const Journey &other) const
{
    //��������! ����� ����� "�������������". ���������� �� ������!

    //���� ������ ��� ������ ��� ���������� ���� ��������� - true
    return (*this < other ||
             this->data.kindOfRecreationIndex == other.data.kindOfRecreationIndex &&
             this->data.countryIndex == other.data.countryIndex &&
             this->data.ticketCost == other.data.ticketCost);
}

/*!
* �������� ��������� "������"
* \param [in] other ������ �������
* \return ��������� ���������
*/
bool Journey::operator> (const Journey &other) const
{
    //�������, ���� �� ������ ��� �����
    return !(*this <= other);
}

/*!
* �������� ��������� "������ ��� �����"
* \param [in] other ������ �������
* \return ��������� ���������
*/
bool Journey::operator>= (const Journey &other) const
{
    //�������, ���� �� ������ ��� ��������� ���� �����
    return !(*this < other) ||
            (this->data.kindOfRecreationIndex == other.data.kindOfRecreationIndex &&
             this->data.countryIndex == other.data.countryIndex &&
             this->data.ticketCost == other.data.ticketCost);
}

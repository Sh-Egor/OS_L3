#include "placeofrestvalidator.h"

PlaceOfRestValidator::PlaceOfRestValidator(QObject *parent)
    : QValidator(parent)
{

}

PlaceOfRestValidator::~PlaceOfRestValidator()
{

}

/*!
* �������-��������� ��� ���������� ����� ������.
* \param [in] input ��������������� ����
* \param [in] pos ������� �������
* \return ��� ���������� �������� ������ �� QValidator::State
*/
QValidator::State PlaceOfRestValidator::validate(QString & input, int & pos ) const
{
    //���� ���-�� ������� � ������ ��������� ������ �� ���������
    if (input.length() > 0 && !input.at(0).isUpper())
        return QValidator::Intermediate;

    return QValidator::Acceptable;
}
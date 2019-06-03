#ifndef PLACEOFRESTVALIDATOR_H
#define PLACEOFRESTVALIDATOR_H

#include <QObject>
#include <QValidator>

class PlaceOfRestValidator : public QValidator
{
    Q_OBJECT

public:
    PlaceOfRestValidator(QObject *parent);
    ~PlaceOfRestValidator();

    /*!
    * �������-��������� ��� ���������� ����� ������.
    * \param [in] input ��������������� ����
    * \param [in] pos ������� �������
    * \return ��� ���������� �������� ������ �� QValidator::State
    */
    QValidator::State validate(QString & input, int & pos ) const;

private:
    
};

#endif // PLACEOFRESTVALIDATOR_H

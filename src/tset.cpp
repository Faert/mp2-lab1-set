// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(TBitField(mp)), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(TBitField(s.BitField)), MaxPower(s.GetMaxPower())
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return (BitField.GetBit(Elem));
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.GetMaxPower();
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if ((MaxPower == s.GetMaxPower()) && (BitField == s.BitField))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (*this == s)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

TSet TSet::operator+(const TSet &s) // объединение
{
    const int TempPower = (MaxPower >= s.GetMaxPower() ? MaxPower : s.GetMaxPower());
    TSet Temp(TempPower);
    Temp.BitField = BitField | s.BitField;
    return Temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet Temp(*this);
    Temp.BitField.SetBit(Elem);
    return Temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet Temp(*this);
    Temp.BitField.ClrBit(Elem);
    return Temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    const int TempPower = (MaxPower >= s.GetMaxPower() ? MaxPower : s.GetMaxPower());
    TSet Temp(TempPower);
    Temp.BitField = BitField & s.BitField;
    return Temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet Temp(MaxPower);
    Temp.BitField = ~BitField;
    return Temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    //Ожидается, что ввод закончится переходом на новую строку сразу после ввода последнего числа(1 3\n, а не 1 3 \n).
    int elem;
    while(cin.peek() != '\n')
    {
        istr >> elem;
        s.InsElem(elem);
    }
    
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    //Изменён, чтобы соответствовать вводу.
    int last = s.GetMaxPower() - 1;
    while (!s.IsMember(last))
    {
        last--;
    }
    for (int i = 0; i < last; i++)
    {
        if (s.IsMember(i))
        {
            ostr << i << " ";
        }
    }
    ostr << last << "\n";
    return ostr;
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{
	if (len <= 0)
	{
		cout << "negative len\n";
		throw "negative len";
	}
	else
	{
		MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField& bf) : BitLen(bf.BitLen) // конструктор копирования
{
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n <= BitLen)
	{
		if (n >= 0)
		{
			return n / (sizeof(TELEM) * 8);
		}
		else
		{
			cout << "negative index\n";
			throw "negative index";
		}
	}
	else
	{
		cout << "large index\n";
		throw "large index";
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n <= BitLen)
	{
		if (n >= 0)
		{
			return 1 << (n % (sizeof(TELEM) * 8));
		}
		else
		{
			cout << "negative index\n";
			throw "negative index";
		}
	}
	else
	{
		cout << "large index\n";
		throw "large index";
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (this->GetBit(n) != 1)
	{
		pMem[GetMemIndex(n)] += GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (this->GetBit(n) != 0)
	{
		pMem[GetMemIndex(n)] -= GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	return bool(pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	TBitField temp(bf);
	swap(temp.pMem, pMem);
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen == bf.BitLen && MemLen == bf.MemLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (bf.pMem[i] != pMem[i])
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField temp(*this);
	if (bf.GetLength() <= BitLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			temp.pMem[i] = (bf.pMem[i] | pMem[i]);
		}
	}
	else
	{
		temp = bf;
		for (int i = 0; i < MemLen; i++)
		{
			temp.pMem[i] = (bf.pMem[i] | pMem[i]);
		}
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField temp(BitLen);
	if (bf.GetLength() <= BitLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			temp.pMem[i] = (bf.pMem[i] & pMem[i]);
		}
	}
	else
	{
		TBitField temp0(bf.BitLen);
		temp = temp0;
		for (int i = 0; i < MemLen; i++)
		{
			temp.pMem[i] = (bf.pMem[i] & pMem[i]);
		}
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen - 1; i++)
	{
		temp.pMem[i] = ~pMem[i];
	}
	for (int i = (MemLen - 1)*8*sizeof(TELEM); i < BitLen; i++)
	{
		if (this->GetBit(i) == 0)
		{
			temp.SetBit(i);
		}
		else
		{
			temp.ClrBit(i);
		}
	}
	return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	size_t a;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		istr >> a;
		if (a == 0)
		{
			bf.ClrBit(i);
		}
		else
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	{
		ostr << bf.GetBit(i);
		if ((i + 1) % (sizeof(TELEM) * 8) == 0)
		{
			ostr << "\n";
		}
	}
	ostr << "\n";
	return ostr;
}

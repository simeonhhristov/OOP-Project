#include "string.h"

String::String()
{
    this->data = nullptr;
    this->size = 0;
}

String::String(const String &other)
{
    setData(other.data);
    this->size = other.size;
}

String::String(size_t size)
{
    this->size = size;
    this->data = new char[this->size];
}
String &String::operator=(const String &other)
{
    if (this != &other)
    {
        delete this->data;
        setData(other.data);
        this->size = other.size;
    }

    return *this;
}
String::String(const char *data)
{
    setData(data);
    int i = 0;
    for (; data[i] != '\0'; i++)
    {
    }
    this->size = i;
}
String::~String()
{
    delete this->data;
}

void String::setData(const char *data)
{
    this->data = new char[strlen(data) + 1];

    for (int j = 0; j < strlen(data); j++)
    {
        this->data[j] = data[j];
    }

    this->data[strlen(data)] = '\0';
}
char *String::getData() const
{
    return this->data;
}
int String::getSize() const
{
    int i = 0;
    for (; this->data[i] != '\0'; i++)
    {
    }
    return i;
}
String &String::concat(const String &other)
{
    return *this += other;
}
//[подходящ тип] split(const char* delimiter); //Разделя низа по подаден символ или низ
String &String::reverse()
{
    int index = this->getSize() - 1;
    for (size_t i = 0; i <= index / 2; i++)
    {
        std::swap(this->data[i], this->data[index - i]);
    }

    return *this;
}
void String::clear()
{
    delete this->data;
    this->size = 0;
}
bool String::empty()
{
    if (this->data[0])
    {
        return 0;
    }
    return 1;
}
char String::toUpper(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }

    return c;
}
bool String::isContained(String other)
{
    int M = this->getSize();
    int N = other.getSize();
    if (M == N)
    {
        for (size_t i = 0; i < M; i++)
        {
            if (toUpper(this->data[i]) != toUpper(other.data[i]))
            {
                return 0;
            }
        }
        return true;
    }

    for (int i = 0; i < N - M; i++)
    {
        int j;

        for (j = 0; j < M; j++)
        {
            if (toUpper(other[i + j]) != toUpper(this->data[j]))
            {
                break;
            }
        }
        if (j == M)
        {
            return 1;
        }
    }

    return 0;
}
void String::charReplace(char toReplace, char newChar)
{
    for (size_t i = 0; this->data[i] != '\0'; i++)
    {
        if (this->data[i] == toReplace)
        {
            this->data[i] = newChar;
        }
    }
}

char &String::operator[](int index)
{
    if (index >= 0 && index < this->size)
    {
        return this->data[index];
    }
    std::cout << "Index out of bounds" << std::endl;
    return this->data[0];
}

String &String::operator+=(const String &other)
{
    this->append(other);

    return *this;
}
String String::operator+(const String &other)
{
    String sum(*this);
    sum += other;

    return sum;
}

bool String::operator==(const String &other)
{
    int i = 0;
    for (; this->data[i] != '\0'; i++)
    {
        if (this->data[i] != other.data[i])
        {
            return false;
        }
    }
    if (other.data[i] != '\0')
    {
        return false;
    }

    return true;
}
String &String::append(const String &other)
{
    char *temp = new char[this->getSize() + other.getSize() + 1];

    for (size_t i = 0; i < this->getSize(); i++)
    {
        temp[i] = this->data[i];
    }
    for (size_t i = 0; i < other.getSize(); i++)
    {
        temp[i + this->getSize()] = other.data[i];
    }

    this->size = this->getSize() + other.getSize();
    delete[] this->data;
    this->data = new char[this->size + 1];

    for (size_t i = 0; i < this->size; i++)
    {
        this->data[i] = temp[i];
    }
    this->data[this->size] = '\0';

    return *this;
}

void String::pushBack(char letter)
{
    char *temp = new char[this->getSize() + 2];
    for (size_t i = 0; i < this->getSize(); i++)
    {
        temp[i] = this->data[i];
    }

    temp[this->getSize()] = letter;
    temp[this->getSize() + 1] = '\0';

    delete[] this->data;
    this->data = temp;
    this->size++;
}
void String::popBack()
{
    char *newStr = new char[this->size - 1];
    for (int i = 0; i < this->size - 1; i++)
    {
        newStr[i] = this->data[i];
    }
    *this = newStr;
    delete[] newStr;
}
void String::swap(String &other)
{
    String temp(*this);
    *this = other;
    other = temp;
}

void String::print()
{
    std::cout << "{" << this->data << "}";
}
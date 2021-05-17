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

    int i = 0;
    for (; data[i] != '\0'; i++)
    {
    }
    this->data = new char[i + 1];

    for (int j = 0; j < i; j++)
    {
        this->data[j] = data[j];
    }
}

int String::getSize() const
{
    return this->size;
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
    char *newString = new char[this->size + other.size];
    for (int i = 0; i < this->size; i++)
    {
        newString[i] = this->data[i];
    }
    for (int i = 0; i < other.size; i++)
    {
        newString[i + this->size] = other.data[i];
    }

    delete this->data;
    this->size += other.size;
    this->data = new char[this->size];

    for (int i = 0; i < this->size; i++)
    {
        this->data[i] = newString[i];
    }
    delete[] newString;

    return *this;
}
String String::operator+(const String &other)
{
    String sum(*this);
    sum += other;

    return sum;
}

bool String::operator==(const String& other)
{   
    int i = 0;
    for (; this->data[i] != '\0'; i++)
    {
        if (this->data[i] != other.data[i])
        {
            return false;
        }
    }
    if (other.data[i]!= '\0')
    {
        return false;
    }
    
    return true;
}
String &String::append(const String &other)
{
    *this += other;

    return *this;
}
void String::pushBack(char letter)
{
    char *newStr = new char[this->size + 1];
    for (int i = 0; i < this->size + 1; i++)
    {
        newStr[i] = this->data[i];
    }
    newStr[this->size] = letter;
    String tempStr(newStr);

    *this = tempStr;
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
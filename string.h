#pragma once
#include <iostream>
#include <cstring>
class String
{
public:
    char *data;
    size_t size;

public:
    String();
    String(const String &);
    String(size_t size);
    String &operator=(const String &);
    String(const char *data);
    ~String();

    friend std::istream &operator>>(std::istream &in, String &other)
    {
        other.data = new char[256];
        other.size = 256;
        in >> other.data;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const String &other)
    {
        for (size_t i = 0; other.data[i] != '\0'; i++)
        {
            out << other.data[i];
        }
        return out;
    }

    void setData(const char *);
    int getSize() const;            //Връща размера на низа
    String &concat(const String &); //Конкатенира два низа (низ1 = "а", низ2 = "b", низ1.concat(низ2) = "ab")

    String &reverse(); //Обръща елементите на низа
    void clear();      //Изчиства елементите на низа
    bool empty();      //Проверява дали низа е празен

    char &operator[](int index);        //Връща символ от низа
    String &operator+=(const String &); //Добавя към един низ друг
    String operator+(const String &);   //Събира два низа и връща нов низ
    bool operator==(const String &);
    String &append(const String &); //Добавя към един низ друг
    void pushBack(char);            //Добавя символ в края на низа
    void popBack();                 //Премахва символ от края на низа
    void swap(String &);            //Разменя стойностите на два низа

    void print(); //Извежда на стандартния изход низ
};
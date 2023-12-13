// Задача №1 "Smatrix"
// 2 курс, комп'ютерна математика 2, Пузанов Павло
// Заголовний файл з ініціалізацією класів SVector та Smatrix, 
// а також усіх їхніх методів

#ifndef __CLASSES_H__
#define __CLASSES_H__

#include "Smatrix_general.h"

class SVector;
class SMatrix;

class SVector {

    friend SMatrix;

    private:
        UInt length;
        MType values;

    public:
        /* Метод для введення вектора з консолі */
        void inputFromConsole();

        /* Метод для введення вектора з текстового файлу */
        void inputFromTextFile(const char* file);

        /* Метод для виведення вектора з бінарного файлу */
        void inputFromBinaryFile(const char* file);

        /* Метод для виведення вектора у консоль як рядку чисел 
        із вказаною точністю */
        void printToConsole(UInt precision=2);

        /* Метод для запис вектора у текстовий файл */
        void printToTextFile(const char* file);

        /* Метод для запису вектора у бінарний файл. Є можливість вибору типу запису, а саме 
        "as_row" для запису у рядок та "as_col" для запису у стовпчик */
        void printToBinaryFile(const char* file, const char* printType="as_row");

        /* Перевизначення оператора додавання для класу SVector. 
        Додавання відбувається покоординатно */
        friend SVector operator+(const SVector& x, const SVector& y);

        /* Перевизначення оператора множення для класу SVector таким чином, 
        що при множенні двох векторів знаходиться скалярний добуток */
        friend DType operator*(const SVector& x, const SVector& y);
};

class SMatrix {

    private:
        UInt rows;
        UInt cols;
        MType values;

        /* Допоміжний метод рекурсивного знаходження визначника матриці. 
        Є приватним, викликається в іншому методі для знаходження визначника */
        DType determinant(MType matrix, UInt size);

    public:
        /* Метод для введення матриці з консолі. Аргументами є розміри матриці - 
        кількість рядків та стовпчиків, а також метод введення: "as_row" для введення
        як рядка та "as_table" для введення як таблиці */
        void inputFromConsole(UInt rows=2, UInt cols=2, const char* inputType="as_row");

        /* Метод для введення матриці з текстового файлу. Параметрами є розміри 
        матриці - кількість рядків та стовпчиків */
        void inputFromTextFile(const char* file, UInt rows, UInt cols);

        /* Метод для введення матриці з бінарного файлу. Параметрами є розміри 
        матриць - кількість рядків та стовпчиків */
        void inputFromBinaryFile(const char* file, UInt rows, UInt cols);

        /* Метод для виведення матриці у консоль із вказаною кількістю рядків 
        та точністю */
        void printToConsole(UInt newCols, UInt precision = 2);

        /* Метод для запису матриці у текстовий файл */
        void printToTextFile(const char* file);

        /* Метод для запису матриці у бінарний файл. Є можливість вибору типу запису, а саме 
        "as_row" для запису у рядок та "as_col" для запису у стовпчик */
        void printToBinaryFile(const char* file, const char* printType="as_row");

        /* Перевизначення оператора додавання для матриць. 
        Додавання відбувається покоординатно */
        friend SMatrix operator+(const SMatrix& x, const SMatrix& y);

        /* Перевизначення оператора множення для матриць. 
        Стандартне матричне множення*/
        friend SMatrix operator*(const SMatrix& x, const SMatrix& y);

        /* Метод для знаходження визначника, який викликає допоміжний метод та 
        повертає значення визначника */
        DType determinant();

        /* Метод для знаходження оберненої матриці за допомогою методу алгебраїчних доповнень */
        SMatrix inverse();

        /* Метод для множення матриці на вектор */
        SVector multByVector(const SVector& x);

        /* метод для обміну стовпчиків у матриці */
        void swapColumns(UInt col1, UInt col2);

        /* Метод для обміну рядків у матриці */
        void swapRows(UInt row1, UInt row2);
};

#endif
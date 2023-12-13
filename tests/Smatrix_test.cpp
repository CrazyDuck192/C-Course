// #include "../src/Smatrix.cpp"
#include "../headers/Smatrix_general.h"
#include "../headers/Smatrix_classes.h"

#include <iostream>

using namespace std;

int main() {

    // перевірка введення векторів з консолі, 
    // текстового та бінарного файлів
    SVector v1;
    SVector v2;
    SVector v3;

    v1.inputFromConsole(); // щоб не видало виключення треба вводити вектори довжини 4
    v2.inputFromTextFile("test_vector_input.txt");
    v3.inputFromBinaryFile("test_vector_input.dat"); // вектор у файлі: 1 0 0 2

    // перевірка додавання векторів та виведення вектора у консоль, 
    // запис у текстовий та бінарний файли
    cout << "Додавання векторів: ";
    SVector v4 = v1 + v2;
    v4.printToConsole();
    cout << endl;

    cout << "Додавання векторів: (у текстовий файл)" << endl << endl;
    SVector v5 = v2 + v3;
    v5.printToTextFile("test_vector_output.txt");

    cout << "Додавання векторів: (у бінарний файл)" << endl << endl;
    SVector v6 = v1 + v3;
    v6.printToBinaryFile("test_vector_output.dat");

    // перевірка множення векторів
    cout << "Скалярний добуток: " << v1 * v2 << endl << endl;


    // перевірка введення матриць з консолі, 
    // текстового та бінарного файлів
    SMatrix m1;
    SMatrix m2;
    SMatrix m3;

    m1.inputFromConsole(3, 3, "as_table");
    m2.inputFromTextFile("test_matrix_input.txt", 2, 2);
    m3.inputFromBinaryFile("test_matrix_input.dat", 2, 2); // матриця у файлі: 0 2 0 3

    // перевірка додавання та множення матриць, виведення на екран
    // та запис у текстовий та бінарний файли
    cout << "Додавання матриць: " << endl;
    SMatrix m4 = m2 + m3;
    m4.printToConsole(2);
    cout << endl;

    cout << "Додавання матриць: (у текстовий файл)" << endl << endl;
    SMatrix m5 = m2 + m3;
    m5.printToTextFile("test_matrix_output.txt");

    cout << "Множення матриць: (у бінарний файл)" << endl << endl;
    SMatrix m6 = m2 * m3;
    m6.printToBinaryFile("test_matrix_output.dat");

    // перевірка множення матриці на вектор, знаходження визначника та
    // оберненої матриці
    SVector v7;
    v7.inputFromConsole(); // для коректної роботи - вектор довжини 2
    cout << "Добуток матриці на вектор: ";
    SVector v8 = m2.multByVector(v7);
    v8.printToConsole();
    cout << endl;

    cout << "Визначник матриці: " << m1.determinant() << endl << endl;
    cout << "Обернена матриця: " << endl;
    SMatrix m7 = m1.inverse();
    m7.printToConsole(3);

    return 0;
}
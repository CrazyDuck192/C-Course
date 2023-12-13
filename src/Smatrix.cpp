// Задача №1 "Smatrix"
// 2 курс, комп'ютерна математика 2, Пузанов Павло
// Файл з описом всіх методів класів SVector та SMatrix

#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include <string.h>
using namespace std;

#include "../headers/Smatrix_classes.h"
#include "../headers/Smatrix_general.h"


void SVector::inputFromConsole() {
    printf("Enter vector: ");
    
    DType value;
    UInt counter = 0;
    do { // ввід робиться поки користувач не натисне "Enter"
        scanf("%lf", &value);
        if (value != 0) {
            SVector::values[{0, counter}] = value;
        }
        counter++;
    } while (getchar() != '\n');
    SVector::length = counter;    
}


void SVector::inputFromTextFile(const char* file) {
    ifstream f(file);

    DType value;
    UInt pos = 0;
    while (!f.eof()) { // вивід робиться поки файл не закінчиться
        f >> value;
        if (value != 0) {
            SVector::values[{0, pos}] = value;
        }
        pos++;
    }
    SVector::length = pos;
    f.close();
}


void SVector::printToConsole(UInt precision) {
    for (UInt pos=0; pos < SVector::length; pos++) {
        DType value = SVector::values[{0, pos}];

        // якщо за даним ключем є значення, то воно виводиться із
        // заданою точністю. Інакше виводиться 0
        if (value) {
            printf("%.*lf ", precision, value);
        }
        else {
            printf("%u ", 0);
        }
    }
    printf("\n");
}


void SVector::printToTextFile(const char* file) {
    ofstream f(file);
    for (UInt pos=0; pos < SVector::length; pos++) {

        if (SVector::values.find({0, pos}) != SVector::values.end()) {
            f << SVector::values.at({0, pos});
        }
        else {
            f << 0;
        }

        if (pos != SVector::length-1) {
            f << " ";
        }
    }
    f.close();
}


DType operator*(const SVector& x, const SVector& y) {
    if (x.length != y.length) {
        throw logic_error("Can only multiply vectors of the same size.");
    }

    DType value = 0;
    for (UInt i=0; i < x.length; i++) {
        if ((x.values.find({0, i}) != x.values.end()) &&
        (y.values.find({0, i}) != y.values.end())) {
            value += x.values.at({0, i}) * y.values.at({0, i});
        }
    }
    return value;
}


SVector operator+(const SVector& x, const SVector& y) {
    if (x.length != y.length) {
        throw logic_error("Can only add vectors of the same size.");
    }

    SVector z;
    z.length = x.length;
    DType a;
    DType b;

    for (UInt i=0; i < x.length; i++) {
        a = 0;
        b = 0;
        if ((x.values.find({0, i}) != x.values.end())) {
            a = x.values.at({0, i});
        }

        if ((y.values.find({0, i}) != y.values.end())) {
            b = y.values.at({0, i});
        }

        z.values[{0, i}] = a + b;
    }
    return z;
}


void SVector::printToBinaryFile(const char* file, const char* printType) {
    ofstream f(file, ios::binary);

        char zero = 0;
        const char* type1 = "as_col";
        const char* type2 = "as_row";
        if ((strcmp(printType, type1) == 1) && (strcmp(printType, type2) == 1)) {
            throw logic_error("Invalid print type! Can only choose between 'as_col' and 'as_row'");
        }
        for (UInt pos=0; pos < SVector::length; pos++) {
            if (SVector::values.find({0, pos}) != SVector::values.end()) {
                f.write((char*)&SVector::values.at({0, pos}), sizeof(DType));
            }
            else {
                f.write(&zero, sizeof(DType));
            }

            if (strcmp(printType, type1) == 0) {
                f.put('\n');
            }
            else if (strcmp(printType, type2) == 0) {
                f.put('\0');
            }
        }

    f.close();
}


void SVector::inputFromBinaryFile(const char* file) {
    ifstream f(file, ios::binary);

    DType value;
    UInt pos = 0;
    while (!f.eof()){
        f.read((char*)&value, sizeof(DType));
        f.ignore(1);

        if (value != 0) {
            SVector::values[{0, pos}] = value;
        }
        pos++;
    }
    SVector::length = pos;
    f.close();
}


void SMatrix::inputFromConsole(UInt rows, UInt cols, const char* inputType) {
    SMatrix::rows = rows;
    SMatrix::cols = cols;

    const char* type1 = "as_row";
    const char* type2 = "as_table";
    // якщо вказаний тип "as_row", то всі значення вводяться одним рядком
    if (strcmp(inputType, type1) == 0) {
        printf("Enter matrix as a row(length = %u): ", rows*cols);

        DType value;
        for (UInt i=0; i < cols; i++) {
            for (UInt j=0; j < rows; j++) {
                scanf("%lf", &value);
                if (value != 0) {
                    SMatrix::values[{i, j}] = value;
                }
            }
        }
    }
    // якщо вказаний тип "as_table", то всі значення вводяться по рядкам, в 
    // залежності від вказаної кількості рядків
    else if (strcmp(inputType, type2) == 0) {
        printf("Enter matrix as a table: \n");

        DType value;
        for (UInt i=0; i < cols; i++) {
            printf("Enter %u row(length = %u): ", i+1, cols);
            for (UInt j=0; j < rows; j++) {
                scanf("%lf", &value);
                if (value != 0) {
                    SMatrix::values[{i, j}] = value;
                }
            }
            cin.clear();
        }
    }
    else {
        throw logic_error("Invalid input type! Can only choose between 'as_row' and 'as_table'");
    }
}


void SMatrix::printToConsole(UInt newCols, UInt precision) {
    if (SMatrix::cols*SMatrix::rows % newCols != 0) {
        throw logic_error("Matrix can't be displayed at this size.");
    } 

    UInt colsCounter = 0;
    for (UInt i=0; i < SMatrix::rows; i++) {
        for (UInt j=0; j < SMatrix::cols; j++) {
            if (SMatrix::values.find({i, j}) != SMatrix::values.end()) {
                DType value = SMatrix::values.at({i, j});
                printf("%.*lf ", precision, value);
            }
            else {
                // задля вирівнювання використовується значення precision
                // при виводі нулів
                printf("%-*u ", precision+2, 0);
            }
            colsCounter++;
            
            if (colsCounter % newCols == 0) {
                printf("\n");
            }
        }
    }
}


SMatrix operator+(const SMatrix& x, const SMatrix& y) {
    if (x.cols != y.cols || x.rows != x.rows) {
        throw logic_error("Matrices must have the same size.");
    }

    SMatrix z;
    z.rows = x.cols;
    z.cols = x.cols;

    // до кінцевої матриці спочатку додаються значення з першої матриці,
    // а потім з другої матриці
    for (auto& elementPairX : x.values) {
        DType el1 = elementPairX.second;
        DType el2 = 0;
        if (y.values.find(elementPairX.first) != y.values.end()) {
            el2 = y.values.at(elementPairX.first);
        }
        z.values[elementPairX.first] = el1 + el2;
    }

    for (auto& elementPairY : y.values) {
        DType el1 = 0;
        DType el2 = elementPairY.second;
        if (x.values.find(elementPairY.first) != x.values.end()) {
            el1 = x.values.at(elementPairY.first);
        }
        z.values[elementPairY.first] = el1 + el2;
    }

    return z;
}


SMatrix operator*(const SMatrix& x, const SMatrix& y) {
    if (x.cols != y.rows || x.rows != y.cols) {
        throw logic_error("Invalid sizes of matrices to multiply.");
    }

    SMatrix z;
    z.rows = x.rows;
    z.cols = y.cols;

    UInt rowNumber = 0;
    for (auto& elementPairX : x.values) {
        rowNumber = elementPairX.first[0];

        for (UInt col=0; col < y.cols; col++) {

            if (y.values.find({elementPairX.first[1], col}) != y.values.end()) {
                z.values[{rowNumber, col}] += 
                elementPairX.second * y.values.at({elementPairX.first[1], col});
            }
        }
    }

    return z;
}


SVector SMatrix::multByVector(const SVector& x) {
    if (SMatrix::cols != x.length) {
        throw logic_error("Can't multiply by vector of this length.");
    }

    SVector y;
    y.length = SMatrix::rows;

    UInt rowNumber = 0;
    for (auto& elementPair : SMatrix::values) {
        rowNumber = elementPair.first[0];
        if (x.values.find({0, elementPair.first[1]}) != x.values.end()) {
            y.values[{0, rowNumber}] += elementPair.second * 
            x.values.at({0, elementPair.first[1]});
        }
    }

    return y;
}


void SMatrix::swapColumns(UInt col1, UInt col2) {
    DType el1;
    DType el2;

    col1--;
    col2--;

    for (UInt i=0; i < SMatrix::rows; i++) {
        el1 = SMatrix::values[{i, col1}];
        el2 = SMatrix::values[{i, col2}];

        if (el1 != 0) {
            SMatrix::values[{i, col2}] = el1;
        }
        else {
            SMatrix::values.erase({i, col2});
        }

        if (el2 != 0) {
            SMatrix::values[{i, col1}] = el2;
        }
        else {
            SMatrix::values.erase({i, col1});
        }
    }
}


void SMatrix::swapRows(UInt row1, UInt row2) {
    DType el1;
    DType el2;

    row1--;
    row2--;

    for (UInt j=0; j < SMatrix::cols; j++) {
        el1 = SMatrix::values[{row1, j}];
        el2 = SMatrix::values[{row2, j}];

        if (el1 != 0) {
            SMatrix::values[{row2, j}] = el1;
        }
        else {
            SMatrix::values.erase({row2, j});
        }

        if(el2 != 0) {
            SMatrix::values[{row1, j}] = el2;
        }
        else {
            SMatrix::values.erase({row1, j});
        }
    }
}


void SMatrix::printToBinaryFile(const char* file, const char* printType) {
    ofstream f(file, ios::binary);

    char zero = 0;
    const char* type1 = "as_row";
    const char* type2 = "as_col";
    if ((strcmp(printType, type1) == 1) && (strcmp(printType, type1) == 1)) {
        throw logic_error("Invalid print type! Can only choose between 'as_row' and 'as_col'");
    }
    for (UInt i=0; i < SMatrix::rows; i++) {
        for (UInt j=0; j < SMatrix::cols; j++) {
            if (SMatrix::values.find({i, j}) != SMatrix::values.end()) {
                f.write((char*)&SMatrix::values.at({i, j}), sizeof(DType));
            }
            else {
                f.write(&zero, sizeof(DType));
            }

            if (printType == type1) {
                f.put('\n');
            }
            else {
                f.put('\0');
            }
        }
    }

    f.close();
}


void SMatrix::inputFromBinaryFile(const char* file, UInt rows, UInt cols) {
    ifstream f(file, ios::binary);

    DType value;
    UInt rowNumber = 0;
    UInt colNumber = 0;

    while (!f.eof()){
        if (rowNumber == rows) {
            break;
        }
        
        f.read((char*)&value, sizeof(DType));
        f.ignore(1);

        if (value != 0) {
            SMatrix::values[{rowNumber, colNumber}] = value;
        }

        colNumber++;
        if (colNumber == cols) {
            colNumber = 0;
            rowNumber++;
        }
    }
    SMatrix::rows = rows;
    SMatrix::cols = cols;

    f.close();
}


void SMatrix::printToTextFile(const char* file) {
    ofstream f(file);

    for (UInt i=0; i < SMatrix::rows; i++) {
        for (UInt j=0; j < SMatrix::cols; j++) {
            DType value = SMatrix::values[{i, j}];
            f << value;

            if (i != SMatrix::rows - 1 || j != SMatrix::cols - 1) {
                f << " ";
            }
        }
    }
    f.close();
}


void SMatrix::inputFromTextFile(const char* file, UInt rows, UInt cols) {
    ifstream f(file);

    DType value;
    UInt rowNumber = 0;
    UInt colNumber = 0;

    while (!f.eof()) {
        if (rowNumber == rows) {
            break;
        }

        f >> value;
        if (value != 0) {
            SMatrix::values[{rowNumber, colNumber}] = value;
        }
        
        colNumber++;
        if (colNumber == cols) {
            rowNumber++;
            colNumber = 0;
        }
    }
    SMatrix::rows = rows;
    SMatrix::cols = cols;

    f.close();
}


DType SMatrix::determinant(MType matrix, UInt size) {
    if (size == 2) {
        DType el1 = matrix[{0, 0}];
        DType el2 = matrix[{0, 1}];
        DType el3 = matrix[{1, 0}];
        DType el4 = matrix[{1, 1}];
        return el1 * el4 - el2 * el3;
    }

    int sign = 1;
    DType result = 0;

    for (UInt col=0; col < size; col++) {
        DType value = matrix[{0, col}];

        if (value != 0) {
            MType minor;

            for (auto& elementPair : matrix) {
                UInt currentRow = elementPair.first[0];
                UInt currentCol = elementPair.first[1];
                if (currentRow != 0 &&
                currentCol != col) {
                    minor[{currentRow-1, currentCol > col ? currentCol - 1 : currentCol}] = 
                    elementPair.second;
                }
            }

            result += sign * value * SMatrix::determinant(minor, size-1);
        }
        sign = -sign;
    }

    return result;
}


DType SMatrix::determinant() {
    DType result = SMatrix::determinant(SMatrix::values, SMatrix::rows);

    return result;
}


SMatrix SMatrix::inverse() {
    if (SMatrix::cols != SMatrix::rows) {
        throw logic_error("Only square matrices have inverse.");
    }

    UInt size = SMatrix::rows;
    DType det = SMatrix::determinant();

    if (det == 0) {
        printf("Matrix is singular, can't find inverse.");
        return SMatrix();
    }
    SMatrix inverseMatrix;
    inverseMatrix.rows = SMatrix::rows;
    inverseMatrix.cols = SMatrix::cols;

    MType minor;
    for (UInt row=0; row < size; row++) {
        for (UInt col=0; col < size; col++) {
            UInt minorRow = 0;
            UInt minorCol = 0;
            for (UInt k=0; k < size*size; k++) {

                if (minorRow != row && minorCol != col) {
                    minor[{minorRow - (minorRow > row), minorCol - (minorCol > col)}] = 
                    SMatrix::values[{minorRow, minorCol}];
                }

                minorCol++;
                if (minorCol == size) {
                    minorRow++;
                    minorCol = 0;
                }
            }

            DType minorDet = determinant(minor, size - 1);
            int sign = (row + col) % 2 == 0 ? 1 : -1;
            if (minorDet != 0) {
                inverseMatrix.values[{col, row}] = sign*minorDet / det;
            }
        }
    
    }

    return inverseMatrix;
}

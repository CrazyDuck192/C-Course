// Задача №1 "Smatrix"
// 2 курс, комп'ютерна математика 2, Пузанов Павло
// Заголовний файл з визначенням власних типів даних

#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <map>
#include <array>

typedef unsigned int UInt;

typedef double DType;

typedef std::array<UInt, 2> Coords;

typedef std::map<Coords, DType> MType;

#endif 
//Aqui se haran las definiciones de lo usado
#ifndef PROYECT_HPP
#define PROYECT_HPP
#include <iostream>
using namespace std;
struct Pregunta{
    string pregunta;
    string respuesta1;
    string respuesta2;
    string respuesta3;
    string respuesta4;
    string correcta;
    int puntaje;
};
struct Materia{
    string nombre;
    Pregunta preguntas[5];
};
struct Nodo{
    Pregunta pregunta;
    Nodo* siguiente;
    Nodo* anterior;
};//porque va a ser una lista doblemente enlazada
void menu();
bool agregarExamen();
#endif
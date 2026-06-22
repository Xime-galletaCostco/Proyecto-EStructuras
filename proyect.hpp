//Aqui se haran las definiciones de lo usado
#ifndef PROYECT_HPP
#define PROYECT_HPP
#include <iostream>
#include <string.h>
using namespace std;
struct Pregunta{
    char pregunta[50];
    char respuesta1[50];
    char respuesta2[50];
    char respuesta3[50];
    char respuesta4[50];
    char correcta[50];
    int puntaje;
};
struct Nodo{
    Pregunta pregunta;
    Nodo* siguiente;
    Nodo* anterior;
};//porque va a ser una lista doblemente enlazada
typedef Nodo* pNodo;
void menu();
bool agregarExamen();
void cargarLista(strinng materiaTitulo,pNodo &raiz);
void agregarNodo(pNodo &raiz,struct Pregunta aux);
#endif

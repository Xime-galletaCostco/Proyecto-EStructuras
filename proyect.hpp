//Aqui se haran las definiciones de lo usado
#ifndef PROYECT_HPP
#define PROYECT_HPP
#include <iostream>
#include <string.h>
#include<string>
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
    bool yaRespondio;
};//porque va a ser una lista doblemente enlazada
typedef Nodo* pNodo;
void menu();
void  agregarExamen();
void cargarLista(string materiaTitulo,pNodo&raiz);
void agregarNodo(pNodo &raiz,struct Pregunta aux);
void aplicarExamen(pNodo &raiz,int suma);
void guardarLista(string materia, pNodo raiz);
void liberarLista(pNodo &raiz);
void modificarExamen();
void  cargarPuntaje(pNodo raiz,int &contador,int &suma);
#endif

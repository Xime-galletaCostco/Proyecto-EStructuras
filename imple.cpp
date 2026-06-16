//--aqui se pone la impolementacion
#include "proyect.hpp"
void menu(){
    cout<<"-----------------------MENU-----------------------"<<endl;
    cout<<"Agregar un nuevo examen---------------------------1"<<endl;
    int opc;
    cin>>opc;
    switch (opc)
    {
    case 1:
        //Se agrega nuevo examen
        agregarExamen();
        break;
    
    default:
        break;
    }
}
bool agregarExamen(){
    system("cls");
    FILE*archivo;
    Materia aux;
    archivo=fopen("examenes.data","ab");
    if(archivo==NULL){
        cout<<"Error al abrir el archivo"<<endl;
        return false;
    }
    cout<<"-------------------CREAR EXAMEN-------------------"<<endl;
    cout<<"Escriba el nombre de la materia: "<<endl;
    cin>>aux.nombre;
    cout<<"Cada pregunta contara con 4 respuestas,"<<endl;
    cout<<"de las cuales solo una es correcta"<<endl;
    for(int i=0;i<5;i++){
        cout<<"Escriba la pregunta "<<i+1<<": "<<endl;
        cin>>aux.preguntas[i].pregunta;
    }
    
    return true;
}
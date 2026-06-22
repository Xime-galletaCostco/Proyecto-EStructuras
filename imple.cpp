//--aqui se pone la impolementacion
#include "proyect.hpp"
void menu(){
    cout<<"-----------------------MENU-----------------------"<<endl;
    cout<<"Agregar un nuevo examen---------------------------1"<<endl;
    cout<<"Modificar reactivos de un examen------------------2"<<endl;
    cout<<"Aplicar un examen---------------------------------3"<<endl;
    cout<<"Salir---------------------------------------------4"<<endl;
    int opc;
    string materiaTitulo;
    FILE*arch;
    cin>>opc;
    switch (opc)
    {
    case 1:
        //Se agrega nuevo examen
        agregarExamen();
        break;
    case 2:
        //aplicar el examen osea usar la lista enlazada doble
        cout<<"Escriba el nombre de la materia de la que quiere aplicar el examen"<<endl;
        cin>>materiaTitulo;
        materiaTitulo=materiaTitulo+".data";
        arch=fopen(materiaTitulo.c_str(),"rb");
        if(arch==NULL){
            cout<<" No se encontro el examen a aplicar, asegurese que escribio el nombre correcto o que el examen existe"<<endl;
        }
        else{
            cout<<"Si se encontro el examen.Preparese para tomarlo.........";
             fclose(arch);
              pNodo raiz=NULL;
        cargarLista(materiaTitulo,raiz);
        //ya esta aqui raiz apuntando
        }
        break;
    case 3:
    break;
    case 4: cout<<"Saliendo.....";
    break;
    default:
        break;
    }
}
bool agregarExamen(){
    system("cls");
    FILE*archivo;
    struct Pregunta aux;
    string nombre;
    string auxiliar;
    cout<<"-------------------CREAR EXAMEN-------------------"<<endl;
    cout<<"Escriba el nombre de la materia: "<<endl;
    cin.ignore();
    getline(cin,auxiliar);
    nombre=auxiliar +".data";
    archivo=fopen(nombre.c_str(),"ab");
    if(archivo==NULL){
        cout<<"Error al abrir el archivo"<<endl;
        return false;
    }
    cout<<"Cada pregunta contara con 4 respuestas,"<<endl;
    cout<<"de las cuales solo una es correcta"<<endl;
    for(int i=0;i<5;i++){
        cout<<"Escriba la pregunta "<<i+1<<": "<<endl;
        cin.getline(aux.pregunta,50,'\n');
        cout<<"Escriba la respuesta CORRECTA"<<endl;
        cin>>aux.correcta;
        cin.ignore();
        cout<<"Escriba el puntaje de la pregunta"<<endl;
        cin>>aux.puntaje;
        cin.ignore();
        cout<<"Escriba las otras respuestas disponibles, esas seran las incorrectas"<<endl;
            cout<<"Respuesta uno"<<endl;
            cin.getline(aux.respuesta1,50,'\n');
            cout<<"Respuesta dos"<<endl;
            cin.getline(aux.respuesta2,50,'\n');
            cout<<"Respuesta tres"<<endl;
            cin.getline(aux.respuesta3,50,'\n');
        fwrite(&aux,sizeof(struct Pregunta),1,archivo);
    }
    //para este punto ya se puede crear el examen y el archivo con el nombre de la materia y se tienen registradas las preguntas del examen
    //no hay lista enlzada eso ya solo esta en modificar
   fclose(archivo);
    return true;
}
void cargarLista(string materiaTitulo,pNodo &raiz){
    //Aqui se supone que ya se confirma que existe el archivo con los registros y forzozamente todos tienen el mismo numero de preguntas
    FILE*arch;
    raiz=NULL;
    struct Pregunta aux;
    arch=fopen(materiaTitulo.c_str(),"rb");
    if(arch==NULL){
        cout<<"No se pudo abrir el examen";
        return;
    }

    while(fread(&aux,sizeof(struct Pregunta),1,arch)==1){
        agregarNodo(raiz,aux);
    }
    fclose(arch);
    //en este punto ya esta la lista y el de raiz para que te empiezes a mover
}
//aqui vamos a poner todo lo relacionado con una lista doble enlazada
void agregarNodo(pNodo &raiz,struct Pregunta aux){
    pNodo nuevo;
    nuevo=new Nodo;
    nuevo->pregunta=aux;
    if(raiz==NULL){
        //osea que lista vacia
        nuevo->anterior=nuevo;
        nuevo->siguiente=nuevo;
        raiz=nuevo;
        return;
    }
    else{
    nuevo->siguiente = raiz;
    nuevo->anterior = raiz->anterior;
    raiz->anterior->siguiente = nuevo;
    raiz->anterior = nuevo;
    raiz = nuevo;
        return;
    }
}
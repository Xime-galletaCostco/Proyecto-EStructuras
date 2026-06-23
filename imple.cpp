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
    archivo=fopen(nombre.c_str(),"wb");
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
        cin.ignore();
        cin.getline(aux.correcta,50,'\n');
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
            cout<<"Respuesta cuatro"<<endl;
            cin.getline(aux.respuesta4,50,'\n');
            
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
void aplicarExamen(pNodo &raiz){
    pNodo aux=raiz;
    char respuesta[50];
    int total =0;
    if(raiz==NULL){
        cout<<"No hay preguntas"<<endl;
        return;
    }
    do{
        cout<<"\nPregunta:"<<endl;
        cout<<aux->pregunta.pregunta<<endl;
        cout<<"1)"<<aux->pregunta.respuesta1<<endl;
        cout<<"2)"<<aux->pregunta.respuesta2<<endl;
        cout<<"3)"<<aux->pregunta.respuesta3<<endl;
        cout<<"4)"<<aux->pregunta.respuesta4<<endl;
        cout<<"Respuesta: ";
        cin.getline(respuesta,50);
        if(strcmp(respuesta,aux->pregunta.correcta)==0){
            total+=aux->pregunta.puntuaje;
        }
        aux=aux->siguiente;
    }while(aux!=raiz);
    cout<<"Puntuaje final: "<<total<<endl;
}
void guardarLista(string materia, pNodo raiz){
    FILE *arch= fopen(materia.c_str(),"wb");
    if(arch==NULL){
        cout<<"ERROR al abrir archivo"<<endl;
        return;
    }
    if(raiz!=NULL){
        pNodo=raiz;
        do{
            fwrite=(&aux->pregunta,sizeof(Pregunta),1,arch);//guarda cada nodo en el archivo 
            aux=aux->siguiente;
        }while(aux!=raiz);//recorre la lista 
    }
    fclose(arch);
    cout<<"Cambios guardados correctamente"<<endl;
}
void liberarLista(pNodo &raiz){
    if(raiz==NULL){
        return;
    }
    pNodo actual=raiz;
    pNodo borrar;
    do{
        borrar=actual;
        actual=actual->siguiente;
        delete borrar;
    }while(actual!=raiz)
        raiz=NULL;
    
}
void modificarExamen(){
    string materia;
    cout<<"Materia del examen:";
    cin>>materia;
    materia=materia +".data";
    FILE *arch=fopen(materia.c_str(),"rb");
    if(arch == NULL){
        cout<<"No existe el examen"<<endl;
        return;
    }
    fclose(arch);
    pNodo raiz=NULL;
    cargarLista(materia,raiz);
    pNodo actual=raiz;
    char opc;
    if(raiz==NULL){
        cout<<"No hay preguntas"<<endl;
        return;
    }
    do{
        cout<<"\nPREGUNTA ACTUAL:\n";
        cout<<actual->pregunta.pregunta<<endl;
        cout<<"1) "<<actual->pregunta.respuesta1<<endl;
        cout<<"2) "<<actual->pregunta.respuesta2<<endl;
        cout<<"3) "<<actual->pregunta.respuesta3<<endl;
        cout<<"4) "<<actual->pregunta.respuesta4<<endl;
        cout<<"Respuesta correcta: "<<actual->pregunta.correcta<<endl;
        cout<<"Puntuaje: "<<actual->puntuaje<<endl;
        cout<<"\nOpciones:\n";
        cout<<"n:siguiente\n";
        cout<<"a:anterior\n";
        cout<<"m:modificar\n";
        cout<<"s:salir\n";
        cin>>opc;
        cin.ignore();
        if(opc=='n'){
            actual=actual->siguiente;
        }else if(opc=='a'){
            actual=actual->anterior;
        }else if(opc=='m'){
            cout<<"Nueva pregunta: ";
            cin.getline(actual->pregunta.pregunta,50);
            cout<<"Respuesta 1: ";
            cin.getline(actual->pregunta.respuesta1,50);
            cout<<"Respuesta 2: ";
            cin.getline(actual->pregunta.respuesta2,50);
            cout<<"Respuesta 3: ";
            cin.getline(actual->pregunta.respuesta3,50);
            cout<<"Respuesta 4: ";
            cin.getline(actual->pregunta.respuesta4,50);
            cout<<"Respuesta Correcta: ";
            cin.getline(actual->pregunta.correcta,50);
            cout<<"Puntuaje: ";
            cin>>actual->pregunta.puntuaje;
            cin.ignore();
        }while(opc!='s');
        guardarLista(materia,raiz);
        liberarLista(raiz);
            
    }
    
    
    

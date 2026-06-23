//--aqui se pone la impolementacion
#include "proyect.hpp"
void menu(){
     int opc=0;
    string materiaTitulo;
    FILE*arch;
    do{
    cout<<"-----------------------MENU-----------------------"<<endl;
    cout<<"Agregar un nuevo examen---------------------------1"<<endl;
    cout<<"Modificar reactivos de un examen------------------2"<<endl;
    cout<<"Aplicar un examen---------------------------------3"<<endl;
    cout<<"Salir---------------------------------------------4"<<endl;
    cin>>opc;
    switch (opc)
    {
    case 1:
        //Se agrega nuevo examen
         agregarExamen();
        break;
    case 2:
        modificarExamen();
    break;
    case 3:
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
        aplicarExamen(raiz);
        }
        break;
    
    case 4: cout<<"Saliendo.....";
    break;
    default:
        break;
    }
}while(opc!=4);}
void agregarExamen(){
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
        return ;
    }
    cout<<"Cada pregunta contara con 4 respuestas,"<<endl;
    cout<<"de las cuales solo una es correcta"<<endl;
    for(int i=0;i<5;i++){
        cout<<"Escriba la pregunta "<<i+1<<": "<<endl;
        cin.getline(aux.pregunta,50,'\n');
        cout<<"Escriba la respuesta CORRECTA"<<endl;
        cin.getline(aux.correcta,50,'\n');
        cout<<"Escriba el puntaje de la pregunta.Use solo numeros"<<endl;
        cin>>aux.puntaje;
        cin.ignore();
        cout<<"Escriba las otras respuestas disponibles, esas seran las incorrectas,menos una,escriba la correcta de nuevo en una opcion"<<endl;
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
    
}
void cargarLista(string materiaTitulo,pNodo&raiz){
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
    nuevo->yaRespondio=false;
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
     if(raiz==NULL){
        cout<<"No hay preguntas"<<endl;
        return;
    }
    pNodo actual=raiz;
    char respuesta[50];
    char opc;
    int total =0;
    cin.ignore();
    while(true){
        system("cls");
         cout<<"\nPregunta:"<<endl;
         cout<<actual->pregunta.pregunta<<endl;
         cout<<"1)"<<actual->pregunta.respuesta1<<endl;
         cout<<"2)"<<actual->pregunta.respuesta2<<endl;
         cout<<"3)"<<actual->pregunta.respuesta3<<endl;
         cout<<"4)"<<actual->pregunta.respuesta4<<endl;
         
            if(!actual->yaRespondio){
            cout<<"Respuesta: ";
            cin.getline(respuesta,50);
            if(strcmp(respuesta,actual->pregunta.correcta)==0){
                total+=actual->pregunta.puntaje;
            }
            actual->yaRespondio=true;
        }
        else{
            cout<<"Esta pregunta ya fue respondida"<<endl;
        }
         cout<<endl<<"-----Opciones disponibles:------"<<endl;
         cout<<"Presione s para siguiente"<<endl;
         cout<<"Presione a para anterior"<<endl;
         cout<<"Si desea salir,presione e de exit"<<endl;
         cin>>opc;
         while(opc!='s'&&opc!='a'&&opc!='e'){
            cout<<"Opcion invalida,intente de nuevo";
            cin>>opc;
         }
         cin.ignore(1000,'\n');
        if(opc=='s'){
            actual=actual->siguiente;
        }
        else if(opc=='a'){
            actual=actual->anterior;
        }
        else if(opc=='e'){
            break;
        }
        
    }
    cout<<"Puntaje final: "<<total<<endl;
    liberarLista(raiz);
}
void guardarLista(string materia, pNodo raiz){
    FILE *arch= fopen(materia.c_str(),"wb");
    pNodo aux;
    if(arch==NULL){
        cout<<"ERROR al abrir archivo"<<endl;
        return;
    }
    if(raiz!=NULL){
        aux=raiz;
        do{
            fwrite(&aux->pregunta,sizeof(Pregunta),1,arch);//guarda cada nodo en el archivo 
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
    pNodo actual = raiz;
    pNodo siguiente;
      do{
         siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }while(actual != raiz);
    raiz = NULL;//aqui se cambio la ufncion ya que la anterior generaba malas implementaciones y memoria suelta para lista doble enlazada
}

void modificarExamen(){
    string materia;
    cout<<"Materia del examen:";
    cin>>materia;
    materia = materia + ".data";
    FILE *arch = fopen(materia.c_str(),"rb");
    if(arch == NULL){
        cout<<"No existe el examen"<<endl;
        return;
    }
    fclose(arch);
    pNodo raiz=NULL;
    cargarLista(materia,raiz);
    if(raiz==NULL){
        cout<<"No hay preguntas"<<endl;
        return;
    }
    pNodo actual=raiz;
    char opc;
    do{
        cout<<"\nPREGUNTA ACTUAL:\n";
        cout<<actual->pregunta.pregunta<<endl;
        cout<<"1) "<<actual->pregunta.respuesta1<<endl;
        cout<<"2) "<<actual->pregunta.respuesta2<<endl;
        cout<<"3) "<<actual->pregunta.respuesta3<<endl;
        cout<<"4) "<<actual->pregunta.respuesta4<<endl;
        cout<<"Respuesta correcta: "<<actual->pregunta.correcta<<endl;
        cout<<"Puntuaje: "<<actual->pregunta.puntaje<<endl;
        cout<<"\nOpciones:\n";
        cout<<"n:siguiente\n";
        cout<<"a:anterior\n";
        cout<<"m:modificar\n";
        cout<<"s:salir\n";
        cin>>opc;
        cin.ignore();
        while(opc !='n'&& opc!= 'm'&& opc!= 's'){
            cout<<"Opcion invalida, intenta otra vez";
            cin>>opc;
        }
        if(opc=='n'){
            actual=actual->siguiente;
        }
        else if(opc=='a'){
            actual=actual->anterior;
        }
        else if(opc=='m'){
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
            cout<<"Puntaje: ";
            cin>>actual->pregunta.puntaje;
            cin.ignore();
        }
    }while(opc!='s');
    guardarLista(materia,raiz);
    liberarLista(raiz);
}

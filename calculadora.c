#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamMax 100
#define Numero '0'
char getTop(char*, char[], int*);
int push(double, double[], int*);
double pop(double[], int*);

int main(int argc, char* argv[]) {
	double pila[tamMax], op2;
	int i, posActPila, posActArgv;
	char c;
	char* op;
	if(argc > 1) { // Mayor que 1 porque el nombre del programa cuenta como argumento
		for(i = 1; i < argc; i++) {
			posActPila = 0;
			posActArgv = 0;
			op = (char*) malloc(sizeof(char));
			while((c = getTop(op, argv[i], &posActArgv)) != '\0') {
				switch (c) {
					case Numero:
						if(argv[i][posActArgv-1] >= '0' && argv[i][posActArgv-1] <= '9' &&  argv[i][posActArgv] == ' ') { // Si pasa esto, significa que leyo un numero valido
							if(push(atof(op), pila, &posActPila) != 0) // Si la funcion no devuelve exito
								return (3);
						}
						else {
							printf("Numero no valido \n");
							return (5);
						}
						break;
					case '+':
						if(posActPila >= 2) { // Si la pila tiene 2 o mas operandos
							if(push(pop(pila, &posActPila) + pop(pila, &posActPila), pila, &posActPila) != 0)
							return (3);
						}
						else {
							printf("Se requieren 2 operandos \n");
							return (2);
						}
						break;
					case '-':
						if(posActPila >= 2) {
							op2 = pop(pila, &posActPila);
							if(push(pop(pila, &posActPila) - op2, pila, &posActPila) != 0)
								return (3);
						}
						else {
							printf("Se requieren 2 operandos \n");
							return (2);
						}
						break;
					case '*':
						if(posActPila >= 2) {
							if(push(pop(pila, &posActPila) * pop(pila, &posActPila), pila, &posActPila) != 0)
								return (3);
						}
						else {
							printf("Se requieren 2 operandos \n");
							return (2);
						}
						break;
					case '/':
						if(posActPila >= 2) {
							op2 = pop(pila, &posActPila); // Extrae el divisor
							if(op2 != 0.0) {
								if(push(pop(pila, &posActPila) / op2, pila, &posActPila) != 0) // Extrae el dividendo, divide y apila
									return (3);
							}
							else {
								printf("Division por 0 \n");
								return (4);
							}
						}
						else {
							printf("Se requieren 2 operandos \n");
							return (2);
						}
						break;
					case ' ':
						break;
					default:
						printf("Caracter no valido \n");
						return (1);
				}
				op = (char*) malloc(sizeof(char));
			}
			free(op);
			posActPila--; // Porque al salir de la funcion push se aumenta en 1 para la proxima entrada
			if(posActPila == 0) // Si el arreglo tiene un solo elemento
				printf("El resultado de la operacion de la calculadora es: %.2f \n", pila[posActPila]); // Fijarme como arreglo esto
			else {
				printf("Operandos no utilizados \n");
				return (7);
			}
		}
	}
	else {
		printf("Uso: ./programa.bin expresión_en_npi [expresión_en_npi [...]] \n");
		return (6);
	}
	return (0);
}


char getTop(char* op, char argv[], int* posActArgv) {
	int i = 0;
	if((argv[*posActArgv] >= '0' && argv[*posActArgv] <= '9') || (argv[*posActArgv] == '-' && argv[*posActArgv+1] != '\0' && argv[*posActArgv+1] != ' ')) { // Si es numero o un signo negativo
		op[i++] = argv[(*posActArgv)++]; // Agrego al vector que almacena el numero
		while(argv[*posActArgv] >= '0' && argv[*posActArgv] <= '9') { // Agrega la parte entera del numero
			op = (char*) realloc(op, strlen(op) + sizeof(char)); // Aumento tamaño de op
			op[i++] = argv[(*posActArgv)++];
		}
		if(argv[*posActArgv] == '.') {
			op = (char*) realloc(op, strlen(op) + sizeof(char)); // Aumento tamaño de op
			op[i++] = argv[(*posActArgv)++];
			while(argv[*posActArgv] >= '0' && argv[*posActArgv] <= '9') {
				op = (char*) realloc(op, strlen(op) + sizeof(char)); // Aumento tamaño de op
				op[i++] = argv[(*posActArgv)++];
			}
		}
		return (Numero);
	}
	else
		return (argv[(*posActArgv)++]); // Devuelve un caracter, pero no encontro un numero valido
}	
	
	
int push(double op, double pila[], int* posActPila) {
	if(*posActPila < tamMax) {
		pila[(*posActPila)++] = op;
		return (0);
	}	
	else
		printf("Pila de operadores desbordada \n");
	return (1);
}


double pop(double pila[], int* posActPila) {
	if(posActPila > 0)
		return(pila[--(*posActPila)]);
	else
		printf("Error, pila vacia \n");
	return (0.0);
}

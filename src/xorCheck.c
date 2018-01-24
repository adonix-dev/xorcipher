/* * * * * * * * * * * * * * * * *
 * Name: Chiffrage XOR     		 *
 * Author: LAGET Antony    		 *
 * Date: 19/01/2018        		 *
 * Description: CheckLibrary     *
 * * * * * * * * * * * * * * * * */
#include "xor.h"

/**
 * [Verification si le caractere est valide pour un message]
 * @inr  	Char 	[caractere a verifier]
 * @return      	[validite du caractere]
 */
int isMessageCharValid(int Char){
	int autorisedChar[256] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0};
	return autorisedChar[Char];
}

/**
 * [Verification si le caractere est valide pour une clef]
 * @param  const char* 	argument  [nom fichier ENTREE]
 * @param  String* 		FileStore [Espace de stockage pour le contenue du fichier]
 * @param  lenth* 		FileLenth [Espace de stockage pour la longueur du fichier]
 * @return           			  [fichier valide]
 */
int checkInFile(const char* argument, String* FileStore, lenth* FileLenth){

	int realloc_size = 100;										//reallocation de l'espace memoire par bloc de 100
	FILE* OpenedFile = NULL;
	String tmpStr = (String)malloc(realloc_size*sizeof(char));	//allocation espace de stockage temporaire
	lenth i = 0;
	int realloc_counter = 0;
	
	
	OpenedFile = fopen(argument, "r");							//Ouverture du fichier en lecture
	
	if (OpenedFile != NULL){

		while (fscanf(OpenedFile, "%c", &(tmpStr[i])) != EOF){	//Lecture caractere par caractere

			if (realloc_counter >= realloc_size)
			{
				tmpStr = (String)realloc(tmpStr, i*realloc_size*sizeof(unsigned char));
				realloc_counter = 0;
			}
			++realloc_counter;
			++i;
		}
		*FileStore = tmpStr;
		*FileLenth = i;
		fclose(OpenedFile);
		return 1;
	}
	free(tmpStr);
	return 0;
}

/**
 * [VERIFICATION DU FICHIER SORTIE ET STOCKAGE DE SON NOM EN MEMOIRE]
 * @param  const char* argument       	[nom du fichier SORTIE]
 * @param  String* outputFileName 		[Espace memoire pour le nom du fichier de sortie]
 * @return int              			[fichier valide]
 */
int checkOutFile(const char* argument, String* outputFileName){

	FILE* OpenedFile = NULL;
	OpenedFile = fopen(argument, "w+");		//Ouverture du fichier en ecriture (cree si n'existe pas)
	if (OpenedFile != NULL){
		*outputFileName = (String)argument;
		fclose(OpenedFile);
		return 1;
	} 
	return 0;
}

/**
 * [Verification si le caractere est valide pour une clef]
 * @param  int Char 	[caractere a verifier]
 * @return int    		[validite du caractere]
 */
int isKeyCharValid(int Char){
	int autorisedKeyChar[126] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1};
	return autorisedKeyChar[Char];
}

/**
 * [VERIFICATION DE LA CLEF ET STOCKAGE EN MEMOIRE]
 * @param  const char* 	inputChar 	[clef entree par l'utilisateur]
 * @param  String* 		key       	[mise en memoire de la clef valide]
 * @return int       				[validite de la clef]
 */
int checkKey(const char* inputChar, String* key){
	
	int autorised = 1, i = 0;

	while((i < (int)strlen(inputChar)) && autorised){

		if(isKeyCharValid(inputChar[i]) && inputChar[i] >= 44) autorised = 1;	//verification si le caratere est valide
		else{autorised = 0;break;}
		i++;
	}

	if (autorised){						// Si la clef est entierement valide 
		*key = (String)inputChar;		// on la stocke en memoire
		return 1;
	}
	return 0;
}

/**
 * [VERIFICATION DU MODE DE CRACKAGE ET STOCKAGE EN MEMOIRE]
 * @param  const char* 	argument 	[mode choisis par l'utilisateur]
 * @param  crackMode* 	mode     	[esapace memoire pour stocker la mode de crac]
 * @return int         				[mode valide]
 */
int checkMode(const char* argument, crackMode* mode){

	//MODEC1, MODEC2, MODE31, MODE32 : cf header
	if((strlen(argument)) == 1 && ((argument[0] == MODEC1) || (argument[0] == MODEC2) || (argument[0] == MODEC3))){
		*mode = argument[0];return 1;
	}
	return 0;
}

/**
 * [VERIFICATION DE LA LONGUEUR DE CLEF ET STOCKAGE EN MEMOIRE]
 * @param  const char* 	argument 	[longueur de la clef rentree par l'utilisateur]
 * @param  lenth* 		keyLenth 	[espace memoire pour stocker la longueur de la clef]
 * @return int        				[longueur de clef valide]
 */
int checkKeyLenth(const char* argument, lenth* keyLenth){

	lenth tmp = strlen(argument);
	int tmpArg; 

	for (lenth i = 1; i <= tmp; ++i)													//pour char cararctere composant la longueur rentree par l'utilisateur
	{
		tmpArg = argument[tmp - (i)];

		if ((tmpArg >= 48 && tmpArg <= 57)) *keyLenth += (int)(tmpArg - 48)*pow(10,i-1); //on le transforme chaque caractere en int et selon son rang on devient une unitee, une dixene, etc
		else return 0;
	}
	return 1;
	
}
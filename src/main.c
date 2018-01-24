/* * * * * * * * * * * * * ** 
 * Name: Chiffrage XOR      *
 * Author: LAGET Antony     *
 * Date: 10/01/2018         *
 * Description: main  		*	
 * * * * * * * * * * * * * **/

/**
 * INCLUTION DU HEADER
 */
#include "xor.h"

/**
 * [main]
 * @param int  		argc 		[nombre d'argument en ligne de commande]
 * @param const 	char*  argv [argument]
 * @param return    int 		[le programme s'est bien execute]
 */

int main(int argc, const char* argv[])
{

    clock_t begin_Time = clock();		// DEMARAGE DU CHRONOMETRE
	
	/**
	 * DECLARATION DE VARIABLES DES PRINCIPALE QUI STOCKE LES ENTREES DE L'UTILISATEUR
	 */
	String 		key 			= NULL; // Stockage de la clef
	crackMode 	mode 			= 0; 	// Stockage du mode
	lenth 		keyLenth 		= 0;	// Stockage longueur de la clef
	String 		inputFile 		= NULL;	// Stockage du fichier "entree"
	lenth 		inputFileLenth 	= 0;	// Stockage de la longueur du fichier "entree"
	String		outputFileName 	= NULL;	// Stockage du nom du fichier "sortie"
	int 		i 				= 1;	// Compteur boucle de lecture des arguments

	//test_script.sh : [  test_command  ] -> [OK]
	
	if (argc%2){ 																// Verification nombre d'argument est pair
		while(i < argc){														
			if (!strcmp("-i",argv[i])){											// Verification de l'option IN
				if(!checkInFile((char*)argv[i+1], &inputFile, &inputFileLenth)) // VERIFICATION DU FICHIER ENTREE ET STOCKATGE EN MEMOIRE DE SON CONTENUE ET DE SA LONGUEUR
					printf("Input File 	: \e[00;31mERROR : file\e[00m\n");
			}
			else if(!strcmp("-o",argv[i])){										// Verification de l'option OUT
				if(!checkOutFile((char*)argv[i+1], &outputFileName)) 			// VERIFICATION DU FICHIER SORTIE ET STOCKAGE DE SON NOM EN MEMOIRE
					printf("Output File 	: \e[00;31mERROR : file\e[00m\n");
			}
			else if(!strcmp("-k",argv[i])){										// Verification de l'option CLEF
				if (!checkKey((char*)argv[i+1], &key)) 							// VERIFICATION DE LA CLEF ET STOCKAGE EN MEMOIRE
					printf("Key 		: \e[00;31mERROR : key\e[00m\n");
			}
			else if (!strcmp("-m",argv[i])){									// Verification de l'option MODE
				if (!checkMode((char*)argv[i+1], &mode)) 						// VERIFICATION DU MODE ET STOCKAGE EN MEMOIRE
					printf("\e[00;31mERROR : command line\e[00m\n");
			}	
			else if (!strcmp("-l",argv[i])){									// Verification de l'option LONGUEUR DE CLEF
				if (!checkKeyLenth((char*)argv[i+1], &keyLenth)) 				// VERIFICATION DE LA LONGUEUR DE CLEF ET STOCKAGE EN MEMOIRE
					printf("\e[00;31mERROR : command line\e[00m\n");
			}
			else{
				printf("\e[00;31mERROR:command line\e[00m\n");					// ERREURS
				exit(-1);
			}
			i+=2;
		}
	}
	else{
		printf("\e[00;31mERROR:command line\e[00m\n");							// ERREUR
		exit(-1);
	} 

	if(!processOption(inputFile, inputFileLenth, outputFileName, key, mode, keyLenth)) exit(-1);	// UTILISATION DES VARIABLE EN MEMOIRE POUR EXECUTER LES ORDRES DE L'UTILISATEUR
	    
	clock_t end_Time = clock();			// ARRET DU CHRONOMETRE
    fprintf(stderr, "%.6f sec\n", (double)(end_Time - begin_Time) / CLOCKS_PER_SEC);// AFFICHAGE TU TEMPS ECOULE SOIT LE TEMPS D'EXECUTION DU PROGRAMME
 	return 0;
}
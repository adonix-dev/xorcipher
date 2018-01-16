/* * * * * * * * * * * * * *
 * Name: Chiffrage XOR     *
 * Author: LAGET Antony    *
 * Date: 10/01/2018        *
 * Description: Header     *
 * * * * * * * * * * * * * */
#ifndef _XOR_H //EVITE L'INCLUTION MULTIPLE
#define _XOR_H

/**
 * IMPORTATION DES LIBRAIRIES EXTERNES
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

/**
 * DEFINITION DE TYPE
 */
typedef unsigned char* String;
typedef int crackMode;
typedef unsigned long lenth;
#define MODEC1 49
#define MODEC2 50
#define MODEC3 51

/**
 * PROTOTYPE DES FONCTIONS UTILISÉ DANS L'ENSEMBLE DU PROGRAMME
 */
// XOR
void 	xorCipher(String input, lenth inputLenth, String key, String* output);		// XORAGE DE L'ENTREE PAR RAPPORT A L'ENTREE

/* 
 * Validation de caracteres
 */
int 	isMessageCharValid(int Char);	// Verification si le caractere est valide pour un message
int 	isKeyCharValid(int Char);		// Verification si le caractere est valide pour une clef

/*
 * Fonctions de verification des entrees utilisateur
 */
int 	checkInFile(const char* argument, String* FileStore, lenth* FileLenth);		// VERIFICATION DU FICHIER ENTREE ET STOCKATGE EN MEMOIRE DE SON CONTENUE ET DE SA LONGUEUR
int 	checkOutFile(const char* argument, String* outputFileName);					// VERIFICATION DU FICHIER SORTIE ET STOCKAGE DE SON NOM EN MEMOIRE
int 	checkKey(const char* argument, String* key);								// VERIFICATION DE LA CLEF ET STOCKAGE EN MEMOIRE
int 	checkMode(const char* argument, crackMode* mode);							// VERIFICATION DU MODE DE CRACKAGE ET STOCKAGE EN MEMOIRE
int 	checkKeyLenth(const char* argument, lenth* keyLenth);						// VERIFICATION DE LA LONGUEUR DE CLEF ET STOCKAGE EN MEMOIRE

/*
 * Fonction d'execution des taches demandees pas l'utilisateur
 */
int 	processOption(String inputFile, lenth inputFileLenth, String outputFileName, String key, crackMode mode, lenth keyLenth); // UTILISATION DES VARIABLE EN MEMOIRE POUR EXECUTER LES ORDRES DE L'UTILISATEUR

////CD
void 	processXOR(String inputFile, lenth inputFileLenth, String outputFileName, String key);		// GESTION CRYPTAGE ET DECRYPTAGE DE FICHIERS

////C1
int 	processC1(String inputFile, lenth inputFileLenth, lenth keyLenth); 		// AVEC LA LONGUEUR DE CLEF
void 	processNoLengthC1(String inputFile, lenth inputFileLenth);				// SANS LA LONGUEUR DE CLEF
// Fonction necessaire a C1
int 	processKeyLengthCrack(String inputFile, lenth inputFileLenth, lenth keyLenth, int* nbOfKeyChar, String* outKeys);		// RENVOIS TOUTES LES CLEF POSSIBLE QUI ASSURE LE DECRYPTAGE EN CARACTERE VALIDES

////C2
int 	processC2(String inputFile, lenth inputFileLenth, lenth keyLenth);		// AVEC LA LONGUEUR DE CLEF
void 	processNoLengthC2(String inputFile, lenth inputFileLenth);				// SANS LA LONGUEUR DE CLEF
// Fonctions necessaires a C2
void 	combine_back(int* nbKeyTreated, int* nbOfKeyChar, int* col, int* line, int* keyLenth, String* key,  String* Keys);		// FONCTION DE PARCOURS DES CARATERES POSSIBLE POUR OBTENIR TOUTE LES COMBINAISONS DE CLEF POSSIBLES
String* combine(int* nbOfKeyChar, int *keyLenth, String* keyChar, int nbOfKeys);												// SON INTERFACE
String* combine_keyChar(lenth keyLenth, int* nbOfKeyChar, String* keysChar, int* nbOfKeys);										// PRE-INTERFACE
void 	frequence_analysis(String inputFile, lenth inputFileLenth, int nbOfKeys, String* Keys);									// ANALYSE FREQUENTIELLE POUR OBTENIR LA CLEF SUI PERMET D'OBTENIR DE LE TEXTE SE RAPPROCHANT AU PLUS DE LA LANGUE FRANCAISE

////C3
int 	processC3(String inputFile, lenth inputFileLenth, lenth keyLenth);														// AVEC LA LONGUEUR DE CLEF
void	processNoLengthC3(String inputFile, lenth inputFileLenth);																// SANS LA LONGUEUR DE CLEF
// Fonctions necessaires a C3
char** 	dictionary_analysis(int* nbOfWords, int maxWordSize);																	// LECTURE DU DICTIONNAIRE ET MISE EN MEMOIRE DES MOT DE LONGUEUR INFERIEURE A 5
void 	dictionary_crack(String inputFile, lenth inputFileLenth, String* Keys, int nbOfKeys, char** small_dict, int nbOfWords, int maxWordSize); // VERIFICATION DE LA PRESENCE DES MOTS DANS LE DICTIONNAIRE FRANCAIS

#endif
/* * * * * * * * * * * * * * * * * *
 * Name: Chiffrage XOR             *
 * Author: LAGET Antony            *
 * Date: 10/01/2018        		   *
 * Description: processor 		   *
 * * * * * * * * * * * * * * * * * */
#include "xor.h"

/**
 * [UTILISATION DES VARIABLE EN MEMOIRE POUR EXECUTER LES ORDRES DE L'UTILISATEUR]
 * @param  String       inputFile       [contenue de fichier ENTREE]
 * @param  lenth        inputFileLenth  [taille de fichier ENTREE]
 * @param  String       outputFileName  [nom fichier SORTIR]
 * @param  String       key             [clef choisie par l'utilisateur]
 * @param  crackMode    mode            [mode choisie par l'utilisateur]
 * @param  lenth        keyLenth        [taille choisie par l'utilisateur]
 * @return int                          [l'ensemble des arguments entree par l'utisateur sont logiques et complets]
 */
int processOption(String inputFile, lenth inputFileLenth, String outputFileName, String key, crackMode mode, lenth keyLenth){

    //(1) Process CD | -i -o -k
	if ((inputFile != NULL) && (outputFileName != NULL) && (key != NULL) && (mode == 0) && (keyLenth == 0))
        //test_script.sh :  [  test_cipher  ] -> [OK]
        //test_script.sh :  [ test_decipher ] -> [OK]
		processXOR(inputFile, inputFileLenth, key, outputFileName);

    //(2) Process C1 avec longueur connue | -i -m -l
    else if((inputFile != NULL) && (outputFileName == NULL) && (key == NULL) && (mode == MODEC1) && ((keyLenth >= 3) && (keyLenth <= 7)))
        //test_crack.sh :   [  crack 1  ] -> [OK]
        processC1(inputFile, inputFileLenth, keyLenth);

    //(3) Process C2 | -i -m
    else if((inputFile != NULL) && (outputFileName == NULL) && (key == NULL) && (mode == MODEC2) && ((keyLenth >= 3) && (keyLenth <= 7)))
        //test_crack.sh :   [  crack 2  ] -> [OK]
        processC2(inputFile, inputFileLenth, keyLenth);
    
    //(4) Process C3 | -i -m -l
    else if((inputFile != NULL) && (outputFileName == NULL) && (key == NULL) && (mode == MODEC3) && ((keyLenth >= 3) && (keyLenth <= 7)))
        processC3(inputFile, inputFileLenth, keyLenth);

    //(5) Process C1 sans longueur precisee | -i -m -l
    else if((inputFile != NULL) && (outputFileName == NULL) && (key == NULL) && (mode == MODEC1) && (keyLenth == 0))
        processNoLengthC1(inputFile, inputFileLenth);

    //(6) Process C2 sans longueur precisee | -i -m
    else if((inputFile != NULL) && (outputFileName == NULL) && (key == NULL) && (mode == MODEC2) && (keyLenth == 0))
        processNoLengthC2(inputFile, inputFileLenth);

    //(7) Process C3 | -i -m -l
    else if((inputFile != NULL) && (outputFileName == NULL) && (key == NULL) && (mode == MODEC3) && (keyLenth == 0))
        processNoLengthC3(inputFile, inputFileLenth);

    else{
    	printf("ERROR : command line\n");
        return 0;
    }

	return 1;

}

/**
 * [ANALYSE FREQUENTIELLE POUR OBTENIR LA CLEF SUI PERMET D'OBTENIR DE LE TEXTE SE RAPPROCHANT AU PLUS DE LA LANGUE FRANCAISE]
 * @param String    inputFile      
 * @param lenth     inputFileLenth 
 * @param String    key            
 * @param String    outputFileName 
 */
void processXOR(String inputFile, lenth inputFileLenth, String key, String outputFileName){

    String tmp = NULL;
    FILE* outputFile = NULL;

    xorCipher(inputFile, inputFileLenth, key, &tmp);
        
    outputFile = fopen((char*)outputFileName,"w+");
    
    for (lenth i = 0; i < inputFileLenth; ++i) fputc(tmp[i], outputFile);

    fclose(outputFile);

    free(inputFile);
}

/**
 * [processC1 AVEC LA LONGUEUR DE CLEF]
 * @param  String   inputFile     
 * @param  lenth    inputFileLenth
 * @param  lenth    keyLenth      
 * @return 
 */
int processC1(String inputFile, lenth inputFileLenth, lenth keyLenth){

    String* outKeys = (String*)malloc(keyLenth*sizeof(int*));
    int* nbOfKeyChar = malloc(keyLenth*sizeof(int));
    
    if(processKeyLengthCrack(inputFile,inputFileLenth,keyLenth,nbOfKeyChar,outKeys)){
        for (lenth i = 0; i < keyLenth; ++i)
        {
            printf("[");
            for (int j = 0; j < nbOfKeyChar[i]; ++j) printf("%c", outKeys[i][j]);
            printf("]");
        }
        printf("\n");
        free(outKeys);
        free(nbOfKeyChar);
        return 1;
    } 
    free(outKeys);
    free(nbOfKeyChar);
    return 0;
}

/**
 * [processNoLengthC1 SANS LA LONGUEUR DE CLEF]
 * @param String    inputFile      
 * @param lenth     inputFileLenth 
 */
void processNoLengthC1(String inputFile, lenth inputFileLenth){

    for (lenth keyLenth = 3; keyLenth <= 7; ++keyLenth) processC1(inputFile,inputFileLenth,keyLenth);
}

/**
 * [processC2 AVEC LA LONGUEUR DE CLEF]
 * @param  String   inputFile     
 * @param  lenth    inputFileLenth
 * @param  lenth    keyLenth      
 * @return               
 */
int processC2(String inputFile, lenth inputFileLenth, lenth keyLenth){

    String* keysChar = (String*)malloc(keyLenth*sizeof(int*));
    int* nbOfKeyChar = malloc(keyLenth*sizeof(int));
    int nbOfKeys;
    
    if(processKeyLengthCrack(inputFile, inputFileLenth, keyLenth, nbOfKeyChar, keysChar)){

        String* Keys = combine_keyChar(keyLenth, nbOfKeyChar, keysChar, &nbOfKeys);

        frequence_analysis(inputFile, inputFileLenth, nbOfKeys, Keys);

        for (int i = 0; i < nbOfKeys; ++i) free(Keys[i]);
        free(Keys);
        free(keysChar);
        free(nbOfKeyChar);
        return 1;
    }
    free(keysChar);
    free(nbOfKeyChar);
    return 0;
}

/**
 * [processNoLengthC2 SANS LA LONGUEUR DE CLEF]
 * @param String    inputFile     
 * @param lenth     inputFileLenth
 */
void processNoLengthC2(String inputFile, lenth inputFileLenth){

    for (lenth keyLenth = 3; keyLenth <= 7; ++keyLenth) processC2(inputFile,inputFileLenth,keyLenth);

}

/**
 * [processC3 AVEC LA LONGUEUR DE CLEF]
 * @param  String   inputFile     
 * @param  lenth    inputFileLenth
 * @param  lenth    keyLenth      
 * @return int          
 */
int processC3(String inputFile, lenth inputFileLenth, lenth keyLenth){

    String* keysChar = (String*)malloc(keyLenth*sizeof(int*));
    int* nbOfKeyChar = malloc(keyLenth*sizeof(int));
    int nbOfKeys;
    int nbOfWords = 0;
    int maxWordSize = 4; // Consigne

    if(processKeyLengthCrack(inputFile, inputFileLenth, keyLenth, nbOfKeyChar, keysChar)){

        String* Keys = combine_keyChar(keyLenth, nbOfKeyChar, keysChar, &nbOfKeys);

        char** small_dict = dictionary_analysis(&nbOfWords, maxWordSize);
        
        dictionary_crack(inputFile, inputFileLenth, Keys, nbOfKeys, small_dict, nbOfWords, maxWordSize);

        for (int i = 0; i < nbOfKeys; ++i) free(Keys[i]);
        free(Keys);
        free(keysChar);
        free(nbOfKeyChar);
        return 1;
    }
    free(keysChar);
    free(nbOfKeyChar);
    return 0;
}

/**
 * [processNoLengthC3 SANS LA LONGUEUR DE CLEF]
 * @param String    inputFile     
 * @param lenth     inputFileLenth
 */
void processNoLengthC3(String inputFile, lenth inputFileLenth){

    for (lenth keyLenth = 3; keyLenth <= 7; ++keyLenth) processC3(inputFile,inputFileLenth,keyLenth);

}


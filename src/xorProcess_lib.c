/* * * * * * * * * * * * * * * * * *
 * Name: Chiffrage XOR             *
 * Author: LAGET Antony            *
 * Date: 10/01/2018        		   *
 * Description: processorLibrary   *
 * * * * * * * * * * * * * * * * * */
#include "xor.h"

/**
 * [RENVOIS TOUTES LES CLEF POSSIBLE QUI ASSURE LE DECRYPTAGE EN CARACTERE VALIDES]
 * @param  String   inputFile  
 * @param  lenth    inputLenth 
 * @param  lenth    keyLenth   
 * @param  int*     nbOfKeyChar
 * @param  String*  outKeys    
 * @return int                 
 */
int processKeyLengthCrack(String inputFile, lenth inputLenth, lenth keyLenth, int* nbOfKeyChar, String* outKeys){

    int k, validChar, tmpChar, l, xored;

    lenth currentCharPos;

    for (lenth i = 0; i < keyLenth; ++i){
        
        outKeys[i] = (String)malloc(70*sizeof(unsigned char));
        l = 0;
        for (int keyChar = 0; keyChar < 126; ++keyChar) 

            if (isKeyCharValid(keyChar)){
                currentCharPos = i;
                k = 0;
                validChar = 0;
                tmpChar = 0;

                while(currentCharPos < inputLenth){

                    xored = inputFile[currentCharPos]^keyChar;

                    if (isMessageCharValid(xored)){
                    	validChar = 1;
                        tmpChar = keyChar;
                    }
                    else{
                        validChar = 0;
                        break;
                    }

                    currentCharPos = i + keyLenth*k; 
                    ++k;
                }
                if (validChar){
                    outKeys[i][l] = tmpChar;               
                    ++l;
                }
            }

        if (!l) return 0;
        else nbOfKeyChar[i] = l; 

    }
    return 1;

}

/**
 * [FONCTION DE PARCOURS DES CARATERES POSSIBLE POUR OBTENIR TOUTE LES COMBINAISONS DE CLEF POSSIBLES]
 * @param int*      nbKeyTreated
 * @param int*      nbOfKeyChar 
 * @param int*      col         
 * @param int*      line        
 * @param int*      keyLenth    
 * @param String*   key         
 * @param String*   Keys        
 */
void combine_back(int* nbKeyTreated, int* nbOfKeyChar, int* col, int* line, int* keyLenth, String* key,  String* Keys){

	for(int i = 0; i < nbOfKeyChar[*col]; i++){
		line[*col] = i;
		if (*col >= *keyLenth - 1){
			for(int k = 0; k < *keyLenth; k++) Keys[*nbKeyTreated][k] = key[k][line[k]];
		 	*nbKeyTreated += 1;	
		}
		else{
			*col += 1;
			combine_back(nbKeyTreated, nbOfKeyChar, col, line, keyLenth, key, Keys);		
		}
	}
	*col -= 1;
}

/**
 * [INTERFACE DE LA FONCTION combine_back]
 * @param  int*     nbOfKeyChar
 * @param  int*     keyLenth   
 * @param  String*  keyChar    
 * @param  int      nbOfKeys   
 * @return int                 
 */
String* combine(int* nbOfKeyChar, int* keyLenth, String* keyChar, int nbOfKeys){

	int nbKeyTreated = 0, col = 0;
	int* line = malloc(*keyLenth*sizeof(int)); 

	String* Keys = (String*)malloc(nbOfKeys*sizeof(int*));
    for(long i = 0; i < nbOfKeys; i++ ) Keys[i] = malloc((*keyLenth)*sizeof(int));

  	combine_back(&nbKeyTreated, nbOfKeyChar, &col, line, keyLenth, keyChar, Keys);
	
	free(line);
  	return Keys;
}

/**
 * [INTERFACE DE combine]
 * @param  lenth    keyLenth   
 * @param  int*     nbOfKeyChar
 * @param  String*  keysChar   
 * @param  int*     nbOfKeys   
 * @return int                     
 */
String* combine_keyChar(lenth keyLenth, int* nbOfKeyChar, String* keysChar, int* nbOfKeys){

	int nbOfKeys_tmp = 1;
	int tmpKeylenth = keyLenth;

    // CALCUL DU NOMBRE DE CLEF POSSIBLE
	for(lenth i = 0; i < keyLenth; i++){
		nbOfKeys_tmp = nbOfKeys_tmp * nbOfKeyChar[i];
	}

	*nbOfKeys = nbOfKeys_tmp;

	return combine(nbOfKeyChar, &tmpKeylenth, keysChar, nbOfKeys_tmp);

}

/**
 * [frequence_analysis description]
 * @param String    inputFile     
 * @param lenth     inputFileLenth
 * @param int       nbOfKeys      
 * @param String*   Keys          
 */
void frequence_analysis(String inputFile, lenth inputFileLenth, int nbOfKeys, String* Keys){

                                                                        // ALPHABET ET LETTRE ACCENTUEES 
    int     bestKey = 0;
    int     currentChar;
    int     basic_alphabet[180] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1};
    float   nbOfLetter;
    float   distance = (float)1000000;
    float   distance_tmp;
    String  decriptedFile = NULL; 

                                                                        // FREQUENCE D'APPARITION DES LETTRES DE L'ALPHABET DANS LA LANGUE FRANCAISE
    float frec_th[26] = {9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.00,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.00,0.30,0.24,0.32}; 

    for (int i = 0; i < nbOfKeys; ++i)
    { 
        float   frec[26] = {0.00};
        nbOfLetter = 0;
        
        xorCipher(inputFile, inputFileLenth, Keys[i], &decriptedFile);

        for (lenth j = 0; j < inputFileLenth; ++j)
        {
            currentChar = decriptedFile[j];

            if (basic_alphabet[currentChar-65] && currentChar>=65){

                //COMPTAGE DU NOMBRE DE CHAQUE LETTRE EN TENANT COMTE DE L'ACCENTUATION
                if (currentChar>=192){                                  

                    if(((currentChar>=200) && (currentChar<=203)) || ((currentChar>=232) && (currentChar<=235))) frec[4] += 1;
                    else if((currentChar==199) || (currentChar==231)) frec[2] += 1;
                    else if((currentChar==206) || (currentChar==207) || (currentChar==238) || (currentChar==239)) frec[8] += 1;
                    else if((currentChar==217) || (currentChar==219) || (currentChar==247) || (currentChar==251)) frec[20] += 1;
                    else if((currentChar==212) || (currentChar==214) || (currentChar==244) || (currentChar==246)) frec[14] += 1;
                    else if((currentChar==192) || (currentChar==194) || (currentChar==196) || (currentChar==224) || (currentChar==226) || (currentChar==228)) frec[0] += 1;
                }
                 
                else if (((currentChar>=65) && (currentChar<=90))) frec[currentChar-65] += 1;
                else if(((currentChar>=97) && (currentChar<=122))) frec[currentChar-97] += 1;
                ++nbOfLetter;
            }

        }

        distance_tmp = 0.00;

        // CALCUL DE LA DISTANCE A LA MOYENE FRANCAISE
        for (int j = 0; j < 26; ++j) distance_tmp += (frec_th[j] - (frec[j]/nbOfLetter))*(frec_th[j] - (frec[j]/nbOfLetter));

        //LE TEXTE QUI RENVOIS LA DISTANCE LA PLUS FAIBLE EST CELUI DONC LA CLEF EST LA BONNE POUR UN FICHER AVEC UN GRAND NIMBRE DE MOTS
        if (distance_tmp < distance){

            distance = distance_tmp;
            bestKey = i;
        }
    }
    printf("%s\n", Keys[bestKey]);

}

/**
 * [LECTURE DU DICTIONNAIRE ET MISE EN MEMOIRE DES MOT DE LONGUEUR INFERIEURE A 5 PAR DEFAULT]
 * @param  int* nbOfWords  
 * @param  int  maxWordSize
 * @return int           
 */
char** dictionary_analysis(int* nbOfWords, int maxWordSize){

    FILE* OpennedFile = NULL;

    OpennedFile = fopen("./sources/fr_dico_lat_1.txt", "r"); 

    char** dictionary = malloc(336530*sizeof(String));

    if (OpennedFile != NULL){
        
        dictionary[0] = malloc(27*sizeof(unsigned char));

        unsigned char tmp;
        unsigned char tmpWord[27];

        int wordLenth = 0;

        while(fscanf(OpennedFile, "%c", &tmp) != EOF){                              // LECTURE DU GRAND DICTIONNAIRE

            if (tmp == 10)
            {
                if (wordLenth <= maxWordSize+1){

                    dictionary[*nbOfWords+1] = malloc(27*sizeof(unsigned char));

                    for (int i = 0; i < wordLenth; ++i) dictionary[*nbOfWords][i] = tmpWord[i]; 

                    dictionary[*nbOfWords][wordLenth] = '\0';
                    *nbOfWords += 1;
                }  
                wordLenth = 0;
                
            }
            else{ if (wordLenth < maxWordSize+1) tmpWord[wordLenth] = tmp; ++wordLenth; } // SI LE MOT A UNE TAILLE QUI EST AU PLUS MAXSIZE ON LE CONSERVE DANS UN PLUS PETIT DICTIONNAIRE
        }

    }
    return dictionary;
    free(dictionary);
}

/**
 * [VERIFICATION DE LA PRESENCE DES MOTS DANS LE DICTIONNAIRE FRANCAIS]
 * @param String    inputFile     
 * @param lenth     inputFileLenth
 * @param String*   Keys          
 * @param int       nbOfKeys      
 * @param char**    small_dict     [dictionnaire de tout les mots d'au plus maxWordSize lettre]
 * @param int       nbOfWords     
 * @param int       maxWordSize    [nombre maximum de lettre des mots du dictionnaire: 4 par default]
 */
void dictionary_crack(String inputFile, lenth inputFileLenth, String* Keys, int nbOfKeys, char** small_dict, int nbOfWords, int maxWordSize){

    int bestKey = 0; 
    int currentletter = 0;
    int nbOfInputWords = 0;
    int nbValidWords = 0;
    int nbValidWords_tmp = 0;
    unsigned char currentChar;
    char tmpStr[27];

    int unvalidChar[94] = {1,1,1,0,0,0,0,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1};                                                                                                                                
    //(currentChar == 32) || (currentChar == 33) || (currentChar == 33)  || (currentChar == 34) || (currentChar == 39) || (currentChar == 40) || (currentChar == 41) || (currentChar == 44) || (currentChar == 46) || (currentChar == 58) || (currentChar == 59) || (currentChar == 63) || (currentChar == 95) || (currentChar == 123) || (currentChar == 125)

    String decriptedFile = NULL; 

    for (int i = 0; i < nbOfKeys; ++i)                                      // PARCOURS DE TOUTE LES CLEF POSSIBLE
    {  
        xorCipher(inputFile, inputFileLenth, Keys[i], &decriptedFile);      // DECRYPTAGE AVEC LA CLEF

        for (lenth j = 0; j < inputFileLenth; ++j)                          // PARCOURS DU CONTENU
        {
            currentChar = decriptedFile[j];
                                                                            // LE CARACTERE N'EST PAS LA PONCTUATION, UN ESPACE OU UN RETOUR CHARIOT
            if (unvalidChar[currentChar-32])
            {   
                    tmpStr[currentletter] = '\0'; 

                    if (currentletter >= 1 && currentletter <= maxWordSize+1) // LE MOT N'EST PAS UN ESPACE ET INFERIEURE A LA TAILLE MAXIMUM, 4 PAR DEFAULT

                        for (int o = 0; o < nbOfWords; ++o)                 // ON PARCOURS LE PETIT DICTIONNAIRE

                            if (!strcmp(small_dict[o], tmpStr))             // ON VERIFIE QUE LE MOT TROUVE EST DE DANS
                            {
                                ++nbValidWords_tmp;
                                nbOfInputWords +=1;
                            }
                            
                    currentletter = 0;
            }
            else{  

                tmpStr[currentletter] = currentChar;
                ++currentletter;
            }
        }
        if (nbValidWords_tmp > nbValidWords)                                   // LE MESSAGE QUI A LE PLUS DE MOT DANS LE DICTIONNAIRE EST CELUI DONT LA CLEF EST LA BONNE
        {
            nbValidWords = nbValidWords_tmp;
            bestKey = i;
        }
        nbValidWords_tmp = 0;
    }
    printf("%s\n", Keys[bestKey]);
}

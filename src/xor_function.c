/* * * * * * * * * * * * * *
 * Name: Chiffrage XOR     *
 * Author: LAGET Antony    *
 * Date: 10/01/2018        *
 * Description: Library    *
 * * * * * * * * * * * * * */
/**
 * INCLUTION DU HEADER
 */
#include "xor.h"

/**
 * [XOR les caracteres de l'ENTREE par rapport a la clef rentree]
 * @param 	String 	input      	[ENTREE a XORer]
 * @param 	lenthinput Lenth 	[longueur de l'ENTREE]
 * @param 	String 	key        	[CLEF]
 * @param   String* output     	[Sortie des caracteres XORer]
 */
void xorCipher(String input, lenth inputLenth, String key, String* output){

	lenth keyLenth = strlen((char*)key);
	String tmpOutput = (String)malloc((inputLenth)*sizeof(unsigned char)); 	// Allocation d'une memoire pour stocker les caracteres XORer
	lenth j = 0;
	
	for(lenth i = 0; i < inputLenth; i++) {
		if (j == keyLenth) j = 0;	
		tmpOutput[i] = (unsigned char)(input[i] ^ key[j]);
		++j;
	}
	tmpOutput[inputLenth]='\0';												// Ajout d'un \0 pour finir la String
	*output = tmpOutput;													// Renvoie de la valeur
}






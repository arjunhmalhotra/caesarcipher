//====================================================================

#define N 6000
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

// function templates
void  decode     ( char cipher[], int key, char plain[] );
void  frequency  ( char text[], float freq[] );
float alignScore ( float f1[], float f2[] );

//====================================================================
// main
//====================================================================

int main ( void )
{
    char cipher[N];         // the original ciphertext as read in
    int n = 0;              // the length of the ciphertext message
    char plain[N];          // place to hold the plaintext message
    float freq[26];         // frequencies we compute from our plaintext
    int key;                // the decoding key
    float score;            // the alignment score
    float align[26];        // alignment scores for all keys
	float min;	            // the lowest frequency
	int lowestkey = 0;      // the key with the lowest frequency


    /*----------------------- PART 1 ---------------------------------
    The purpose of part 1 is to set up the known frequencies for
    English letters A..Z in a float array.   And to read the input
    text from standard input and store the text into a char array.
    ----------------------------------------------------------------*/
     

	min = 1;
    // letter frequencies for A..Z in regular English writing
    float knownfreq[] =
    { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
      0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
      0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
      0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
      0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };

    
    /* This block of code will read a character of input at a time
     from cin until it hits the end of the input (end-of-file).   
     The characters are stored in the character array cipher.  */
    while ( cin )
    {
        char c;
        cin >> noskipws >> c;   // noskipws allows us to read spaces
        if ( cin )
            cipher[n++] = c;
    }
    cipher[n] = 0;  // end of buffer
    
    cout << "The scores for particular keys are: " << endl;


	for ( int key = 0; key < 26; key++ )        // for loop to calculate lowest key
	
	
	{
		decode ( cipher, key, plain );          // decoding for each key
		frequency ( plain, freq );              // computing frequencies for each key


        // print statement for all scores w.r.t. known scores
		cout << key << " : " << alignScore ( freq, knownfreq ) << endl;
		
		align[key] = alignScore ( freq, knownfreq );
		
			if ( align[key] < min )
				{
					min = align[key];           // assigning lowest freq score to corresponding key
					lowestkey = key;
				}
		
	}
	cout << "The lowest frequency is : " << min << endl;
	cout << "The key is : " << lowestkey << endl;

	decode ( cipher, lowestkey, plain );        // using key w/ lowest frequency to give decoded text


	cout << "The decoded cipher is : " << endl;
	cout << plain;


    
    return 0;
}

//====================================================================
// decode
// This function decodes a ciphertext into a plaintext using a
// secret key.
// Parameters:
// - cipher: a character array (c string) that is the ciphertext
// - key   : an integer key for the Caesar Cipher
// Return Value:
// - none, but the plain (plaintext) is filled in with the decoded
//   cipher text.
//====================================================================
void decode ( char cipher[], int key, char plain[] )
{
	int clength = strlen(cipher);                   // uses string.h to compute the 
                                                    // the length of cipher text
	
	for ( int i = 0; i < clength; i++)              // for loop for the decoding equation
	{
		if ( cipher[i] >= 65 && cipher[i] <= 90 )   // condition that the character must be    		
		{	                                        // between ASCII 65 & 90 i.e. A and Z
			
			if ( key != 0 )	                        // the key cannot be zero or it wont be encoded
			{	
				if ( cipher[i] > 65 )               // for results between 65 & 90				
					plain[i] = cipher[i] - key % 26;
				
				if ( cipher[i] - key < 65 )         // for results less than 65
					plain[i] = cipher[i] - key + 26;
			}
		}
		else
			plain[i] = cipher[i];                   // case that key is 0
	}

	plain[clength] = 0;                             // null condition
}

//====================================================================
// frequency
// This function computes the relative frequency of upper case letters
// that appear in the text.  Characters that are not in A..Z are ignored
// in the frequency calculation.
//
// Parameters:
// - text : a character array (c string) containing printable chars.
//
// Return Value: none but freq is changed
// - freq : an array of 26 floats each with the frequency of their
// respective letters in the string text.
//====================================================================
void frequency ( char text[], float freq[] )
{
	int n = 0;                                      // initializing the count and character count
	int count = 0;


	for ( int i = 0; i < 26; i++ )  
		freq[i] = 0;                                // initializing all frequencies to 0

	while ( text[n] )                               // while loop to record frequency values
	{	

		if ( text[n] >= 'A' && text[n] <= 'Z' )
		{
			int x = text[n] - 'A';
			freq[x]++;                              // returning values to the array of frequencies
			count++;
		}
		n++;
	}
	
	for ( int i = 0; i < 26; i++ )
		
	{
		//cout << freq[i] << endl;		
		

		freq[i] = (float)freq[i] / count ;          // establishing the array of floating point freqs
	}	

}
//====================================================================
// alignScore
// This function computes an alignment score between the two float
// vectors.  Each vector is of length 26 floats.  Their inner product
// is computed and returned.
// Parameters:
// f1 : an array of 26 floating point values
// f2 : an array of 26 floating point values
// Return Value:
// sum of (f1[i] - f2[i])^2,  that is, compute the sum of the squared
// differences of the individual elements in the array.
//====================================================================
float   alignScore ( float f1[], float f2[] )
{

	float sum;              // assign the sum as a float point
	float score;            // assign the return value as a float

	for (int i = 0; i <= 25; i++)
	{

        // uses math.h to compute the sum equation
		score = pow( ( float ( f1[i] ) - float ( f2[i] ) ), 2);
		
		sum += score;
	
	}

	return sum;

}


//====================================================================

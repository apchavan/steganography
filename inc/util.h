/**
 * This file declares some necessary utility functions.
 */
 
 #ifndef UTIL_H
 #define UTIL_H
 
 #include <string>
 
 namespace Steganography
 {
 	/** Function that return SHA-1 string of given string.
 	  * The return string is of 20 bytes always.
 	  * @param		in		The string to be hashed
 	  * @return				The hashed string of string parameter 'in'
 	  */
 	std::string sha(const std::string& in);
 	
 	/** Sets a bit.
 	  *
 	  * @param		p		A byte whose bits needs to be changed/ set.
 	  * @param		bit		The value to set either to 0 or to 1.
 	  * @param		index	The position of bit to change.
 	  */
 	void setbit(unsigned char& p, const int bit, const int index = 0);
 	
 	/** Gets a bit.
 	  *
 	  * @param		p		A byte whose bits we want.
 	  * @param		index	The position of bit we want.
 	  *
 	  * @return				The value of the desired bit i.e. 0 or 1.
 	  */
 	int getbit(const unsigned char &p, const int index = 0);

 }	// namespace 'Steganography' closed.
 
 #endif	// 'UTIL_H' closed.

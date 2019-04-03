/**
 * This file contains the definition for 'TextFile' class declared in 'TextFile.h'
 *
 */
 
#include "TextFile.h"
#include <fstream>

using namespace std;

namespace Steganography
{
	/**
	 * In the constructor below, 
	 * 'mText(str)' is used to intialize the value of 'str' to data member 'mText' of 'TextFile' class.
	 * The colon (:) is used for two reasons :=>
	 * {1} Calling base class constructors
	 * {2} Initialising member variables before the body of the constructor executes.
	 * This is generally used to assign the value to variables of type 'const'
	 */
	TextFile::TextFile(const string& str) : mText(str)
		{
			// Only Initialize the value to 'mText' before the constructor is called.
		}
		
	TextFile::~TextFile()
		{
			// Nothing to do in destructor
		}
		
	TextFile TextFile::open(const string& filename)
		{
			TextFile t;
			ifstream file(filename.c_str());
			/**
			 * c_str returns a const char* that points to a null-terminated string (i.e. a C-style string). 
			 * It is useful when you want to pass the "contents" of an std::string 
			 * to a function that expects to work with a C-style string. 
			 */
			 
			 string line;
			 getline(file, t.mText);
			 /**
			  * (#)The first variable:
			  * Pointer to an array of characters where extracted characters are stored as a c-string.
			  * (#)The second variable:
			  * Maximum number of characters to write to s (including the terminating null character). 
			  * If the function stops reading because this limit is reached without finding the delimiting character, 
			  * the failbit internal flag is set. 
			  * streamsize is a signed integral type.
			  */
			  
			 
			 while( getline(file, line))
			 	t.mText += "\n"  + line;
			 
			 return (t);
		}
	
	// Return size of the file
	string::size_type TextFile::size() const
		{
			return mText.size();
		}
	
	// Return 'std::string' object
	string TextFile::str() const
		{
			return mText;
		}
		
	// Convert to 'std::string'
	TextFile::operator std::string()
		{
			return mText;
		}
		
	// Overload '<<'
	ostream& operator <<(ostream& out, const TextFile& textFile)
		{
			return ( out<< textFile.str() );
		}
	
	// Append 'std::string' object 
	TextFile& TextFile::append(const string& str)
		{
			mText += str;
			return *this;
		}
		
	// Append 'std::string' object using '+=' operator
	TextFile& TextFile::operator +=(const string& str)
		{
			return this->append(str);
		}
		
	// Append 'TextFile' object
	TextFile& TextFile::append(const TextFile& textFile)
		{
			return this->append(textFile.str());
		}
		
	// Append 'TextFile' object using '+=' operator
	TextFile& TextFile::operator +=(const TextFile& textFile)
		{
			return this->append(textFile.str());
		}
		
	// Save the text file to disk
	void TextFile::save(const string& filename)
		{
			ofstream file(filename.c_str());
			
			string::iterator sit;
			for(sit = mText.begin() ; sit != mText.end() ; ++sit)
				{
					file.put(*sit);
				}
		}
} // namespace 'Steganography' closed.

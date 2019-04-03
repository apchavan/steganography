/**
 * This file declares 'TextFile' class that is necessary to perform the text related operations like opening, saving, 
 * appending, displaying, etc.
 * Also for representing text file buffer.
 */

 #ifndef TEXTFILE_H
 #define TEXTFILE_H

 #include <string>
 #include <iostream>
  
 namespace Steganography
 {
 	class TextFile
 		{
 			private :
 				/** To hold the contents of the text file */
 				std::string mText;
 			
 			public :
 				/** Constructor for class 'TextFile' to initialize the text file with given string */
 				TextFile(const std::string& str = "");
 				
 				/** Destructor for class 'TextFile'*/
 				virtual ~TextFile();
 				/**
 				 * Desciption for 'virtual ~TextFile();' :=>
 				 * Virtual destructors are useful when you have a parent and child class, and you want to delete an 
 				 * instance of the base class by first deleting the instance of the child class. This prevents a memory 
 				 * leak, which would have otherwise happenened if your destructor was not virtual; the base class instance 
 				 * would only have been deleted, leaving the derived instance to cause a memory leak. 
 				 */
 				 
 				
 				/** Open a text file and return the object of class 'TextFile' */
 				static TextFile open(const std::string& filename);
 				
 				/** Returns the size (in bytes) of the text file */
 				std::string::size_type size() const;
 				
 				/** Returns the contents of the text file as 'std::string' object */
 				std::string str() const;
 				
 				/** To convert into 'std::string' */
 				operator std::string();
 				
 				/**
 				  * "operator std::string();" description :=>
                  * It is a 'conversion operator' that allows the object to be explicitly or implicitly casted to 
                  * std::string. When such a cast occurs, the operator is invoked and the result of the cast is the result 
                  * of the invocation.
                  * As an example of an implicit cast, suppose you had a function that accepted type std::string or const 
                  * std::string&, but not the given object type. Passing your object to that function would result in the 
                  * conversion operator being invoked, with the result passed to the function instead of your type.
                  */
 				
 				/** Overloads '<<' operator for I/O */
 				friend std::ostream& operator <<(std::ostream& , const TextFile&);
 				
 				/** Append the given string to the text file using 'append()' method or '+=' operator respectively */
 				TextFile& append(const std::string& str);
 				TextFile& operator +=(const std::string& str);
 				
 				/** Append the given text file to the text file using 'append()' method or '+=' operator respectively */
 				TextFile& append(const TextFile& textFile);
 				TextFile& operator +=(const TextFile& textFile);
 				
 				/** Saves the text file to the disk with the given filename */
 				void save(const std::string& filename);
 				
 		};	// class 'TextFile' closed.
 		
 }	// namespace 'Steganography' closed.
 
 #endif	// 'TEXTFILE_H' closed.

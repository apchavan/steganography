/**
 * This file declares some necessary functions to handle the unexpeccted exceptions, errors.
 */

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <stdexcept>
#include <exception>

namespace Steganography
{
	/** Base class for exceptions */
	struct Error : public std::runtime_error
		{
			Error(const std::string& msg = " There has been an error ! ");
		};
	
	/** For handling empty 'MatImage' exception */
	struct ImageEmptyError : public Error
		{
			ImageEmptyError(const std::string& msg = " Image is empty ! ");
		};
		
	/** For handling empty text steg exception */
	struct TextEmptyError : public Error
		{
			TextEmptyError(const std::string& msg = " Text is empty ! ");
		};
		
	/** For handling empty password set exception */
	struct KeyEmptyError : public Error
		{
			KeyEmptyError(const std::string& msg = " Key is empty ! ");
		};
		
	/** For handling is image is not large enough */
	struct InsufficientImageError : public Error
		{
			InsufficientImageError(const std::string& msg = " Image is not large enough ! ");
		};
		
	/** For handling unsteg using incorrect password */
	struct KeyMismatchError : public Error
		{
			KeyMismatchError(const std::string& msg = " Incorrect password ! ");
		};
		
	/** For handling I/O error */
	struct IOError : public Error
		{
			IOError(const std::string& msg = " Input/output error ! ");
		};
	
	/** Displays an error message and aborts the program with return value '-1' to abort the program 
	  * @param error_msg	The error message
	  * @param ret			The return value
	  */
	void error(const std::string& error_msg = " There is an error ! ", int ret = -1);
	
	/** Displays an error message of exception and aborts the program with return value '-1' to abort the program 
	  * @param e			The exception thrown
	  * @param ret			The return value
	  */
	void error(const std::exception& e, int ret = -1);
	
}	// namespace 'Steganography' closed.

#endif	// 'ERROR_H' closed.

/** 
 * This file provides the difinition for the exception that might occur in the application
 * It is declared in "Error.h" header file
 */

#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include "Error.h"

using namespace std;

namespace Steganography
{
	Error::Error(const string& msg) : runtime_error(msg) {}

	ImageEmptyError::ImageEmptyError(const string& msg) : Error(msg) {}

	TextEmptyError::TextEmptyError(const string& msg) : Error(msg) {}

	KeyEmptyError::KeyEmptyError(const string& msg) : Error(msg) {}

	InsufficientImageError::InsufficientImageError(const string& msg) : Error(msg) {}

	KeyMismatchError::KeyMismatchError(const string& msg) : Error(msg) {}

	IOError::IOError(const string& msg) : Error(msg) {}

	// Error with message
	void error(const string& error_msg, int ret)
	{
		cerr << ":: ERROR ::  " << error_msg << endl;
		exit(ret);
	}	// 'error(const string& error_msg, int ret)' closed.

	// Error with exception
	void error(const exception& e, int ret)
	{
		error(e.what(), ret);
	}	// 'error(const exception& e, int ret)' closed.

}	// namespace 'Steganograpgy' closed.

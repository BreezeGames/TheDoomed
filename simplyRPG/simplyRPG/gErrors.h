/*	This file is part of GEngine.
*
*Decription:
* Represents a namespace for errors.
* Contains error structures and funtions for error-handling.
*
*Author: George Popov
*Date:
*Current Phase: Paused
*/
#ifndef ERRORS
#define ERRORS

//Structures of errors
namespace err
{
	void handleError(const char* msg);

	struct ERROR_CRITICAL
	{
		const char* msg;
		ERROR_CRITICAL(const char* error_description){msg = error_description;}
	};
}
#endif
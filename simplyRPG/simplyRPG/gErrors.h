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
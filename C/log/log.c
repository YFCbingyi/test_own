/*************************************************************************
	> File Name: log.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月21日 星期四 10时38分49秒
 ************************************************************************/

#include<stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOG_INFO(s,...) write_log(s,##__VA_ARGS__)

int write_log (FILE* pFile, const char *format, ...) {
	va_list arg;
	int done;

	va_start (arg, format);
	//done = vfprintf (stdout, format, arg);

	time_t time_log = time(NULL);
	struct tm* tm_log = localtime(&time_log);
	fprintf(pFile, "%04d-%02d-%02d %02d:%02d:%02d ", tm_log->tm_year + 1900, tm_log->tm_mon + 1, tm_log->tm_mday, tm_log->tm_hour, tm_log->tm_min, tm_log->tm_sec);

	done = vfprintf (pFile, format, arg);
	va_end (arg);

	fflush(pFile);
	return done;
}

int main() {
	FILE* pFile = fopen("123.txt", "a");
    LOG_INFO(pFile,"this is define %d %s %d\n",1,__func__,__LINE__);
	//write_log(pFile, "%s %d %f\n", "is running", 10, 55.55);
	fclose(pFile);

	return 0;
}

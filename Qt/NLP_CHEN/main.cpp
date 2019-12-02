#include "mainwindow.h"
#include "cplustest.h"
#include <QApplication>
#include "debug_log.h"
#include <cstdio>
#include <fstream>
#include <stdio.h>
#define DEBUG_LOG( str ) log_append_to_file("/home/cby/log_file", str,__FILE__,__LINE__ );
void log_append_to_file(char* filename,char* str,char* sourceFile,int fileLine)
{
    time_t t;
    time(&t);
    struct tm* tp= localtime(&t);
    printf("%x\n",tp);
    char now_str[100];
    strftime(now_str, 100, "%Y-%m-%d %H:%M:%S", tp);

    FILE *fo;
    fo = fopen(filename, "a");
    if (fo == 0) {
        return;
    }

    fprintf(fo, "%s %s(:%d):%s\r\n",now_str,sourceFile,fileLine, str);
    fclose(fo);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    mycplus::cplustest *cplus
            = new mycplus::cplustest();
    cplus->test();
    delete cplus;
    return a.exec();
}

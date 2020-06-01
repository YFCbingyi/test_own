/*************************************************************************
	> File Name: normal.h
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月01日 星期一 09时47分00秒
 ************************************************************************/

#ifndef _NORMAL_H
#define _NORMAL_H

#include <string>
#include <cstdlib>
#include <cstdio>

//字符串去掉所有空格
void trim(std::string &s) {
    int index = 0;
    if(!s.empty()) {
        while((index = s.find(' ',index)) != std::string::npos) {
            s.erase(index,1);
        }
    }
}

//system 执行cmd
bool runcmd(std::string &cmd) {
    pid_t status;
    status = ::system(cmd.c_str());
    if(status == -1) {
        return false;
    } else {
        if(WIFEXITED(status)){
            if(0 == WEXITSTATUS(status)){
                return true;
            }else{
                printf("run failed %d \n",WEXITSTATUS(status));
                return false;
            }
        }else{
            printf("exit code %d \n",WEXITSTATUS(status));
            return false;
        }
    }
}

#endif

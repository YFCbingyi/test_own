#include "nlp_test.h"
#include "debug_log.h"
nlp_test::nlp_test()
{

}

void nlp_test::run()
{
    LOG(INFO) << "run _ ";
    int i = 10;
        try
        {
            thread1 = std::thread(&nlp_test::_func1_,this);
            thread2 = std::thread(&nlp_test::_func1_,this);
            thread3 = std::thread(&nlp_test::_func1_,this);
        }
        catch(std::exception &e)
        {
            LOG(ERROR) << "exception: "<< e.what();
        }
}

void nlp_test::_func1_()
{
//    std::string cmd = "rosservice call /speech_service/nlp_baidu \"ask: '你好'\"";
    while(true)
    {
        LOG(INFO) << "打印";
        system("rosservice call /speech_service/nlp_baidu \"ask: '你好'\"");
    }
}

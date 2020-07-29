#include "baidu_deploy.h"
#include "debug_log.h"

// 获取access_token所需要的url

const std::string APIKey ="KGLQLzDVQjcQCWEyEc612TcN";

const std::string SecretKey = "Mx7p13zYPpO4QyHEOrdPN6jb9o28fcLd";

int main(int argc,char * argv[])
{
//    初始化日志文件
    std::string log_info = "./log/log_info";
    std::string log_warning = "./log/log_warn";
    std::string log_error = "./log/log_error";
    initLogger(log_info,log_warning,log_error);
    if(argc != 2)
    {
        std::cerr <<"传入参数格式有误, 输入 ./test --help 查看具体操作 "<<std::endl;
        LOG(ERROR) << "传入参数格式有误, 输入 ./test --help 查看具体操作";
        return -1;
    }
    std::string deploy_func = argv[1];
    LOG(INFO) << "deploy func is :"<<deploy_func;

    BaiduDeploy baidu;
    if(!baidu.inital()) {
        LOG(ERROR) << "请检查配置文件";
        return -1;
    }

    std::string AccessKey;
    std::string request;
    std::string json_result;
#if 1
    while(AccessKey.empty())
    {
        if(baidu.get_access_token(AccessKey, APIKey, SecretKey))
            LOG(ERROR) << "get access token failed";
        else
            LOG(INFO)<<"get access token success";
    }
    //判断是哪种
    if(deploy_func.compare("add") == 0)
    {
        //新增生产环境
        request = baidu.organiza_msg_product(BaiduDeploy::TASK_ADD,baidu.m_botid,baidu.m_region,baidu.m_model);
        LOG(INFO) << "request "<<request ;
        if(baidu.unit_utterance(json_result,request,AccessKey))
        {
            LOG(ERROR) << "send msg to baidu failed...";
            std::cerr << "send msg to baidu failed..." <<std::endl;
            return -1;
        }
        LOG(INFO)<<"json_ result "<< json_result;
        if(baidu.get_errorcode(json_result))
        {
            std::string error_msg = baidu.get_error_msg(json_result);
            LOG(ERROR) << "deployment add failed,error_msg : "<<error_msg;
            std::cerr << "deployment add failed,error_msg : "<<error_msg <<std::endl;
            return -1;
        }
        LOG(INFO) <<"deployment add success";
        if(!baidu.set_deploymentId(json_result)) {
            LOG(ERROR) << "set deploymentID failed";
            std::cerr << "set deploymentID failed" << std::endl;
            return -1;
        }
    }
    else if(deploy_func.compare("update") == 0)
    {
        //更新生产环境
        request = baidu.organiza_msg_product(BaiduDeploy::TASK_UPDATE,baidu.m_botid,baidu.m_region,baidu.m_model);
        LOG(INFO) << "request "<<request ;
        if(baidu.unit_utterance(json_result,request,AccessKey))
        {
            LOG(ERROR) << "send msg to baidu failed...";
            std::cerr << "send msg to baidu failed..." <<std::endl;
            return -1;
        }
        LOG(INFO)<<"json_ result "<< json_result;
        if(baidu.get_errorcode(json_result))
        {
            std::string error_msg = baidu.get_error_msg(json_result);
            LOG(ERROR) << "deployment update failed,error_msg : "<<error_msg;
            std::cerr << "deployment update failed,error_msg : "<<error_msg <<std::endl;
            return -1;
        }
        LOG(INFO) << "deployment update success";
        if(!baidu.set_deploymentId(json_result)) {
            LOG(ERROR) << "set deploymentID failed";
            std::cerr << "set deploymentID failed" << std::endl;
            return -1;
        }
	}
	else if(deploy_func.compare("check") == 0)
	{
		//查询生产环境状态
		int deploymentid = baidu.get_deploymentId(baidu.m_botid);
        if(deploymentid == -1) {
            LOG(ERROR) << "get deploymentID failed";
            std::cerr << "get deploymentID failed" << std::endl;
            return -1;
        }
		request = baidu.organiza_msg_product(BaiduDeploy::TASK_GET_STATE,baidu.m_botid,baidu.m_region,baidu.m_model,deploymentid);
		LOG(INFO) << "request "<<request ;
		if(baidu.unit_utterance(json_result,request,AccessKey))
		{
			LOG(ERROR) << "send msg to baidu failed...";
			std::cerr << "send msg to baidu failed..." <<std::endl;
			return -1;
		}
		LOG(INFO)<<"json_ result "<< json_result;
		///{"result":{"createTime":"2019-03-29 11:05:50","modelVersion":"91","deploymentId":11763,"updateTime":"2019-03-29 11:17:18","region":"bj","deployStatus":"finished"},"error_msg":"ok","error_code":0}
		if(baidu.get_errorcode(json_result))
		{
			std::string error_msg = baidu.get_error_msg(json_result);
			LOG(ERROR) << "deployment getStatus failed,error_msg : "<<error_msg;
			std::cerr << "deployment getStatus failed,error_msg : "<<error_msg <<std::endl;
			return -1;
		}
		LOG(INFO) << "deployment getStatus success";
		std::cout << "deployment getStatus success" <<std::endl;
	} else if(deploy_func.compare("--help") == 0) {
        std::cout << "./test add     --新增生产环境部署" << std::endl;
        std::cout << "./test update  --更新生产环境部署" << std::endl;
        std::cout << "./test check   --检查生产环境状态" << std::endl;
    }
	else
    {
        std::cerr <<"传入参数格式有误, 输入 ./test --help 查看具体操作 "<<std::endl;
        LOG(ERROR) << "传入参数格式有误, 输入 ./test --help 查看具体操作";
        return -1;
    }
#endif
    return 0;
}


//    {"result":{"deploymentId":"11763"},"error_msg":"ok","error_code":0}
//    {"error_msg":"modelVersion 请求参数不正确","error_code":282004}
//    {"error_code":3,"error_msg":"Unsupported openapi method"}

/*************************************************************************
	> File Name: PageHtml.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时02分48秒
 ************************************************************************/

#ifndef _PAGEHTML_H
#define _PAGEHTML_H
#include "IHtml.h"
// #include "ThreadPool.h"

class PageHtml : public IHtml
{
public:
	PageHtml(std::string name,std::string html) : _name(name), _html(html) {}
	~PageHtml(){}
	void start() {
		std::string result;
		getHtmlData(_html,result);
		parse(result);
		// ThreadPool thread_pool(5);
		// thread_pool.start();
		for(auto &t : _pictures) {
			std::string path = _name +"/"+ t.substr(t.find_last_of('/')+1);
			// thread_pool.appendTask(std::bind(&PageHtml::download,t,path));
			// std::this_thread::sleep_for(std::chrono::milliseconds(10));
			download(t,path);
		}
		// thread_pool.stop();
	}
private:
	void parse(std::string &msg) {
		//遍历获取pageHtml下图片的链接集合
		htmlcxx::HTML::ParserDom parser;
        tree<HTML::Node> dom = parser.parseTree(msg);
        for (auto t = dom.begin(); t != dom.end(); t++)
        {
            t->parseAttributes();
            if (t->isTag())
            {
                if (t->attribute("src").first && t->attribute("data-original").first && (t->attribute("src").second.find(".jpg") != std::string::npos))
                {
                    std::string pic = t->attribute("src").second;
					_pictures.push_back(pic);
                }
            }
        }
	}
private:
	std::string _name,_html;
	std::vector<std::string> _pictures;
};

#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <ctime>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include "debug_log.h"
#include <cmath>
#include <cstring>
#include <algorithm>
std::string msg_end_result;
#define STR_COM(a) "I"+a+"U"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

}

void MainWindow::crash_test() {

    ifstream is("/home/cby/rsData/conf/greeting/observer.json", ios::binary);
    if (!is.is_open()) {
        cout << "open json file failed." << endl;
    }
    Json::Reader reader;
    Json::Value root;

    // 解析json内容
    if (reader.parse(is, root)) {
        int num = root["regions"].size();
        for(int i = 0; i< num ;i++) {
            if(!root["regions"][i]["name"].asString().compare("tour")) {
                PPoint_ point;
                for(int j = 0;j < root["regions"][i]["vertices"].size(); j++) {
                    point.x = root["regions"][i]["vertices"][j][0].asFloat();
                    point.y = root["regions"][i]["vertices"][j][1].asFloat();
                    std::cout << point.x << "  "<< point.y << std::endl;
                    point_group_.push_back(point);
                }
                break;
            }
        }
    } else {

    }
    is.close();

    double minx = point_group_[0].x;
    double miny = point_group_[0].y;
    double maxx = minx;
    double maxy = miny;
    for(auto i = point_group_.begin(); i != point_group_.end();i++) {
        minx = minx > (*i).x ? (*i).x : minx;
        miny = miny > (*i).y ? (*i).y : miny;
        maxx = maxx < (*i).x ? (*i).x : maxx;
        maxy = maxy < (*i).y ? (*i).y : maxy;
    }
    std::cout << minx << " " << miny << " " << maxx << " " <<maxy << std::endl;
    double x = (minx+maxx)/2;
    double y = (miny+maxy)/2;
    std::cout << x << " " << y <<std::endl;
}

void MainWindow::sqlstr_orginize_yanhui() {

}

void MainWindow::insert_to_sqlite_orginaze() {
#if 0
    int userid = 43;
    int age = 21;
    int glasses = 0;
    int edited = 0;
    std::string RobotID = "bot2";
    std::string username = "李太白";
    std::string race = "";
    std::string gender = "";
    std::string expression = "";
    std::string usertag = "";
    std::string telephone = "16283648272";
    std::string birthday = "29172640";
    std::string update = "insert into FaceLibrary values('"+RobotID+"',"+std::to_string(userid)+",'"+username+"',"+std::to_string(age)+",'"+race+"','"+gender+"',"+std::to_string(glasses)+",'"+expression+"',"+std::to_string(edited)+",'"+usertag+"','"+telephone+"','"+birthday+"',2)";
    std::cout << update <<std::endl;
#else
    int userid = 82;
    int faceid = 3512;
    std::string RobotID = "bot2";
    std::string imagepath = "";
    std::string facefeature = "";
    std::string date = "";
    std::string type = "normal";

    std::string update = "insert into FeatureInfo (RobotId,UserId, FaceId, ImagePath, FaceFeature, Date, Type,upload) values('"+RobotID+"',"+std::to_string(userid)+","+std::to_string(faceid)+",'"+imagepath+"','"+facefeature+"','"+date+"','"+type+"',2)";
    std::cout << update <<std::endl;
//    INSERT INTO FeatureInfo (RobotId,UserId, FaceId, ImagePath, FaceFeature, Date, Type,upload) VALUES ('bot2',84,352,'','','','normal',2)
#endif
}

std::string MainWindow::get_random_str(std::string &src,std::string search_code) {
    std::string text;
    try{
        if(src.find(search_code) != std::string::npos) {
            std::vector<std::string> gtxt_;
            while(src.find_first_of(search_code) != std::string::npos) {
                gtxt_.push_back(src.substr(0,src.find_first_of(search_code)));
                src.erase(0,src.find_first_of(search_code)+1);
            }
            gtxt_.push_back(src);
            text = gtxt_[get_random_number(0,gtxt_.size())];
        } else {
            text = src;
        }
    } catch(std::exception &e) {
        std::cout <<"NlpBase::get_random_str "<<e.what() <<std::endl;
    }
    return text;
}

std::string MainWindow::get_robot_id()
{
    char *conf = getenv("HOME");
    std::string file = std::string(conf)+"/.RS/license.key";
    std::ifstream is(file.c_str());
    std::string s,robot_id("");
    while(getline(is,s)) {
        robot_id += s;
    }
    return robot_id;
}

void MainWindow::test5() {
    struct NetPacket
    {
        unsigned int Header;
        unsigned int length;
        unsigned short type;
        unsigned short store;
        std::string data;
    };

    std::string ll = "jisjoaaf";
    NetPacket info;
    info.Header = 0x5aa55aa5;
    info.length = ll.length()+12;
    info.type = 0x1;
    info.store = 0;
    info.data = ll;

}

bool MainWindow::lessmark(const   Point_&   s1,const   Point_&   s2)
{
//    if(get_distance_point(s1.x,s1.y,5,5) < get_distance_point(s2.x,s2.y,5,5)) {
//        return true;
//    } else
//        return false;

    return (get_distance_point(s1.x,s1.y,5,5) < get_distance_point(s2.x,s2.y,5,5)) ? true : false;
}

bool MainWindow::get_usebale_point_group(Point_ &person_pose,double r,int num ,std::vector<Point_> &point_group)
{
    if(!point_group.empty())
        point_group.clear();
    Point_ point;
    int angle = 360/num;
    double m = 5,n=5;
    for(int i = 0,a = 0;i<num;i++,a+=angle)
    {
        point.x = person_pose.x + r* cos(a * 3.14/180);
        point.y = person_pose.y + r* sin(a * 3.14/180);
        point_group.push_back(point);
#if 0
        if(point_group.empty()) {
            point_group.push_back(point);
        } else {
            int ll = 0;
            for(auto l = point_group.begin();l != point_group.end();l++,ll++) {
                if(get_distance_point(point.x,point.y,m,n) < get_distance_point(point_group[ll].x,point_group[ll].y,m,n)) {
                    auto it = point_group.begin()+ll;
                    point_group.insert(it,point);
                    break;
                }
                if(ll == point_group.size()-1) {
                    point_group.push_back(point);
                    break;
                }
            }
        }
#endif
   }
    LOG(INFO) << "size "<<point_group.size();
    for(auto i = point_group.begin(); i != point_group.end();i++) {
        LOG(INFO) << "x " <<(*i).x << " y "<<(*i).y;

        LOG(INFO) << "distance " <<get_distance_point((*i).x,(*i).y,m,n);
    }

    return true;
}

bool MainWindow::sort_group(std::vector<Point_> &point_group) {
    sort(point_group.begin(),point_group.end(),lessmark);

    LOG(INFO) << " 排序后";
    for(auto i = point_group.begin(); i != point_group.end();i++) {
        LOG(INFO) << "x " <<(*i).x << " y "<<(*i).y;
        LOG(INFO) << "distance " <<get_distance_point((*i).x,(*i).y,5,5);
    }
}

void MainWindow::run() {
    //********************************
    //    start_get_point();
    //    start_game();
    //    test();
    //**********************************
    //    test1();
    //    get_random_num();
    //***********************************
    //    test2();
    //********************************
    //    read_json_file_();
    //*******************************
    //    for(int i = 0;i<20;i++)
    //        read_config_file_();
    //*********************************
    //    std::string msg;
    //    get_area_msg(1,msg);
    //    std::cout << "msg :" << msg << std::endl;
    //**********读取配置文件***************
    //    conf = new Config_json();
    //**********线程**************
    //    thread = new new_thread();
    //    thread->run_();
    //********字符串组合***************
    //    string_compalte();
    //***********计算时间差***************
    //    get_time_different();
    //××××××××巡视相关×××××××××××××××
    //    start_xunshi();
    //×××××××××nlp测试××××××××××××××××××
    //    nt = new nlp_test();
    //    nt->run();
    //*************字符串转整型****************
    //    string id = "128392751512";
    //    string id2 = "home241";
    //    if(isnum(id))
    //        LOG(INFO)<< id << " is num";
    //    else
    //        LOG(INFO)<< id << " is not num";
    //    if(isnum(id2))
    //        LOG(INFO)<< id2 << " is num";
    //    else
    //        LOG(INFO)<< id2 << " is not num";
    //**************sqlite**************
    //    db_ = new fourssqlite();
    //***************拆分字符串××××××××××××
    //    chaifenstr();
    //    ceshivector();
    //    test3();
    //    test4();
    //    if(check_str(std::string("is")))
    //        LOG(INFO) << "this is true";
    //    else
    //        LOG(INFO) << "this is false";
    //*************************************
    //    for(int i=0;i<20;i++)
    //    {
    //        usleep(500000);
    //        if(check_duringtime(3))
    //        {
    //        `    LOG(INFO) << "满足天骄";
    //        }
    //    }
    //***************发布计时***************
    //    chrono = new chrono_test;
}

bool MainWindow::check_str(const std::string &name)
{
    if(!name.compare("is"))
        return true;
    else
        return false;
}

bool MainWindow::isnum(string s)
{
    stringstream sin(s);
    double t;
    char p;
    if(!(sin >> t))
        /*解释：
           sin>>t表示把sin转换成double的变量（其实对于int和float型的都会接收），如果转换成功，则值为非0，如果转换不成功就返回为0
       */
        return false;
    if(sin >> p)
        /*解释：此部分用于检测错误输入中，数字加字符串的输入形式（例如：34.f），在上面的的部分（sin>>t）已经接收并转换了输入的数字部分，在stringstream中相应也会把那一部分给清除，如果此时传入字符串是数字加字符串的输入形式，则此部分可以识别并接收字符部分，例如上面所说的，接收的是.f这部分，所以条件成立，返回false;如果剩下的部分不是字符，那么则sin>>p就为0,则进行到下一步else里面
         */
        return false;
    else
        return true;
}

void MainWindow::organize_data(bool flag, int f)
{
    flag = false;
    f = 7;

}

void MainWindow::string_compalte()
{
    std::string a = "love";
    std::string b = "I-"+a+"U";
    std::cout << b << std::endl;
    std::cout << STR_COM(a) << std::endl;
}

void MainWindow::start_get_point()
{
    LOG(INFO) << "llll";
    p = new point_zb();
}

void MainWindow::start_game()
{
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(push_button2_clicked()));
    form = new Form();
}

void MainWindow::push_button2_clicked()
{
    qDebug() << "push button 2 clicked";
    this->hide();
    form->show();
}

void MainWindow::start_nlp()
{
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(push_button_clicked()));
    nlp = new NLP(this);
}

void MainWindow::start_xunshi()
{
    x = new xunshi();
    x->run();
}

void MainWindow::push_button_clicked()
{
    QString text = ui->lineEdit->text();
    std::string xx = text.toStdString();
    nlp->tu_start(xx);
}
void MainWindow::push_button3_clicked()
{
    this->hide();
    uip->show();
}

void MainWindow::show_msg_(const QString &msg)
{
    ui->textEdit->setText(msg);
}

void MainWindow::show_text(const QString &msg)
{
    ui->textEdit->setText(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    bool start_ = true;
        bool over_ = false;
        bool leave_ = true;
        bool intercept = false;
        bool talk_  = false;
        bool busy = false;
        struct info
        {
            int view_id;
            int view_state;
            double x;
            double y;
        };
        struct info msg;
        cur_state = JNJ;
        while(1)
        {
            if(leave_)
            {
                qDebug()<<"离开当前点，前往下一个点";
                leave_ = false;
                msg.view_id = 1;
                msg.view_state = 1;
            }
            switch (cur_state) {
            case JJ:
                if(!talk_)
                {
                    talk_ = true;
                    //kaishijiaohu
                }
                if(busy)
                {
                    msg.view_state = 3;
                    cur_state = JNJ;
                    talk_ = false;
                }
                break;
            case JNJ:
                if(over_)//到达目的地
                    //结束
                {

                }
                if(start_)//未开始
                {
                    start_ = false;
                    qDebug()<<"未开始，现在开始";
//                    move_finished(msg.x,msg.y);
                    break;
                }
                if(msg.view_id != 0) //观察区
                {
                    //还没观察 / 观察已经完成
                    if(msg.view_state == 1)
                    {
                        qDebug()<<"观察区，还没进行观察";
//                        into_observe_point();
                        msg.view_state = 2;
                    }
                    else if(msg.view_state == 3)
                    {
                        qDebug()<<"观察区，观察完毕，准备离开";
                        leave_ = true;
                        break;
                    }
                }else   //非观察区
                {
//                    move_finished(msg.x,msg.y);
                    qDebug()<<"非观察点，移动";
                }
                break;
            case XNJ:
                if(intercept)
                {
                    cur_state = XJ;
                    //显示界面 语音..
                }
                break;
            case XJ:
                if(!talk_)
                {
                    talk_ = true;
                }
                if(busy)
                {
                    cur_state = XNJ;
                    talk_ = false;
                }
                break;
            default:
                break;
            }

        }
}

void MainWindow::test1()
{
    int i = 15;
    srand((unsigned)time(NULL));

    while(i--)
    {
        switch (rand()%MSG_NUM) {
        case 0:
            std::cout << MSG1 <<std::endl;
            break;
        case 1:
            std::cout << MSG2 <<std::endl;
            break;
        case 2:
            std::cout << MSG3 <<std::endl;
            break;
        case 3:
            std::cout << MSG3 <<std::endl;
            break;
        default:
            break;
        }
    }
}

//语音方面的json格式
void MainWindow::test2()
{
    Json::Value value;
    Json::Value wait;
    Json::Value waitshow;
    waitshow["show"] = "首页";
    waitshow["audio"].append("您好，是否需要我的服务。可以向我咨询业务办理和中心导览信息，有需要的可以来我这里");
    waitshow["audio"].append("我这里可以查找表格填写模版哦");
    waitshow["audio"].append("也可以查看便民设施信息");
    wait["waitarea"].append(waitshow);
    wait["leave"].append("一会儿见");
    wait["leave"].append("别着急，很快就可以办理了");
    value.append(wait);
    Json::Value relax;
    Json::Value relaxshow;
    relaxshow["show"] = "咨询";
    relaxshow["audio"].append("您好，大厅有自助饮水机和手机充电站");
    relaxshow["audio"].append("您好，大厅设有书刊杂志，您可以阅读");
    relaxshow["audio"].append("如果有业务方面的问题，可以向我咨询，我很乐意为您服务");
    relax["relaxarea"].append(relaxshow);
    relax["leave"].append("有需要可以随时找我，再见");
    value.append(relax);
    Json::Value couter;
    Json::Value coutershow;
    coutershow["show"] = "咨询";
    coutershow["audio"].append("您好，大厅有自助饮水机和手机充电站");
    coutershow["audio"].append("您好，大厅设有书刊杂志，您可以阅读");
    coutershow["audio"].append("如果有业务方面的问题，可以向我咨询，我很乐意为您服务");
    couter["couterarea"].append(coutershow);
    couter["leave"].append("有需要可以随时找我，再见");
    value.append(couter);
    Json::Value form;
    Json::Value formshow1;
    Json::Value formshow2;
    Json::Value formshow3;

    formshow1["show"] = "表格";
    formshow1["audio"].append("您好，请问您是否需要表格模版做参考");
    formshow2["show"] = "咨询";
    formshow2["audio"].append("也可以向我咨询业务办理和中心导览信息，有需要的可以来我这里");
    formshow3["show"] = "中心导览";
    formshow3["audio"].append("中心设有多项便民设施，如有需要可以向我查询");
    form["formarea"].append(formshow1);
    form["formarea"].append(formshow2);
    form["formarea"].append(formshow3);
    form["leave"].append("有需要可以随时找我，再见");
    value.append(form);

    Json::Value runn;
    Json::Value runnshow;
    runnshow["show"] = "首页";
    runnshow["audio"].append("您好，需要什么服务");
    runn["moving"].append(runnshow);
    runn["leave"].resize(0);
    value.append(runn);
    std::string str = value.toStyledString();
    std::cout << str << std::endl;
//    std::string file = "home/cby/project/points.json";
//    std::ifstream all(file, std::ios_base::);
}

void MainWindow::read_json_file_()
{
    ///home/cby/project/point.json
    std::cout << __LINE__ <<std::endl;
    Json::Reader reader;
    Json::Value root;

//    std::string file = "/home/cby/lighty_ws/src/rsApp/data/config/rslog.json";
    std::string file = "/home/cby/project/points.json";
//    is.open;

    std::ifstream iss(file, std::ios_base::binary);
    if(!iss.is_open()){
      std::cout <<"open error "<<std::endl;
    }
    std::cout << __LINE__<<std::endl;

    std::ifstream t(file);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    std::cout << "str = "<<str << std::endl;
    try{
        std::cout << "ready parse"<< std::endl;
        if(reader.parse(iss,root))
        {

            std::string name = root["name"].asString();
            std::cout << "name is :"<< name << std::endl;
            int total = root["point"].size();
            std::cout <<"total is :" <<total << std::endl;
            for(int i=0; i < total; i++)
            {
                std::cout <<"ok  "<<std::endl;
                TourPoint p;
                p.id = root["point"][i]["id"].asInt();
                p.x = root["point"][i]["x"].asInt();
                p.y = root["point"][i]["y"].asInt();
                std::cout <<"id = " <<p.id <<std::endl;
                std::cout <<"x = " <<p.x <<std::endl;
                std::cout <<"y = " <<p.y <<std::endl;
                tourline_.push_back(p);
            }
        }

    }catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
//    int x = tourline_.size();
//    for(int i = 0;i<x;i++)
//    {
//        std::cout <<"id = " <<tourline_[i].id <<std::endl;
//        std::cout <<"x = " <<tourline_[i].x <<std::endl;
//        std::cout <<"y = " <<tourline_[i].y <<std::endl;
//    }
}

void MainWindow::get_area_msg(int i, std::string &msg)
{
    Json::Reader reader;
    Json::Value root;
    std::string file = "/home/cby/project/points.json";
    std::ifstream iss(file, std::ios_base::binary);
    if(!iss.is_open()){
      std::cout <<"open error "<<std::endl;
    }
    try
    {
        if(reader.parse(iss,root))
        {
            int x = root["area_view"].size();
            for(int a = 0; a < x;a++)
            {
//                std::string name = root["area_view"][a].asString();
//                std::cout << name << std::endl;
                //|| (!root["area_view"][a]["name"].asString().compare("form2"))||(!root["area_view"][a]["name"].asString().compare("form3"))
                switch (i) {
                case 1:
                    if((!root["area_view"][a]["name"].asString().compare("form"))  )
                        msg+=root["area_view"][a].toStyledString();
                    break;
                default:
                    break;
                }
            }
            Json::Reader Reader;
            Json::Value DevJson;
            Reader.parse(msg,DevJson);
            int showid = DevJson["msg"][1]["show"].asInt();
            std::cout << "showid" << showid << std::endl;
        }
    }catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

}

int MainWindow::read_config_file_()
{
    static bool flag;
    static double time;
    if(flag)
    {
        time++;
        if(time > 10)
            flag = false;
        std::cout << "默认是true,time is "<<time << std::endl;
    }
    else
    {
        time = 0;
        std::cout << "默认是false,time is "<<time << std::endl;
        flag = true;
    }
    return 0;
}

void MainWindow::get_time_different()
{
    time_t start,end;
    double cost;
    bool flag = false;
    xunshi x;
    while(0)
    {
        usleep(800000);
        if(!flag)
        {
            flag = true;
            time(&start);
        }
        time(&end);
        cost = difftime(end,start);
        LOG(INFO)<<"cost : "<<cost;
        if(cost > 5)
        {
            flag = false;
            LOG(ERROR) << "success ";
        }
    }
    while(1)
    {
        sleep(1);
        switch (get_timediff_result(flag,5,x)) {
        case 0:
            flag = false;
            LOG(INFO) << "切换成功";
            break;
        case 1:
            LOG(INFO) << "开始计时";
            flag = true;
            break;
        default:
            break;
        }
    }
}

int MainWindow::get_timediff_result(bool start_timing,double rated_time,xunshi &x)
{
    static time_t start;
    time_t end;
    if(!start_timing)
    {
        time(&start);
        return 1;
    }
    time(&end);
    if(difftime(end,start) > rated_time)
    {
        int y = x.get_id();
        LOG(INFO) << "y " << y;
        return 0;

    }
    else
    {
        return -1;
    }
}

bool MainWindow::chaifenstr()
{
    std::string str = "user_yesno : 需要";
    int index = str.find(" : ");
    std::cout << index << std::endl;
    std::string src = str.substr(0,index);
    std::cout << src << src.size()<<std::endl;
    std::string sen = str.substr(index+3,str.size());
    std::cout << sen << sen.size()<<std::endl;
}

bool MainWindow::ceshivector()
{
    std::string name1 = "zhangsanf";
    std::string name2 = "liyu";
    std::string name3 = "jijfa";
    std::string name4 = "gajiag";

    name.push_back(name1);
    name.push_back(name2);
    name.push_back(name3);

    strring.push_back(name1);
    strring.push_back(name3);
    strring.push_back(name4);

    for(std::vector<std::string>::iterator it = name.begin(); it!=name.end();it++)
    {
        std::cout << "name1: "<<(*it) << std::endl;
    }
    name = get_jiaoji_str(name,strring);
    for(std::vector<std::string>::iterator it = name.begin(); it!=name.end();it++)
    {
        std::cout << "name3: "<<(*it) << std::endl;
    }
}

std::vector<string> MainWindow::get_jiaoji_str(std::vector<string> &v1, std::vector<string> &v2)
{
    std::vector<std::string> v;
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));//求交集
    for(std::vector<std::string>::iterator it = v.begin(); it!=v.end();it++)
    {
        std::cout << "name2: "<<(*it) << std::endl;
    }
    return v;
}

void MainWindow::test3()
{
    std::vector<double> v{1.0, 2.0, 3.0, 0.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    auto smallest = std::min_element(std::begin(v), std::end(v));
     int i = std::distance(std::begin(v), smallest);
     LOG(INFO) << i;
}

bool MainWindow::get_bool()
{
    LOG(INFO) << " is true";
    return true;
}

void MainWindow::test4()
{
    std::string name="chenbingyi",pwd = "W123456";
    LOG(INFO) << "name :" << name << " pwd :"<<pwd;
}

bool MainWindow::check_duringtime(time_t durtime)
{
    static time_t start_,end_;
    static int i;
    i++;
    LOG(INFO) << "i = " <<i;
    if(i == 1)
    {
        time(&start_);
    }
    time(&end_);
    if(difftime(end_,start_) > durtime)
    {
        i = 0;
        LOG(INFO) << "success";
        return true;
    }
    LOG(INFO) << "failed";
    return false;
}

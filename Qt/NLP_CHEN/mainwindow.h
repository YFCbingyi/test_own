#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nlp.h"
#include "xunshi.h"
#include "form.h"
#include "point_zb.h"
#include "config_json.h"
#include "new_thread.h"
#include "nlp_test.h"
#include "uipython.h"
#include "fourssqlite.h"
#include "chrono_test.h"
#include <ctime>
#define MSG1 "您好，附近有等待区，可以先休息一下。如有业务方面的问题，可以向我咨询，很乐意为您服务"
#define MSG2 "您好，是否需要我的服务。可以向我咨询业务相关信息"
#define MSG3 "您好，我了解业务办理的流程，可以向我咨询"

#define MSG_NUM 3
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    typedef struct
    {
        double x;
        double y;
    } PPoint_;
    std::vector<PPoint_> point_group_;

    typedef struct Point
    {
        double x;
        double y;
        double dis;
    }Point_;

    std::vector<Point_> gpoint_;
    struct Que{
        double x;
        double y;
        double dis;
    }que_;
    std::vector<Que> qque_;
    typedef struct {
      int id;
      double x;
      double y;
    } TourPoint;

    typedef std::vector<TourPoint> TourLine;
    enum CUR_STATE {JJ, JNJ, XJ,XNJ};
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void crash_test();
    void run();
    void test();
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void sqlstr_orginize_yanhui();
    std::string get_robot_id();
    std::string get_random_str(std::string &src,std::string search_code);
    void insert_to_sqlite_orginaze();
    bool get_bool();
    void read_json_file_();
    int read_config_file_();
    int get_random_number(int min,int max) const {
        return rand() % static_cast<int>(max + 1 - min) + min;
    }
    void show_text(const QString &msg);

    void start_xunshi();
    void start_nlp();
    void start_game();
    void start_get_point();
    void get_area_msg(int i,std::string &msg);
    void string_compalte();

    void get_time_different();
    int get_timediff_result(bool start_timing,double rated_time,xunshi &x);
    void organize_data(bool flag,int f);

    bool isnum(string s);
    bool chaifenstr();
    bool ceshivector();
    std::vector<string> get_jiaoji_str(std::vector<std::string> &v1,std::vector<std::string> &v2);
    bool check_str(const std::string &name);
    bool check_duringtime(time_t durtime);
    bool get_usebale_point_group(Point_ &person_pose,double r,int num ,std::vector<Point_> &point_group);
    static double get_distance_point (double x,double y,double m,double n){
        return sqrt((x-m)*(x-m) + (y-n)*(y-n));
    }
    static bool lessmark(const   Point_&   s1,const   Point_&   s2);
    bool sort_group(std::vector<Point_> &point_group);
private:
    CUR_STATE cur_state;
    Ui::MainWindow *ui;
    NLP *nlp;
    xunshi *x;
    Form* form;
    point_zb *p;
    TourLine tourline_;
    Config_json *conf;
    new_thread *thread;
    nlp_test *nt;
    uipython *uip;
    fourssqlite *db_;
    chrono_test *chrono;

    std::vector<std::string> name;
    std::vector<std::string> strring;

public slots:
    void push_button_clicked();
    void push_button2_clicked();
    void push_button3_clicked();
    void show_msg_(const QString &msg);
};

#endif // MAINWINDOW_H

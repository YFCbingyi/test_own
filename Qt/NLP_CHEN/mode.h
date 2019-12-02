#ifndef MODE_H
#define MODE_H

class my_share_ptr;
class Mode {
public:
    virtual ~Mode() {}
    virtual void operation(my_share_ptr* handle) = 0;
    double line;
};

class NormalMode : public Mode {
private:
    void operation(my_share_ptr* handle);
};

class PlanMode : public Mode {
    void operation(my_share_ptr* handle);
};

#endif // MODE_H

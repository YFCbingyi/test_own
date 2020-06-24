#include "peripherals/Expression.h"
#include <unistd.h>
int main() {
    Expression *ep = Expression::getInstance();
	printf("EXP_CONFIDENCE 自信\n");
	ep->display(Expression::EXP_CONFIDENCE);
	sleep(2);
	printf("EXP_HAPPY 开心\n");
	ep->display(Expression::EXP_HAPPY);
	sleep(2);
	printf("EXP_CRY 苦\n");
	ep->display(Expression::EXP_CRY);
	sleep(2);
	printf("EXP_BLOWBUBBLE 吹泡\n");
	ep->display(Expression::EXP_BLOWBUBBLE);
	sleep(2);
	printf("EXP_SHUTUP 闭嘴\n");
	ep->display(Expression::EXP_SHUTUP);
	sleep(2);
	printf("EXP_LICKLIPS 舔唇\n");
	ep->display(Expression::EXP_LICKLIPS);
	sleep(2);
	printf("EXP_ANGRY 生气\n");
	ep->display(Expression::EXP_ANGRY);
	sleep(2);
	printf("EXP_SUPRISE 震惊\n");
	ep->display(Expression::EXP_SUPRISE);
    return 0;
}

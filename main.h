#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//定义书籍结构体
typedef struct Book{
    char bookname[100];
    char author[100];
    int num;
    char publisher[100];
    int inventory;//库存
}book;
//借书人
typedef struct{
    char name[100];
    char borrow_name[100];
    char borrow_time[100];
    char return_time[100];
}borrow;
//用户
typedef struct User{
    char name[50];
    char password[50];
}USER;
//定义bo链表结构体
typedef struct NODE
{
    book data;
    borrow br;
    USER user;
    struct NODE *next;
}node;

//读文件
void read_fp(char *filename);
//注册
void enroll();
//普通用户登录
int login(char *name);
//管理员登录
int loginRoot();
//创建节点
node *createbook();
//插入节点
void insertbook(node *head,book book);
//打印节点
void printbook(node *head);
//添加书籍信息
void addbook();
//删除书籍信息
void delbook();
//查看所有书籍信息
void showbook();
//查询书籍信息
void searchbook();
//借阅书籍
void borrowbook(char *name);
//归还书籍
void returnbook(char *name);
//创建brrow节点
node *createborrow();
//插入节点
void insertbrrrow(node *head,borrow br);
//打印brrow节点
void printborrow(node *head);
//对编号进行排序
void sortnum();
//排序
void sortbook(node *head);
//创建user节点
node *createuser();
//插入user节点
void insertuser(node *head,USER user);
//打印user节点
void printuser(node *head);
//修改密码
void changepassword();
//查看以订阅书籍
void tosubscribe(char *name);
//查看借书人信息
void showreader();
//删除用户
void deleteuser();
//获取当地时间
char *gettime(char *time_string, size_t size);
// 计算截止时间
char *get_deadline(char *time_string, size_t size, int days);
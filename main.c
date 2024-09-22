#include"main.h"
#if 1
int main()
{
    int n=0;
    int n2 =0; 
    int flag=0;
    char name[50];
    NEXT:
    read_fp("ui/denglu.txt");
    printf("按任意键继续");
    getchar();
    printf("请输入您要进行的操作:\n");
    scanf("%d",&n);
    char k = n + '0';
    if(k<'0' || k>'9')
    {
        printf("输入错误，请重新输入\n");
        
        goto NEXT;
    }
    //用户登录界面选择
    switch (n)
    {
        case 1:
            enroll();//注册
            goto NEXT;   
            break;
        case 2:
           read_fp("ui/user_select.txt");//用户选择
            scanf("%d",&n2);
            switch (n2)
            {
            case 1://管理员
                 flag =loginRoot(name);
                if(flag==1)
                {
                    int se1 =0;
                    NEXT2:
                    read_fp("ui/root.txt");
                    printf("请输入您要进行的操作:\n");
                    scanf("%d",&se1);
                    switch (se1)
                    {
                        case 1:
                            addbook();//添加书籍
                            goto NEXT2;
                            break;
                        case 2:
                            delbook();//删除书籍
                            goto NEXT2;
                            break;
                        case 3:
                            sortnum();//排序书籍
                            goto NEXT2;
                            break;
                        case 4:
                            showreader();//查看借书人信息
                            goto NEXT2;
                            break;
                        case 5:
                            deleteuser();//删除用户
                            goto NEXT2;
                            break;
                        case 6:
                            printf("您已成功退出程序\n");
                            break;
                        default:
                            printf("输入错误，请合规操作\n");
                            break;
                    }
                }
                break;
            case 2://普通用户
                 flag =login(name);
                if(flag==1)
                {
                    int se =0;
                    NEXT1:
                    read_fp("ui/user.txt");
                    printf("请输入您要进行的操作:\n");
                    scanf("%d",&se);
                    switch (se)
                    {
                        case 1:
                            showbook();//显示书籍
                            goto NEXT1;
                            break;
                        case 2:
                            searchbook();//查询书籍信息
                            goto NEXT1;
                            break;
                        case 3:
                            borrowbook(name);//借阅书籍
                            goto NEXT1;
                            break;
                        case 4:
                            returnbook(name);//归还书籍
                            goto NEXT1;
                            break;
                        case 5:
                            tosubscribe(name);//查看以订阅书籍
                            goto NEXT1;
                            break;
                        case 6:
                            printf("您已成功退出程序\n");
                            break;
                        default:
                            printf("输入错误，请合规操作\n");
                            break;
                    } 
                }
                break;         
            default:
                printf("输入错误\n");
                break;
        }
        break;
        case 3:
            changepassword();//修改密码
            goto NEXT;
            break;
        case 4:
            printf("您已成功退出程序\n");
            break;
        default:
            printf("输入错误，请合规操作\n");
            goto NEXT;
            break;
    }
    return 0;
}

#endif
// int main()
// {
//     char time[100];
//     gettime(time,sizeof(time));
//     printf("当前时间:%s\n",time);
//     char time2[100];
//     get_deadline(time2,sizeof(time2),30);
//     printf("截止时间:%s\n",time2);
//     return 0;
// }
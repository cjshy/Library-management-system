#include"main.h"

//对文件进行读
void read_fp(char *filename)
{
    FILE *fp =fopen(filename,"r");
    if(fp == NULL)
    {
        printf("文件打开失败\n");
        return ;
    }
    char temp[200];
    while(fgets(temp,sizeof(temp),fp) !=NULL)
    {
        printf("%s",temp);
    }
    fclose(fp);
    putchar(10);
    return ;
}
//注册
void enroll()
{
    char name[50];
    char password[20];
    char name1[50];
    char name2[50];
    int flag =0;
    FILE *fp = fopen("user.txt", "a+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return;
    }
    printf("请输入您的用户名：");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1]='\0';
    printf("请输入您的密码：");
    //getchar();
    fgets(password, sizeof(password), stdin);
    while(fgets(name1, sizeof(name1), fp) != NULL)
    {
        strcpy(name2, strtok(name1,":"));
        if(strcmp(name,name2)== 0)
        {
            flag =1;
        }
    }
    if(flag == 1)
    {
        printf("账户已存在\n");
        flag = 0;
        return ;
    }
    else
    {
        fprintf(fp,"%s:%s",name,password);
        fclose(fp);
        printf("注册成功\n");
    }
}
//普通用户登录
int login(char *name)
{
    char name1[50];
    char name2[50];
    char password[20];
    char password1[20];
    int flag =0;
    int root_flag =0;
    FILE *fp = fopen("user.txt", "r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return -1;
    }
    printf("请输入您的用户名：");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1]='\0';
    printf("请输入您的密码：");
    fgets(password, sizeof(password), stdin);
    //判断是否为普通用户
    while(fgets(name1, sizeof(name1), fp) != NULL)
    {
        strcpy(name2, strtok(name1,":"));
        strcpy(password1, strtok(NULL,":"));
        if(strcmp(name,name2)== 0 && strcmp(password,password1)== 0)
        {
            flag =1;
            break;
        }
    }
    if(flag == 1)
    {
        printf("登陆成功\n");
        printf("欢迎您，%s,您是普通用户\n",name);
        return flag;
    }
    else
    {
        printf("用户名或密码错误\n");
        return -1;
    }
       
}
//管理员登录
int loginRoot(char *name)
{
    char name1[50];
    char name2[50];
    char password[20];
    char password1[20];
    int flag =0;
    FILE *fp = fopen("superuser.txt", "r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return -1;
    }
    printf("请输入您的用户名：");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1]='\0';
    printf("请输入您的密码：");
    fgets(password, sizeof(password), stdin);
    //判断是否为管理员用户
    while(fgets(name1, sizeof(name1), fp) != NULL)
    {
        strcpy(name2, strtok(name1,":"));
        strcpy(password1, strtok(NULL,":"));
        if(strcmp(name,name2)== 0 && strcmp(password,password1)== 0)
        {
            flag =1;
            break;
        }
    }
    if(flag == 1)
    {
        printf("登陆成功\n");
        printf("欢迎您，%s,您是管理员用户\n",name);
        return flag;
    }
    else
    {
        printf("用户名或密码错误\n");
        return -1;
    }
}
//创建book节点
node *createbook()
{
    node *p = (node*)malloc(sizeof(node));
    if(p == NULL)
    {
        printf("内存分配失败！");
        return NULL;
    }
    strcpy(p->data.author, " ");
    strcpy(p->data.bookname, " ");
    strcpy(p->data.publisher, " ");
    p->data.inventory = 0;
    p->data.num = 0;
    p->next = NULL;
    return p;
}
//插入节点
void insertbook(node *head,book book)
{
    node *p = malloc(sizeof(node));
    if(p == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    strcpy(p->data.author, book.author);
    strcpy(p->data.bookname, book.bookname);
    strcpy(p->data.publisher, book.publisher);
    p->data.inventory = book.inventory;
    p->data.num = book.num;
    while(head->next!= NULL)
    {
        head = head->next;
    }
    head->next = p;
    p->next = NULL;
}
//打印节点
void printbook(node *head)
{
    node *p = head->next;
    while(p !=NULL)
    {
        printf("书名：%s \t",p->data.bookname);
        printf("作者：%s \t",p->data.author);
        printf("出版社:%s \t",p->data.publisher);
        printf("库存：%d \t",p->data.inventory);
        printf("编号：%d\n",p->data.num);

        p = p->next;
    }
}
//添加书籍信息
void addbook()
{
    book books;
    node *head = createbook();
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("book.txt","a+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    printf("请输入书名：");
    getchar();
    scanf("%s",books.bookname);
    printf("请输入作者：");
    getchar();
    scanf("%s",books.author);
    printf("请输入出版社：");
    getchar();
    scanf("%s",books.publisher);
    printf("请输入库存：");
    scanf("%d",&books.inventory);
    printf("请输入编号：");
    scanf("%d",&books.num);
    insertbook(head,books);
    fprintf(fp,"%s:%s:%s:%d:%d\n",books.bookname,books.author,books.publisher,books.inventory,books.num);
    fclose(fp);
    printf("添加成功！\n");

}
//删除书籍信息
void delbook()
{
    node *head = createbook();
    char bookname[50];
    char temp[200];
    book Books;
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("book.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    printf("请输入书名：");
    getchar();
    scanf("%s",bookname);
    node *p = head;
    node *q = head;
    int flag =0;
    while (fgets(temp, sizeof(book), fp)!= NULL)
    {
        strcpy(Books.bookname, strtok(temp,":"));
        strcpy(Books.author, strtok(NULL,":"));
        strcpy(Books.publisher, strtok(NULL,":"));
        Books.inventory = atoi(strtok(NULL,":"));
        Books.num = atoi(strtok(NULL,"\n"));
        insertbook(head,Books);
        head = q;
        //printbook(head);;
        if(strcmp(Books.bookname,bookname)==0)
        {
            while(p->next!= NULL)
            {
                if(strcmp(p->next->data.bookname,bookname) == 0)
                {
                    flag =1;
                    node *temp = p->next;
                    p->next = p->next->next;
                    free(temp);
                    break;
                } 
                else
                {
                    p = p->next;
                }
            }
        }
    }
    if(flag == 0)
    {
        printf("书籍不存在！\n");
        return ;
    }
    fclose(fp);
    //删除文件中的数据
    fp = fopen("book.txt","w+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    while(head->next!= NULL)
    {
        fprintf(fp,"%s:%s:%s:%d:%d\n",head->next->data.bookname,head->next->data.author,head->next->data.publisher,head->next->data.inventory,head->next->data.num);
        head = head->next;
    }
    fclose(fp);
    printf("删除成功！\n");
}
//查看所有书籍信息
void showbook()
{
    node *head1 = createbook();
    char bookname[50];
    char temp[200];
    book Books;
    if(head1 == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("book.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    node *p = head1;
    while (fgets(temp, sizeof(book), fp)!= NULL)
    {
        strcpy(Books.bookname, strtok(temp,":"));
        strcpy(Books.author, strtok(NULL,":"));
        strcpy(Books.publisher, strtok(NULL,":"));
        Books.inventory = atoi(strtok(NULL,":"));
        Books.num = atoi(strtok(NULL,"\n"));
        insertbook(head1,Books);
        head1 = p;
    }

    fclose(fp);
    printf("书籍信息如下：\n");
    printbook(head1);
    return ;
}    
//查询书籍信息
void searchbook()
{
    FILE *fp = fopen("book.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    printf("请输入书名或编号：\n");
    printf("1.书名\n");
    printf("2.编号\n");
    int n;
    char bookname[50];
    int num=0;
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        printf("请输入书名：");
         scanf("%s",bookname);
        break;
    case 2:
        printf("请输入编号：");
        scanf("%d",&num);
        break;
    default:
        break;
    }
    
    char temp[200];
    book Books;
    int flag =0;
    while(fgets(temp, sizeof(book), fp)!= NULL)
    {
        strcpy(Books.bookname, strtok(temp,":"));
        strcpy(Books.author, strtok(NULL,":"));
        strcpy(Books.publisher, strtok(NULL,":"));
        Books.inventory = atoi(strtok(NULL,":"));
        Books.num = atoi(strtok(NULL,"\n"));
        if((strcmp(Books.bookname,bookname)==0) || (Books.num == num))
        {
            flag =1;
            printf("%s\t%s\t%s\t%d\t%d\n",Books.bookname,Books.author,Books.publisher,Books.inventory,Books.num);
        }
    }
    if(flag == 0)
    {
        printf("书籍不存在！\n");
    }
    fclose(fp);
    return ;
}
//借阅书籍
void borrowbook(char *name)
{
    node *head = createbook();
    char bookname[50];
    char temp[200];
    book Books;
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("book.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    printf("请输入书名：");
    getchar();
    scanf("%s",bookname);
    node *p = head;
    node *q = head;
    int flag =0;
    char borrow_name[50];
    while (fgets(temp, sizeof(book), fp)!= NULL)
    {
        strcpy(Books.bookname, strtok(temp,":"));
        strcpy(Books.author, strtok(NULL,":"));
        strcpy(Books.publisher, strtok(NULL,":"));
        Books.inventory = atoi(strtok(NULL,":"));
        Books.num = atoi(strtok(NULL,"\n"));
        insertbook(head,Books);
        head = q;
        //判断是否有这本书籍
        if(strcmp(Books.bookname,bookname)==0)
        {
            
           flag =1;
           strcpy(borrow_name,bookname);
           printf("存在这本书籍,库存;%d\n",Books.inventory);
           getchar();
           printf("您是否确定借阅这本书籍？(y/n)\n");
           char c;
           scanf("%c",&c);
           if(c == 'y' || c == 'Y')
           {
                if(Books.inventory > 0)
                {
                    while(p->next!= NULL)
                    {
                        if(strcmp(p->next->data.bookname,bookname) == 0)
                        {
                            p->next->data.inventory--;
                            printf("借阅成功！\n");
                            break;
                        }
                        else{
                            p = p->next;
                        }
                    }
                }
                else{
                    printf("这本书籍已经借完了！\n");
                    return ;
                }
           }
           else
           {
                printf("您取消了借阅！\n");
                return ;
           
            }
        }

    }
    //书籍不存在
        if(flag == 0)
        {
            printf("书籍不存在！\n");
            return ;
        }
        fclose(fp);
    //更新文件中的数据
        fp = fopen("book.txt","w+");
        if(fp == NULL)
        {
            printf("文件打开失败！");
            return ;
        }
        while(head->next!= NULL)
        {
            fprintf(fp,"%s:%s:%s:%d:%d\n",head->next->data.bookname,head->next->data.author,head->next->data.publisher,head->next->data.inventory,head->next->data.num);
            head = head->next;
        }
        fclose(fp);          

        //创建一个文件记录用户借了什么书
        FILE *fp1 = fopen("borrow.txt","a+");
        if(fp1 == NULL)
        {
            printf("文件打开失败！");
            return ;
        }
        borrow br;
        strcpy(br.name,name);
        strcpy(br.borrow_name,borrow_name);
        gettime(br.borrow_time,sizeof(br.borrow_time));
        get_deadline(br.return_time,sizeof(br.return_time),15);//默认15天后归还
        fprintf(fp1,"%s:%s:%s-%s\n",br.name,br.borrow_name,br.borrow_time,br.return_time);
        fclose(fp1);
        return ;
}
//归还书籍
void returnbook(char *name)
{
     printf("请输入您归还的书名：");
    getchar();
    char bookname[50];
    scanf("%s",bookname);
    char borrow_name[50];
    int flag1 =0;
    //删除文件中的数据
    node *head1 = createborrow();
    if(head1 == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("borrow.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }

    borrow br;
    char temp2[200];
    node *p1 = head1;
    node *q1 = head1;
    while ( fgets(temp2, sizeof(temp2), fp)!= NULL)
    {
        strcpy(br.name, strtok(temp2,":"));
        strcpy(br.borrow_name, strtok(NULL,":"));
        strcpy(br.borrow_time, strtok(NULL,"-"));
        strcpy(br.return_time, strtok(NULL,"\n"));
        insertbrrrow(head1,br);
        head1 = q1;
        //printborrow(head1);
        if(flag1 == 0)
        {
            if(strcmp(name,br.name)==0 && strcmp(bookname,br.borrow_name)==0)
            {

                while(p1->next != NULL)
                {
                    if(strcmp(p1->next->br.name,name) == 0 && strcmp(p1->next->br.borrow_name,bookname) == 0)
                    {
                        flag1 =1;
                        node *temp = p1->next;
                        p1->next = temp->next;
                        free(temp);
                        break;
                    }
                    else
                    {
                        p1 = p1->next;
                    }
                }
            
            }
        }
        
    }

    if (flag1 == 0)
    {
        printf("您没有借阅这本书籍！\n");
        return ;
    }
    head1 = q1;
    fclose(fp);

    //更新文件中的数据
    //printf("********\n");
    //printborrow(head1);
    fp = fopen("borrow.txt","w+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    while(head1->next != NULL)
    {
        fprintf(fp,"%s:%s:%s-%s\n",head1->next->br.name,head1->next->br.borrow_name,head1->next->br.borrow_time,head1->next->br.return_time);
        head1 = head1->next;
    }
    fclose(fp);
    printf("删除成功！\n");

#if 1
    //更新book.txt文件中的数据
    node *head = createbook();
    char temp[200];
    book Books;
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp1 = fopen("book.txt","r");
    if(fp1 == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
   
    node *p = head;
    node *q = head;
    int flag =0;
    while (fgets(temp, sizeof(book), fp1)!= NULL)
    {
        strcpy(Books.bookname, strtok(temp,":"));
        strcpy(Books.author, strtok(NULL,":"));
        strcpy(Books.publisher, strtok(NULL,":"));
        Books.inventory = atoi(strtok(NULL,":"));
        Books.num = atoi(strtok(NULL,"\n"));
        insertbook(head,Books);
        head = q;
        if(strcmp(Books.bookname,bookname)==0)
        {
            //strcpy(borrow_name,bookname);
            while(p->next!= NULL)
            {
                if(strcmp(p->next->data.bookname,bookname) == 0)
                {
                    flag =1;
                    p->next->data.inventory++;
                    break;
                }
                else
                {
                    p =p->next;
                }
            }
        }
    }
    if(flag == 0)
    {
        printf("图书馆没有这本书籍！\n");
        return ;
    }
    fclose(fp1);

    //更新文件中的数据
    fp1 = fopen("book.txt","w+");
    if(fp1 == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    while(head->next!= NULL)
    {
        fprintf(fp1,"%s:%s:%s:%d:%d\n",head->next->data.bookname,head->next->data.author,head->next->data.publisher,head->next->data.inventory,head->next->data.num);
        head = head->next;
    }
    fclose(fp1);
#endif
    
}
//创建brrow节点
node *createborrow()
{
    node *p = (node*)malloc(sizeof(node));
    if(p == NULL)
    {
        printf("内存分配失败！");
        return NULL;
    }
    strcpy(p->br.name, " ");
    strcpy(p->br.borrow_name, " ");
    strcpy(p->br.borrow_time, " ");
    strcpy(p->br.return_time, " ");
    p->next = NULL;
    return p;
}
//插入brrow节点
void insertbrrrow(node *head,borrow br)
{
    if(head == NULL)
    {
        printf("头节点未初始化\n");
        return ;
    }
    node *p = malloc(sizeof(node));
    if(p == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    p->next = NULL;
    strcpy(p->br.name, br.name);
    strcpy(p->br.borrow_name, br.borrow_name);
    strcpy(p->br.borrow_time, br.borrow_time);
    strcpy(p->br.return_time, br.return_time);
    while(head->next != NULL)
    {
        head = head->next;
    }
    head->next = p;
    return ;
}
//打印brrow节点
void printborrow(node *head)
{
    if(head == NULL)
    {
        printf("链表为空！");
        return ;
    }
    while(head->next != NULL)
    {
        printf("%s:%s:%s:%s\n",head->next->br.name,head->next->br.borrow_name,head->next->br.borrow_time,head->next->br.return_time);
        head = head->next;
    }
}
//对编号进行排序
void sortnum()
{
    node *head = createbook();
    char temp[200];
    book Books;
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("book.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    node *p = head;
    node *q = head;
    int flag =0;
    while (fgets(temp, sizeof(book), fp)!= NULL)
    {
        strcpy(Books.bookname, strtok(temp,":"));
        strcpy(Books.author, strtok(NULL,":"));
        strcpy(Books.publisher, strtok(NULL,":"));
        Books.inventory = atoi(strtok(NULL,":"));
        Books.num = atoi(strtok(NULL,"\n"));
        insertbook(head,Books);
        head = q;
    }
    fclose(fp);
    //排序
    sortbook(head);
    //更新文件中的数据
    fp = fopen("book.txt","w+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    while(head->next != NULL)
    {
        fprintf(fp,"%s:%s:%s:%d:%d\n",head->next->data.bookname,head->next->data.author,head->next->data.publisher,head->next->data.inventory,head->next->data.num);
        head = head->next;
    }
    fclose(fp);
    printf("排序成功！\n");
}
//排序
void sortbook(node *head)
{
    if(head == NULL)
    {
        printf("链表为空！");
        return ;
    }
    node *temp;
    temp = head->next;
    head->next = NULL;

    node *s;
    node *save = head;
    while(temp!= NULL)
    {
        s = temp;
        temp =temp->next;
        while(head->next !=NULL && s->data.num > head->next->data.num)
        {
            head = head->next;
        }
        s->next = head->next;
        head->next = s;

        head = save;
    }
}
//创建user节点
node *createuser()
{
    node *p = (node*)malloc(sizeof(node));
    if(p == NULL)
    {
        printf("内存分配失败！");
        return NULL;
    }
    strcpy(p->user.name, " ");
    strcpy(p->user.password, " ");
    p->next = NULL;
    return p;
}
//插入user节点
void insertuser(node *head,USER user)
{
    node *p = malloc(sizeof(node));
    if(p == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    strcpy(p->user.name, user.name);
    strcpy(p->user.password, user.password);
    while(head->next != NULL)
    {
        head = head->next;
    }
    head->next = p;
    p->next = NULL;
}
//打印user节点
void printuser(node *head)
{
    if(head == NULL)
    {
        printf("链表为空！");
        return ;
    }
    while(head->next != NULL)
    {
        printf("%s:%s\n",head->next->user.name,head->next->user.password);
        head = head->next;
    }
}
//修改密码
void changepassword()
{
    node *head = createuser();
    char temp[200];
    USER Users;
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("user.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    node *p = head;
    node *q = head;
    int flag =0;
    char name[50];
    printf("请输入用户名：");
    scanf("%s",name);
    char password[100];
    printf("请输入原密码：");
    scanf("%s",password);
    while (fgets(temp, sizeof(USER), fp)!= NULL)
    {
         strcpy(Users.name,strtok(temp,":"));
         strcpy(Users.password,strtok(NULL,"\n"));
         insertuser(head,Users);
         head =q;
         //printuser(head);
         if(strcmp(Users.name,name) == 0 && strcmp(Users.password,password) == 0)
         {
            
            while(p->next)
            {
                if(strcmp(p->next->user.name,name)==0 && strcmp(p->next->user.password,password)==0)
                {
                    flag =1;
                    char passwordnew[100];
                    printf("请输入新密码：");
                    scanf("%s",passwordnew);
                    if(strcmp(passwordnew,password)== 0)
                    {
                        printf("新密码与原密码相同！\n");
                        return ;
                    }
                    strcpy(p->next->user.password,passwordnew);
                    printf("密码修改成功！\n");
                    break;
                }
                else
                {
                    p= p->next;
                }
            }

         }
         
    }
    if(flag == 0)
         {
            printf("用户名或密码错误！\n");
            return ;
         }
    fclose(fp);
    //更新文件中的数据
    fp = fopen("user.txt","w+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    while(head->next != NULL)
    {
        fprintf(fp,"%s:%s\n",head->next->user.name,head->next->user.password);
        head = head->next;
    }
    fclose(fp);
}
//查看借书人信息
void showreader()
{
    FILE *fp = fopen("borrow.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败\n");
        return ;
    }
    char temp[200];
    borrow readr;
    while(fgets(temp,sizeof(borrow),fp))
    {
        strcpy(readr.name,strtok(temp,":"));
        strcpy(readr.borrow_name,strtok(NULL,":"));
        strcpy(readr.borrow_time,strtok(NULL,"-"));
        strcpy(readr.return_time,strtok(NULL,"\n"));
        printf("姓名：%s  借出书籍:%s  借书时间：%s  还书时间：%s\n",readr.name,readr.borrow_name,readr.borrow_time,readr.return_time);
    }
    fclose(fp);
}
//查看以订阅书籍
void tosubscribe(char *name)
{
   FILE *fp = fopen("borrow.txt","r");
   if(fp == NULL)
   {
       printf("文件打开失败！");
       return ;
   }
   char temp[200];
   borrow br;
   int flag =0;
   node *head1 = createborrow();
    if(head1 == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
   while(fgets(temp,sizeof(borrow),fp))
   {
       strcpy(br.name,strtok(temp,":"));
       strcpy(br.borrow_name,strtok(NULL,":"));
       strcpy(br.borrow_time,strtok(NULL,"-"));
       strcpy(br.return_time,strtok(NULL,"\n"));
       if(strcmp(br.name,name) == 0)
       {
           insertbrrrow(head1,br);
            flag =1;
       }   
   }
   if (flag == 1)
   {
       printf("您已订阅以下书籍：\n");
       printborrow(head1);
   }
   else
   {
       printf("您还没有订阅任何书籍！\n");
   }
   fclose(fp);
}
//获取当地时间
char *gettime(char *time_string, size_t size)
{
    time_t current_time;
    struct tm *local_time;

    // 获取当前时间
    current_time = time(NULL);

    // 将时间转换为本地时间
    local_time = localtime(&current_time);

    // 格式化时间字符串
    strftime(time_string, size, "%Y-%m-%d %H:%M:%S", local_time);

    return time_string;
}
// 计算截止时间
char *get_deadline(char *time_string, size_t size, int days)
{
    time_t current_time;
    struct tm *local_time;

    // 获取当前时间
    current_time = time(NULL);

    // 加上时间间隔
    current_time += days * 24 * 60 * 60;

    // 将时间转换为本地时间
    local_time = localtime(&current_time);

    // 格式化时间字符串
    strftime(time_string, size, "%Y-%m-%d %H:%M:%S", local_time);

    return time_string;
}
//删除用户
void deleteuser()
{
    node *head = createuser();
    char temp[200];
    USER Users;
    if(head == NULL)
    {
        printf("内存分配失败！");
        return ;
    }
    FILE *fp = fopen("user.txt","r");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    node *p = head;
    node *q = head;
    int flag =0;
    char name[50];
    printf("请输入用户名：");
    scanf("%s",name);
    while (fgets(temp, sizeof(USER), fp)!= NULL)
    {
         strcpy(Users.name,strtok(temp,":"));
         strcpy(Users.password,strtok(NULL,"\n"));
         insertuser(head,Users);
         if(strcmp(Users.name,name) == 0)
         {
            while(p->next)
            {
                if(strcmp(p->next->user.name,name)==0)
                {
                    flag =1;
                    node *temp = p->next;
                    p->next = temp->next;
                    free(temp);
                    break;
                }
                else
                {
                    p= p->next;
                }
            }
         }
    }
    if(flag == 0)
    {
        printf("用户名不存在！\n");
        return ;
    }
    fclose(fp);
    //更新文件中的数据
    fp = fopen("user.txt","w+");
    if(fp == NULL)
    {
        printf("文件打开失败！");
        return ;
    }
    while(head->next != NULL)
    {
        fprintf(fp,"%s:%s\n",head->next->user.name,head->next->user.password);
        head = head->next;
    }
    fclose(fp);
    printf("删除成功！\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAXSIZE 100 // 定义名字的字符数

typedef struct val {
    char childname[MAXSIZE]; // 节点中的孩子名
    struct val* next;
} val;//child节点 

typedef struct {
    char nodename[MAXSIZE];
    int childnum;//节点孩子数量 
    val* first;
} node;//链表头节点 

typedef struct {
    int size;//表头节点数 
    node* nodes;
    char code[6];//六位管理员密码 
} tree;//家族树 

tree t;//定义全局变量
int visited[MAXSIZE];//定义保存查找过的节点数组 
void menu1();//族谱系统 
void keydown1();// 族谱系统按键
void menu2();//查找系统 
void keydown2();// 查找系统按键
void menu3();//管理员系统目录
void managersystem();//管理员系统
void keydown3();//管理员系统按键 
void update();//更新系统,如果有人改名 
void Displaytree(tree* t);//输出族谱 
void updatecode(tree* t);//更新密码 
void update_node_name(tree* t); //修改姓名 

void Readcode(const char *str,tree* t)//传入密码 
{
	FILE *fp=fopen(str,"r");//打开文件 
	if(fp==NULL)
	{
		cout<<"无法打开文件"<<endl;
		return ; 
	}
	fscanf(fp,"%s\n", t->code);//读入密码 
	fclose(fp);//关闭文件 
} 

void Keepcode(const char* str,tree* t)//保存密码 
{
	FILE *fp=fopen(str,"w");
	if(fp==NULL)
	{
		cout<<"传入文件不存在"<<endl;
		return ; 
	} 
	fprintf(fp,"%s",t->code);//传入密码 
	fclose(fp);//关闭文件 
} 

void keeptree(const char* str ,tree* t)//保存族谱进入txt文件 
{
	FILE *fp = fopen(str, "w");//写入方式打开文件
	if(fp==NULL)
	{
		cout<<"文件不存在"<<endl;
		return ; 
	} 
	fprintf(fp,"%d\n",t->size);//输入节点数
	for(int i=0; i < t->size ; ++i)
	{
		fprintf(fp,"%s ",t->nodes[i].nodename);//输入节点名 
		fprintf(fp,"%d ",t->nodes[i].childnum);//输入节点孩子数 
		for(int j = 0;j < t->nodes[i].childnum; ++j) 
		{
			fprintf(fp,"%s ",t->nodes[i].first->childname);//遍历输入孩子名
			t->nodes[i].first = t->nodes[i].first->next;//将指针向后遍历 
		}
		fprintf(fp,"\n");//读入换行符，防止下一次打开文件产生错误
	}	
}

void Readtree(const char *str , tree* t) //创建邻接链表 (用txt文件传入) 
{
	FILE *fp=fopen(str,"r");
	if(fp==NULL)
	{
		cout<<"无法打开文件"<<endl;
		return ;
	}
	
    fscanf(fp,"%d\n", &t->size);
    t->nodes = (node*)malloc(sizeof(node) * t->size); // 给node开出t->size个空间
    int i;

    for (i = 0; i < t->size; ++i) {
        t->nodes[i].first = NULL; // 将first指针置为空
        fscanf(fp,"%s", t->nodes[i].nodename); // 传入nodename
        int j;
        fscanf(fp,"%d", &t->nodes[i].childnum);
        val* cur = NULL;
        for (j = 0; j < t->nodes[i].childnum; ++j) {
            val* newChild = (val*)malloc(sizeof(val));
            fscanf(fp,"%s\n", newChild->childname);
            newChild->next = NULL;
            if (cur == NULL) {
                t->nodes[i].first = newChild;
            } else {
                cur->next = newChild;
            }
            cur = newChild;
        }
    }
    fclose(fp);//关闭文件 
}

void confirmcode()//密码验证 
{
	int code_size;//密码长度
	char usercode[6];//用来存放输入密码
	cout<<"请输入密码"<<endl; 
	while(1)
	{
		cin>>usercode;//输入用户密码 
		usercode[6]='\0';
		code_size = strlen(usercode);//将输入的密码长度传入 
		if(code_size != 6)
		{
			cout<<"输入密码错误"<<endl;
			return  ;//退出密码验证函数 
		} 
		else{
			if(strcmp(usercode,t.code)==0)
			{
				cout<<"密码正确"<<endl;
				system("pause");
				system("cls");
				managersystem();//密码正确进入管理员系统 
			}
			else
			{
				cout<<"输入密码错误"<<endl;
				return ; 
			}
			
		}
	} 	 
}

void update_code(tree* t)//更新密码 
{
	char updatecode[6];//定义接收修改后的密码的数组
	int code_size;
	cout<<"请输入要修改的密码"<<endl; 
	cin>>updatecode;//输入修改后的密码 
	code_size = strlen(updatecode);
	if(code_size!=6)
	{
		cout<<"输入的格式不对"<<endl;
		cout<<"是否还要修改密码('Y'或'N')"<<endl;
		char key;
		cin>>key;
		if(key=='y'||key=='Y')
		{
			system("pause");
			system("cls");
			update_code(t);
		} 
		else if(key=='n'||key=='N')
		    return ;//退出修改函数 
	} 
	else
	{
		cout<<"你输入修改后的密码是"<<updatecode<<endl;
		cout<<"请确认要修改密码是否正确('Y'或'N')"<<endl;
		char reply;
		cin>>reply;
		if(reply=='Y'||reply=='y')
		{
			strcpy(t->code,updatecode);//修改密码 
			cout<<"修改操作成功"<<endl;
			cout<<"修改后的密码是： "<<t->code<<endl;
			system("pause");
			system("cls");
			return ; 
		} 
		else if(reply=='N'||reply=='n')
		{
			cout<<"修改操作取消"<<endl;
			system("pause");
			system("cls");
			return;//退出修改系统 
		} 
		else
		    cout<<"$输入错误，修改失败"<<endl;
			cout<<"$退出修改操作"<<endl; 
			system("pause");
			system("cls");
		    return ; //退出修改系统 
	}  
	return ; 
}

void update_node_name(tree* t ,int index)
{
	if(index==-1)
	{
		cout<<"该人不存在族谱中"<<endl;
		return ; 
    }
	char usedname[MAXSIZE] ;
	strcpy(usedname,t->nodes[index].nodename);//将index下标的名字传入原名             
	char aftername[MAXSIZE];
	cout<<"$请输入修改后的名字"<<endl;
	cin>>aftername;
	int i,mark;
	for(i=0 ;i < t->size;++i)
	{
		val* cur = t->nodes[i].first;//定义一个指针变量来遍历孩子链表 
		while(cur)
		{
			if(strcmp(usedname,cur->childname)==0) 
			{
				strcpy(cur->childname,aftername); 
			}
			cur = cur->next;
		} 
		if(strcmp(usedname,t->nodes[i].nodename)==0)
		{
			mark = i; 
		}
	} 
	strcpy(t->nodes[mark].nodename,aftername);
	system("cls");//清理页面  
} 

void Displaytree(tree* t)//输出族谱中所有的人名 
{
	for(int i=0 ;i < t->size; ++i)
	{
		printf("%s\t",t->nodes[i].nodename);
		while((i+1)%5==0)//每输出5个名字就换行 
		{
			printf("\n");
			break;//退出循环 
		}
	} 
	printf("\n$以上是族谱里留有名字的人$\n");
} 

void Displaytree_havechild(tree* t)//显示领接链表的族谱树内有孩子的人名和孩子名字 
{
    int i;
    for (i = 0; i < t->size; ++i) {
        val* cur = t->nodes[i].first;
        if (cur != NULL) {
            printf("%s的孩子有：", t->nodes[i].nodename);
            while (cur) {
                printf("%s\t", cur->childname);
                cur = cur->next;
            }
            printf("\n");
        }
    }
    system("pause");//页面暂停 
    system("cls"); //清理页面 
}

int findnodeindex(tree* t) //替换查找名字信息为表头下标 
{
    printf("请输入要进行操作的人名\n");
    char indexname[MAXSIZE];
    scanf("%s", indexname);
    for (int j = 0; j < t->size; ++j) {
        if (strcmp(indexname, t->nodes[j].nodename) == 0) {
            return j;
        }
    }
    cout<<"该人不存在族谱中"<<endl;
    system("pause");//页面暂停 
    system("cls");//清理页面 
    return -1; // 未找到返回-1 
}

void printchildname(tree* t, int index)//深度优先算法递归输出childname 
{
	if(index==-1)
	{
		cout<<"该人不存在族谱中"<<endl;
		return ; 
	} 
	else
	{  
		int visited[t->size]; // 用来记录查找过的后代
        for (int i = 0; i < t->size; ++i) 
	    {
            visited[i] = 0; // 初始化 visited 数组为 0
        }
        val* cur = t->nodes[index].first;
        if (cur == NULL) 
	    {
            return ;
        }
        while (cur != NULL) 
	    {
            cout<<cur->childname<<" ";
            int j;
            for (j = 0; j < t->size; ++j) 
		    {
                if (strcmp(cur->childname, t->nodes[j].nodename) == 0)
			    {
                    break;
                }
            }  
        if (j < t->size) 
		{
            if (visited[j] == 0) {
                visited[j] = 1; // 标记该节点为已访问
                printchildname(t,j);//递归输出孩子节点名字 
            }
        }
        cur = cur->next; // 继续遍历下一位孩子
        }
	}  
}

int countchildnum(tree* t, int index, int* visited) //输出子孙数量 
{
	if(index==-1)
	{
		return -1; 
	}
    val* cur = t->nodes[index].first;
    int count = 0;
    while (cur != NULL) {
        int j;
        for (j = 0; j < t->size; ++j) {
            if (strcmp(cur->childname, t->nodes[j].nodename) == 0) 
			{
                if (visited[j] == 0) 
				{
                    visited[j] = 1;
                    count += 1 + countchildnum(t, j, visited);
                }
                break;
            }
        }
        cur = cur->next;
    }
    return count;
}

void answer1(tree* t, int index, int num) //设计查找子孙数的回答
{
	if(index==-1||num==-1)
	{
		return ;
	}
    printf("\n查找到%s的子孙数是%d\n", t->nodes[index].nodename, num);
    return ; 
}

void answer2(int judge)//设计查找子孙名字的回答 
{
	if(judge==1)
	{
		printf("$该人的孩子有：\n");
	} 
}

void menu1()//设计系统主交互页面 
{
	printf("\t* * * * * * * * * * * * * * * * * * *\n");
	printf("\t*      【欢迎使用族谱系统】         *\n");
	printf("\t*         1.查看族谱                *\n");
    printf("\t*         2.进入查找系统            *\n");
    printf("\t*         3.进入管理员系统          *\n");
	printf("\t*         4.退出系统                *\n");
	printf("\t* 请输入对应的数字1-4进行相关操作:  *\n");
	printf("\t* * * * * * * * * * * * * * * * * * *\n");
}

void menu2()//设计查找系统交互页面 
{
	printf("\t* * * * * * * * * * * * * * * * * * *\n");
	printf("\t*      【欢迎使用查找系统】         *\n");
	printf("\t*         1.查看后代名字            *\n");
	printf("\t*         2.查看后代数量            *\n");
	printf("\t*         3.查看已有孩子的人        *\n");
	printf("\t*         4.退出系统                *\n");
	printf("\t* 请输入对应的数字1-3进行相关操作:  *\n");
	printf("\t* * * * * * * * * * * * * * * * * * *\n");
} 

void menu3()//设计管理员系统 
{
	printf("\t* * * * * * * * * * * * * * * * * * *\n");
	printf("\t*      【欢迎使用管理员系统】       *\n");
	printf("\t*         1.查看族谱                *\n");
	printf("\t*         2.修改名字                *\n");
	printf("\t*         3.修改系统密码            *\n");
	printf("\t*         4.退出管理员系统          *\n");
	printf("\t* 请输入对应的数字1-4进行相关操作:  *\n");
	printf("\t* * * * * * * * * * * * * * * * * * *\n");
} 

void findsystem()//查找系统 
{
	while(1)
	{
		menu2();
		keydown2();
		system("pause");//暂停当前页面 
		system("cls");//清空页面 
	}
	
} 

void managersystem()//管理员系统 
{
	while(1)
	{
		menu3(); 
		keydown3();
		system("pause");//暂停当前页面 
		system("cls");//清空页面 
	} 
} 

void keydown3()
{
	int keydown =0;
	cin>>keydown;
	switch(keydown)
	{
		case 0:
			cout<<"\t$退出系统$"<<endl;
			cout<<"\t$退出成功$"<<endl;
			system("pause");
			exit(0);//退出程序 
			break;
		case 1:
			Displaytree(&t);//输出族谱 
			break;
		case 2:
			{
			Displaytree(&t);//输出族谱 
			system("pause");//暂停界面 
			system("cls");//清理界面 
			int index = findnodeindex(&t);
			update_node_name(&t,index);//修改姓名 
			keeptree("genealogy.txt",&t);//保存修改后的族谱
			} 
			break;
		case 3:
			update_code(&t);//修改管理员密码 
			Keepcode("systemcode.txt",&t);//保存修改后的密码 
			break;
		case 4:
		    cout<<"\t$退出系统$"<<endl;
			cout<<"\t$退出成功$"<<endl;
			system("pause");
			exit(0);//退出程序 
			break;
		default :
			cout<<"\n$输入错误,请重新输入"<<endl;
			break;	
	}
} 

void keydown2()
{
	int keydown = 0;
	cin>>keydown;//输入按键值 
	switch(keydown)
	{
		case 0:
			cout<<"\t$退出系统$"<<endl;
			cout<<"\t$退出成功$"<<endl;
			system("pause");
			exit(0);//退出程序 
			break; 
		case 1://查找后代的名字 
		    {
		    	for(int i=0;i < t.size; ++i)//初始化visited函数 
		            {
			           visited[i]=0;
		            } 
		    	Displaytree(&t); 
		    	int index = findnodeindex(&t); 
		    	printchildname(&t,index);
			}
			break;
		case 2://查找后代的个数 
		    {
		    	for(int i=0;i < t.size; ++i)//初始化visited函数 
		            {
			           visited[i]=0;
		            } 
		    	Displaytree(&t);
		    	int index = findnodeindex(&t);
		    	int num = countchildnum(&t,index,visited);
		    	answer1(&t,index,num);
			} 
			break;
		case 3://输出有孩子节点的人名以及孩子名字 
		     Displaytree_havechild(&t); 
			 break; 
		case 4:
		      cout<<"\t$退出系统$"<<endl;
		      cout<<"\t$退出成功$"<<endl;
		      system("pause");//页面暂停 
		      exit(0);//退出系统 
		      break;
		default :
			cout<<"$输入错误,请重新输入$"<<endl; 
			break;
	}
} 

void keydown1()//设计族谱系统的按键操作 
{
	int keydown = 0;
	scanf("%d",&keydown);//输入按键值 
	switch(keydown)
	{
		case 0:
			printf("\t$退出系统$\n");
			printf("\t$退出成功$\n");
			system("pause");//页面暂停 
			exit(0);
			break;
		case 1:
		    Displaytree(&t);//显示族谱树 
		    break;
		case 2:
			system("cls");//清空界面 
			findsystem();//进入查找系统 
		    break;
		case 3:
			system("cls");//清空界面
			confirmcode();//进入密码验证界面,输入密码后进入管理员系统 
			break; 
		case 4:
			printf("\t$退出系统$\n");
			printf("\t$退出成功$\n");
			system("pause");//页面暂停 
			exit(0);
			break;
		default :
			printf("\t$输入错误$\n");
			printf("\t请重新输入!");
			break;	 
	}
	 
} 

void freetree(tree* t) //释放邻接链表的空间 
{
    for (int i = 0; i < t->size; ++i) 
	{
        val* cur = t->nodes[i].first;
        while (cur != NULL) 
		{
            val* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(t->nodes);
}

int main()//主函数 
{ 
    Readtree("genealogy.txt", &t);//读取文本文件里面的元素 
    Readcode("systemcode.txt",&t);//读入文本文件里的密码 
    for(int i=0;i < t.size; ++i)//初始化visited函数 
		{
			visited[i]=0;
		} 
	
    while(1)
    {
    	menu1();//打开界面 
		keydown1();//打开按键界面
		system("pause");//暂停界面
		system("cls");//清空界面 
	}
	keeptree("genealogy.txt",&t);//保存修改后的族谱
	Keepcode("systemcode.txt",&t);
    freetree(&t);//释放树空间 
    return 0; 
}

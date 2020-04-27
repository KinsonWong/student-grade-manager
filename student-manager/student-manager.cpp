// student-manager.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Node{
			int  id;						                             /*学号：主键，唯一*/
			char name[10];					                             /*姓名*/
			char sex[3];					                             /*性别：男或女*/
			char specialty[20];				                             /*专业*/
			char classes[20];				                             /*班级：唯一，不同班级不同*/
			enum studentcategory category;                               /*枚举型学生类别 本科生、研究生*/
			int  math;						                             /*高数*/
			int  english;					                             /*英语*/
			int  clanguage;					                             /*C语言*/
			int  comprehensive;				                             /*课程综合*/
			int  thesis;					                             /*毕业论文*/
			int  totalscore;				                             /*总成绩*/
			int  classrank;					                             /*班级排名*/
			int  schoolrank;				                             /*校级排名*/
			enum studentcategory{Undergraduate=1,Postgraduate=2};
			struct Node *next;
}NODE;

NODE *head;
void add_student_menu();                                                  /*添加学生菜单函数*/
NODE *add_student(int select,NODE *p2,int i);                             /*添加学生实现函数*/
void change_student_menu();                                               /*修改学生信息菜单函数*/
NODE *find_node(int number);                                              /*学号查找学生*/
void change_student_1();                                                  /*修改本科生信息*/
void change_student_2();                                                  /*修改研究生信息*/
void delete_student();                                                    /*删除学生信息*/    
void search_student_menu();                                               /*查询学生信息菜单函数*/
void show_student(NODE *p);                                               /*显示学生信息*/
void show_form();                                                         
void show_classes_student();                                              /*按班级显示学生信息*/
void show_id_student();                                                   /*按学号查下学生信息*/
void show_name_student();                                                 /*按姓名查询学生*/
void show_classes_fail_student();                                         /*显示某班不及格的学生*/                                       
void sort_student_menu();                                                 /*排序菜单函数*/
void sort_score_student();                                                /*全校学生按总分降序排序*/
void sort_class_score_student();                                          /*某班学生按总分降序排序*/
void statistic_student_menu();                                            /*统计学生信息菜单函数*/
double calculate_ave(char banji[20]);                                     /*计算某班某科平均分*/
void show_classes_ave_low_high();                                         /*显示某班某科最高、最低、平均分*/
void show_classes_over_ave_student();                                     /*显示某班某科超过平均分的学生信息*/
void show_classes_course_fail_student();                                  /*显示某班某科不及格的学生信息*/
void count_classes_course_grade();                                        /*科目评分函数*/
void get_course_grade(char banji[20],int sel);
void read_from_file();                                                    /*读取文件*/
void write_to_file();                                                     /*写入文件*/
void calculate_totalscore();                                              /*计算学生总成绩*/
void sort_all_student();                                                  /*所以学生按总分降序排序*/
void main()
{
	read_from_file();
	calculate_totalscore();
	int sel;
	while(1)
	{
		system("cls");
		printf("         学生成绩管理系统\n");
		printf("======================================\n");
		printf("1-添加学生信息      2-修改学生信息\n");
		printf("3-删除学生信息      4-查询学生信息\n");
		printf("5-学生成绩排序      6-学生信息统计\n");
		printf("0-退出\n");
		printf("======================================\n");
		printf("请输入选项：");
		scanf("%d",&sel);
		switch(sel){
		case 1:
			add_student_menu();
			break;
		case 2:
			change_student_menu();
			break;	
		case 3:
			delete_student();
			break;
		case 4:
			search_student_menu();
			break;
		case 5:
			sort_student_menu();
			break;
		case 6:
			statistic_student_menu();
			break;
		case 0:
			system("cls");
			printf("已退出学生成绩管理系统\n");
			return;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
		
	}
}
void add_student_menu()
{
	system("cls");
	int n,i,select;
	NODE *p2=NULL;
	printf("====================================\n");
	printf("请输入需要添加信息的学生的个数：");
	scanf("%d",&n);
	for(i=1;i<=n;)
	{
		printf("\n请选择学生类型(1-本科生  2-研究生):");
		scanf("%d",&select);
		if(select==1||select==2){
			p2=add_student(select,p2,i);
			i++;
		}
		else
			printf("选择错误，请重新选择\n");
	}
		calculate_totalscore();
		write_to_file();
}
NODE *add_student(int select,NODE *p2,int i)
{
	NODE *p1;
	if ((p1 = (NODE*)malloc(sizeof(NODE))) == NULL) {
		printf("不能成功分配存储块！\n");
		exit(0);
	}
	p1->next=NULL;
	if(select==1)
	{
		p1->category=(enum studentcategory)1;
		printf("\n请输入该本科生的个人信息\n");
		printf("姓名  性别  学号  专业   班级   高数成绩 英语成绩 C语言成绩\n");
		printf("===========================================================================\n");
		scanf("%s%s%d%s%s%d%d%d",&p1->name,&p1->sex,&p1->id,&p1->specialty,&p1->classes,&p1->math,&p1->english,&p1->clanguage);
		p1->comprehensive=0;
		p1->thesis=0;
	}
	else
	{
		p1->category=(enum studentcategory)2 ;
		printf("\n请输入该研究生的个人信息\n");
		printf("姓名  性别  学号  专业   班级   课程综合 毕业论文\n");
		printf("===========================================================================\n");
		scanf("%s%s%d%s%s%d%d",&p1->name,&p1->sex,&p1->id,&p1->specialty,&p1->classes,&p1->comprehensive,&p1->thesis);
		p1->math=0;
		p1->english=0;
		p1->clanguage=0;
	}
	if (i == 1)
		head = p1;
	else
		p2->next = p1;
	p2 = p1;
	return p2;
}
void change_student_menu()
{
	system("cls");
	int select;
	printf("(输入 0 返回主菜单)\n");
	printf("====================================\n");
	printf("请选择学生类型(1-本科生  2-研究生):");
	scanf("%d",&select);
	if(select==1)
		change_student_1();
	if(select==2)
		change_student_2();
	if(select==0)
		return;
	else{
		printf("输入错误");
		
	}
	calculate_totalscore();
    write_to_file();
}
NODE *find_node(int number)
{
	NODE *p;
	p = head;
	while ((p->id != number) && (p->next != NULL))
		p = p->next;
	if (p->id != number)
		p = NULL;
    return p;
}
void change_student_1()
{
	int id,select=-1;
	NODE *p;
	printf("请输入该本科生的学号：");
	scanf("%d",&id);
	p=find_node(id);
	if(p==NULL){
		printf("无该生信息\n");
	}
	else{
		while(select!=0){
			system("cls");
			printf("请选择需要修改的数据\n");
			printf("（1-姓名  2-性别  3-专业  4-班级  5-高数成绩  6-英语成绩  7-C语言成绩  0-返回）\n");
		    scanf("%d",&select);
			switch(select)
			{
			case 1:printf("请输入要修改的数据\n");scanf("%s",p->name);break;
			case 2:printf("请输入要修改的数据\n");scanf("%s",p->sex);break;
			case 3:printf("请输入要修改的数据\n");scanf("%s",p->specialty);break;
			case 4:printf("请输入要修改的数据\n");scanf("%s",p->classes);break;
			case 5:printf("请输入要修改的数据\n");scanf("%d",&p->math);break;
			case 6:printf("请输入要修改的数据\n");scanf("%d",&p->english);break;
			case 7:printf("请输入要修改的数据\n");scanf("%d",&p->clanguage);break;
			case 0:printf("\n返回\n"); return;break;
			default:printf("输入错误，请重新输入！\n"); break;
			}
		}
	}
}
void change_student_2()
{
	int id,select=-1;
	NODE *p;
	printf("请输入该研究生的学号：");
	scanf("%d",&id);
	p=find_node(id);
	if(p==NULL){
		printf("无该生信息");
	}
	else{
		while(select!=0){
			printf("请选择需要修改的数据");
			printf("1-姓名  2-性别  3-专业  4-班级  5-课程综合  6-毕业论文  0-返回\n");
		    scanf("%d",&select);
			switch(select)
			{
			case 1:printf("请输入要修改的数据\n");scanf("%s",p->name);break;
			case 2:printf("请输入要修改的数据\n");scanf("%s",p->sex);break;
			case 3:printf("请输入要修改的数据\n");scanf("%s",p->specialty);break;
			case 4:printf("请输入要修改的数据\n");scanf("%s",p->classes);break;
			case 5:printf("请输入要修改的数据\n");scanf("%d",&p->comprehensive);break;
			case 6:printf("请输入要修改的数据\n");scanf("%d",&p->thesis);break;
			case 0:printf("\n返回\n"); return;break;
			default:printf("输入错误，请重新输入！\n"); break;
			}
		}
	}
}
void delete_student()
{
	int num;
	NODE *p1,*p2;
	system("cls");
	printf("=========================\n");
	printf("请输入该学生的学号:");
	scanf("%d",&num);
	p1 = p2 = head;
	while ((p1->id != num) && (p1->next != NULL)) {
		p2 = p1;
		p1 = p1->next;
	}
	if (p1->id == num) {
		if (head == p1)
			head = p1->next;
		else
			p2->next = p1->next;
		free(p1);
	}
	else
		printf("未找到该学生\n");
	write_to_file();
}
void search_student_menu()
{
	system("cls");
	int select;
	NODE *p=head;
	printf("=====================================================\n");
	printf("1-显示全部学生信息      2-按班级显示学生信息\n");
	printf("3-用学号查找学生        4-用姓名查找学生\n");
	printf("5-查询某班某科成绩不及格学生\n");
	printf("0-返回\n");
	printf("=====================================================\n");
	printf("请选择要进行的操作：");
	scanf("%d",&select);
	switch(select)
	{
	    case 1:
		system("cls");printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *本科生名单*");
		show_form();
		while(p!=NULL){
			if(p->category==1){
				show_student(p);
				p=p->next;
			}
			else
				p=p->next;
		}
		printf("\n");
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *研究生名单*");
		show_form();
		p=head;
		while(p!=NULL){
			if(p->category==2){
				show_student(p);
				p=p->next;
			}
			else
				p=p->next;
		}
		printf("\n\n按回车返回\n");
		getchar();
		getchar();
		break;
		case 2:show_classes_student();break;
		case 3:show_id_student();break;
		case 4:show_name_student();break;
		case 5:show_classes_fail_student();break;
		case 0:return;break;
		default:printf("输入错误，请重新输入！\n"); break;
	}
}
void show_student(NODE *p)
{
	if(p->category==1)
		printf("\n%-8s%-8s%-8d%-12s%-18s%-11s%-6d%-7d%-10d%-10d%-10d%-10d%-12d%-11d",p->name,p->sex,p->id,p->specialty,p->classes,"本科生",p->math,p->english,p->clanguage,p->comprehensive,p->thesis,p->totalscore,p->classrank,p->schoolrank);
	else
		printf("\n%-8s%-8s%-8d%-12s%-18s%-11s%-6d%-7d%-10d%-10d%-10d%-10d%-12d%-11d",p->name,p->sex,p->id,p->specialty,p->classes,"研究生",p->math,p->english,p->clanguage,p->comprehensive,p->thesis,p->totalscore,p->classrank,p->schoolrank);
}
void show_form()
{
	printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("姓名   性别    学号       专业          班级         学生类型   高数  英语   C语言   课程综合   毕业论文   总成绩   班级排名   学校排名");
	printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");

}
void show_classes_student()
{
	NODE *p1=head;
	char banji[20];
	printf("请输入班级：");
	scanf("%s",banji);
	printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *本科生名单*");
		show_form();
		while(p1!=NULL){
			if(p1->category==1 && strcmp(p1->classes,banji)==0){
				show_student(p1);
				p1=p1->next;
			}
			else
				p1=p1->next;
		}
		printf("\n");
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *研究生名单*");
		show_form();
		p1=head;
		while(p1!=NULL){
			if(p1->category==2 && strcmp(p1->classes,banji)==0){
				show_student(p1);
				p1=p1->next;
			}
			else
				p1=p1->next;
		}
	    printf("\n");
		printf("\n按回车返回\n");
		getchar();
		getchar();
}
void show_id_student()
{
	NODE *p1=head;
	int number;
	printf("请输入学生学号:");
	scanf("%d",&number);
	show_form();
	if(p1->id==number)
		show_student(p1);
	else{
		printf("\n无该学生生信息！\n");
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	printf("\n按回车返回\n");
		getchar();
		getchar();
}
void show_name_student()
{
	NODE *p1=head;
	char xingming[10];
	printf("请输入学生姓名：");
	scanf("%s",xingming);
	show_form();
	if(strcmp(p1->name,xingming)==0)
		show_student(p1);
	else{
		printf("\n无该学生信息！\n");
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	printf("\n按回车返回\n");
		getchar();
		getchar();
}
void show_classes_fail_student()
{
	NODE *p1=head;
	char banji[20];
	int select;
	printf("请输入班级：");
	scanf("%s",banji);
	printf("请输入需要查询的科目(1-高数  2-英语  3-C语言  4-课程综合  5-毕业论文)：");
	scanf("%d",&select);
	show_form();
	while(p1!=NULL)
	{
		if(strcmp(p1->classes,banji)==0)
		{
			switch(select)
			{
			case 1:if(p1->math<60) show_student(p1);break;
			case 2:if(p1->english<60) show_student(p1);break;
			case 3:if(p1->clanguage<60) show_student(p1);break;
			case 4:if(p1->comprehensive<60) show_student(p1);break;
			case 5:if(p1->thesis<60) show_student(p1);break;
			default:printf("科目选择错误");
			}
		}
	}
}
void sort_student_menu()
{
	system("cls");
	int select;
	NODE *p1=head,*p2=head;
	int m=1,n=1,x=1,y=1;
	printf("=====================================\n");
	printf("1-全部学生按总成绩从高到低排序并显示\n");
	printf("2-某班学生按总成绩从高到低排序并显示\n");
	printf("0-返回\n");
	printf("=====================================\n");
	printf("请输入要进行的操作:");
	scanf("%d",&select);
	if(select==1){
		sort_all_student();
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *本科生名单*");
		show_form();
		while(p1!=NULL){
			if(p1->category==1){
				p1->schoolrank=m;
				show_student(p1);
				m++;
				p1=p1->next;
			}
			else
				p1=p1->next;
		}
		write_to_file();
		printf("\n");
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *研究生名单*");
		show_form();
		while(p2!=NULL){
			if(p2->category==2){
				p2->schoolrank=n;
				show_student(p2);
				n++;
				p2=p2->next;
			}
			else
				p2=p2->next;
		}
		write_to_file();
		printf("\n\n按回车返回\n");
		getchar();
		getchar();
	}
	if(select==2){
		p1=head;
		p2=head;
		sort_all_student();
		char banji[20];
	    printf("请输入班级：");
	    scanf("%s",banji);
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *本科生名单*");
		show_form();
		while(p1!=NULL){
			if(strcmp(p1->classes,banji)==0){
				if(p1->category==1){
					p1->classrank=x;
				    show_student(p1);
				    x++;
				    p1=p1->next;
				}
				else
					p1=p1->next;
			}
			else p1=p1->next;
		}
		write_to_file();
		printf("\n");
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *研究生名单*");
		show_form();
		while(p2!=NULL){
			if(strcmp(p2->classes,banji)==0){
				if(p2->category==2){
					p2->classrank=y;
				    show_student(p2);
				    y++;
			     	p2=p2->next;
				}
				else
					p2=p2->next;
			}
			else p2=p2->next;
		}
		write_to_file();
		printf("\n\n按回车返回\n");
		getchar();
		getchar();
	}
	if(select==0)
		return;
	else;	
}
void statistic_student_menu()
{
	system("cls");
	int select;
	printf("\n================================================================================================\n");
	printf("1-显示某班某课程的平均、最高和最低成绩    2-显示某班某课程超过课程平均成绩的学生名单及人数\n");
	printf("3-显示某班某课程不及格学生名单及人数      4-显示某班某课程不同等级的学生人数\n");
	printf("0-返回\n");
	printf("================================================================================================\n");
	printf("请输入要进行的操作:");
	scanf("%d",&select);
	switch(select)
	{
	case 1:show_classes_ave_low_high();break;
	case 2:show_classes_over_ave_student();break;
	case 3:show_classes_course_fail_student();break;
	case 4:count_classes_course_grade();break;
	case 0:return;
	default:printf("选择错误\n");break;
	}
}
double calculate_ave(char banji[20],int sel)
{
	NODE *p=head;
	int count,sum;
	count=0;
	sum=0;
	while(p!=NULL)
	{
		if(strcmp(p->classes,banji)==0 )
		{
			if(sel==1 && p->category==1){
				sum+=p->math;
				count++;
			}
			else if(sel==2 && p->category==1){
				sum+=p->english;
				count++;
			}
			else if(sel==3 && p->category==1){
				sum+=p->clanguage;
				count++;
			}
			else if(sel==4 && p->category==2){
				sum+=p->comprehensive;
				count++;
			}
			else if(sel==5 && p->category==2)
			{
				sum+=p->thesis;
				count++;
			}
			else 
				;
		}
		p=p->next;
	}
	return sum/count;
}	
void show_classes_ave_low_high()
{
	int select;
	double ave;
	NODE *p1=head,*ph,*pl;
	pl=ph=head;
	char banji[20];
	printf("请输入班级：");
	scanf("%s",banji);
	system("cls");
	printf("请输入需要查询的科目(1-高数  2-英语  3-C语言  4-课程综合  5-毕业论文)：");
	scanf("%d",&select);
	while(p1!=NULL)
	{
		if(select==1)
		{
			if(strcmp(p1->classes,banji)==0 && (p1->math>ph->math))
				ph=p1;
			while(pl!=NULL){             /*让pl指针指向本科生*/
					if(strcmp(pl->classes,banji)==0&&pl->category==1)
						break;
					else
						pl=pl->next;
				}
			if(strcmp(p1->classes,banji)==0 && (p1->math<pl->math) && p1->math!=0)
				pl=p1;
		}
		else if(select==2)
		{
			if(strcmp(p1->classes,banji)==0 && (p1->english>ph->english))
				ph=p1;
			while(pl!=NULL){              /*让pl指针指向本科生*/
					if(strcmp(pl->classes,banji)==0&&pl->category==1)
						break;
					else
						pl=pl->next;
				}
			if(strcmp(p1->classes,banji)==0 && (p1->english<pl->english) && p1->english!=0)
				pl=p1;
		}
		else if(select==3)
		{
			if(strcmp(p1->classes,banji)==0 && (p1->clanguage>ph->clanguage))
				ph=p1;
			while(pl!=NULL){            /*让pl指针指向本科生*/
					if(strcmp(pl->classes,banji)==0&&pl->category==1)
						break;
					else
						pl=pl->next;
				}
			if(strcmp(p1->classes,banji)==0 && (p1->clanguage<pl->clanguage) && p1->clanguage!=0)
				pl=p1;
		}
		else if(select==4)
		{
			if(strcmp(p1->classes,banji)==0 && (p1->comprehensive>ph->comprehensive))
				ph=p1;
			while(pl!=NULL){             /*让pl指针指向研究生*/
					if(strcmp(pl->classes,banji)==0&&pl->category==2)
						break;
					else
						pl=pl->next;
				}
			if(strcmp(p1->classes,banji)==0 && (p1->comprehensive<pl->comprehensive) && p1->comprehensive!=0)
				pl=p1;
		}
		else if(select==5)
		{
			if(p1->category==2){
				if(strcmp(p1->classes,banji)==0 && (p1->thesis>ph->thesis))
					ph=p1;
				while(pl!=NULL){         /*让pl指针指向研究生*/
					if(strcmp(pl->classes,banji)==0&&pl->category==2)
						break;
					else
						pl=pl->next;
				}
				if(strcmp(p1->classes,banji)==0 && (p1->thesis<pl->thesis))
					pl=p1;
			}
		}
		else
			printf("选择错误\n");
		p1=p1->next;
	}
	if(select==1)
	{
		ave=calculate_ave(banji,1);
		printf("该班高数的平均成绩为：%lf\n",ave);
		printf("该班高数的最高成绩为：%d\n",ph->math);
		printf("该班高数的最低成绩为：%d\n",pl->math);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else if(select==2)
	{
		ave=calculate_ave(banji,2);
		printf("该班英语的平均成绩为：%lf\n",ave);
		printf("该班英语的最高成绩为：%d\n",ph->english);
		printf("该班英语的最低成绩为：%d\n",pl->english);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else if(select==3)
	{
		ave=calculate_ave(banji,3);
		printf("该班C语言的平均成绩为：%lf\n",ave);
		printf("该班C语言的最高成绩为：%d\n",ph->clanguage);
		printf("该班C语言的最低成绩为：%d\n",pl->clanguage);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else if(select==4)
	{
		ave=calculate_ave(banji,4);
		printf("该班课程综合的平均成绩为：%lf\n",ave);
		printf("该班课程综合的最高成绩为：%d\n",ph->comprehensive);
		printf("该班课程综合的最低成绩为：%d\n",pl->comprehensive);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else if(select==5)
	{
		ave=calculate_ave(banji,5);
		printf("该班毕业论文的平均成绩为：%lf\n",ave);
		printf("该班毕业论文的最高成绩为：%d\n",ph->thesis);
		printf("该班毕业论文的最低成绩为：%d\n",pl->thesis);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else{
		printf("选择错误\n");
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
}
void show_classes_over_ave_student()
{
	int select;
	double ave;
	int count=0;
	NODE *p1=head;
	char banji[20];
	printf("请输入班级：");
	scanf("%s",banji);
	system("cls");
	printf("请输入需要查询的科目(1-高数  2-英语  3-C语言  4-课程综合  5-毕业论文)：");
	scanf("%d",&select);
	show_form();
	if(select==1)
	{
		ave=calculate_ave(banji,1);
		while(p1!=NULL)
		{
			
			if((strcmp(p1->classes, banji)==0) && (p1->math>=ave))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}
		printf("\n\n该班高数的平均成绩为：%lf\n",ave);	
		printf("该班高数超过平均成绩的人数为：%d\n",count);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else if(select==2)
	{
		ave=calculate_ave(banji,2);	
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->english>=ave))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
		    printf("\n\n该班英语的平均成绩为：%lf\n",ave);
			printf("该班英语超过平均成绩的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 
	else if(select==3)
	{
		ave=calculate_ave(banji,3);	
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->clanguage>=ave))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
		    printf("\n\n该班C语言的平均成绩为：%lf\n",ave);
			printf("该班C语言超过平均成绩的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 
	else if(select==4)
	{
	    ave=calculate_ave(banji,4);	
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->comprehensive>=ave))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
		    printf("\n\n该班课程综合的平均成绩为：%lf\n",ave);
			printf("该班课程综合超过平均成绩的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 		
	else if(select==5)
	{
		ave=calculate_ave(banji,5);	
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->thesis>=ave))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
		    printf("\n\n该班毕业论文的平均成绩为：%lf\n",ave);
			printf("该班毕业论文超过平均成绩的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 		
	else
		;
}
void show_classes_course_fail_student()
{
	int select;
	int count=0;
	NODE *p1=head;
	char banji[20];
	printf("请输入班级：");
	scanf("%s",banji);
	system("cls");
	printf("请输入需要查询的科目(1-高数  2-英语  3-C语言  4-课程综合  5-毕业论文)：");
	scanf("%d",&select);
	show_form();
	if(select==1)
	{
		while(p1!=NULL)
		{
			
			if((strcmp(p1->classes, banji)==0) && (p1->math<60) && (p1->category==1))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}
		printf("\n该班高数不及格人数为：%d\n",count);
		printf("\n按回车返回\n");
		getchar();
		getchar();
	}
	else if(select==2)
	{
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->english<60) && (p1->category==1))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
			printf("\n该班英语不及格的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 
	else if(select==3)
	{
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->clanguage<60) && (p1->category==1))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
			printf("\n该班C语言不及格的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 
	else if(select==4)
	{
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->comprehensive<60) && (p1->category==2))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
			printf("\n该班课程综合不及格的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 		
	else if(select==5)
	{
		while(p1!=NULL)
		{
			if((strcmp(p1->classes, banji)==0) && (p1->thesis<60) && (p1->category==2))
			{
				show_student(p1);
			    count++;
			}
			p1=p1->next;
		}		
			printf("该班毕业论文不及格的人数为：%d\n",count);
			printf("\n按回车返回\n");
		getchar();
		getchar();
	} 		
	else
		printf("选择错误\n");
}
void count_classes_course_grade()
{
	int select;
	char banji[20];
	printf("请输入班级：");
	scanf("%s",banji);
	system("cls");
	printf("请输入需要查询的科目(1-高数  2-英语  3-C语言  4-课程综合  5-毕业论文)：");
	scanf("%d",&select);
	get_course_grade(banji,select);
}
void get_course_grade(char banji[20],int sel)
{
	NODE *p=head;
	int score;
	int count1=0,count2=0,count3=0,count4=0,count5=0;
	while(p!=NULL){
		if(strcmp(p->classes, banji)==0)
		{
			if(sel==1)
		       score=p->math;
	        else if(sel==2)
		       score=p->english;
    	    else if(sel==3)
		       score=p->clanguage;
	        else if(sel==4)
		       score=p->comprehensive;
	        else if(sel==5)
		       score=p->thesis;
	        else
	    	   printf("选择错误");
			switch(score/10)
			{
			case 10:case 9:count1++;break;
			case 8:count2++;break;
			case 7:count3++;break;
			case 6:count4++;break;
			case 5:case 4:case 3:case 2:case 1:case 0:count5++;break;
			default:break;
			}
		}
		p=p->next;
	}
	printf("\n此科目等级为优的人数是%d\n",count1);
	printf("此科目等级为良的人数是%d\n",count2);
	printf("此科目等级为的中人数是%d\n",count3);
	printf("此科目等级为及格的人数是%d\n",count4);
	printf("此科目等级为不及格的人数是%d\n",count5);
	printf("\n按回车返回\n");
		getchar();
		getchar();
}
void read_from_file()
{
	NODE*p1 = NULL, *p2 = NULL;
	FILE*fp;
	if ((fp = fopen("student.txt", "r")) == NULL) {
		printf("\n不能打开文件！\n");
		exit(0);
	}
	while (!feof(fp)) {		                        /*文件不到末尾*/
		if ((p1 = (NODE*)malloc(sizeof(NODE))) == NULL) {
			printf("\n内存申请出错\n");
			fclose(fp);
			exit(0);
		}
		if (fread(p1, sizeof(NODE), 1, fp) != 1) {	/*读到末尾或者出错，跳出循环*/
			free(p1);
			break;
		}
		if (head == NULL)
			head = p2 = p1;
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	fclose(fp);
}
void write_to_file()
{
    NODE*p1;
	FILE*fp;
	if ((fp = fopen("student.txt", "w")) == NULL) {
		printf("\n不能打开文件！\n");
		exit(0);
	}
	p1 = head;
	while (p1 != NULL) {
		fwrite(p1, sizeof(NODE), 1, fp);
		p1 = p1->next;
	}
	fclose(fp);
}
void calculate_totalscore()
{
	NODE *p = head;
	while (p != NULL) {
		if (p->category == 1)
			p->totalscore = p->math+p->english+p->clanguage;
		else 
			p->totalscore = p->comprehensive+p->thesis;
		p = p->next;
	}
}
void sort_all_student()
{
	NODE *p, *pp, *s, *pt;
	if ((p = (NODE*)malloc(sizeof(NODE))) == NULL) {
		printf("不能成功分配存储块！\n");
		exit(0);
	}
	if ((pp = (NODE*)malloc(sizeof(NODE))) == NULL) {
		printf("不能成功分配存储块！\n");
		exit(0);
	}
	p->next=head;
	pp=p;
	s=p->next; 
	while (p->next!=NULL){
		while (s->next!=NULL){
				if (p->next->totalscore<s->next->totalscore){
						pt = p->next;
						p->next=s->next;
						s->next=p->next->next;
						p->next->next=pt;
				}
				else s = s->next;
		}
		p = p->next;
		s = p->next;
	}
	head = pp->next;              /*恢复头指针*/
}



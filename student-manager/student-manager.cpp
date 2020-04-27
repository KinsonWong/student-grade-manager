// student-manager.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Node{
			int  id;						                             /*ѧ�ţ�������Ψһ*/
			char name[10];					                             /*����*/
			char sex[3];					                             /*�Ա��л�Ů*/
			char specialty[20];				                             /*רҵ*/
			char classes[20];				                             /*�༶��Ψһ����ͬ�༶��ͬ*/
			enum studentcategory category;                               /*ö����ѧ����� ���������о���*/
			int  math;						                             /*����*/
			int  english;					                             /*Ӣ��*/
			int  clanguage;					                             /*C����*/
			int  comprehensive;				                             /*�γ��ۺ�*/
			int  thesis;					                             /*��ҵ����*/
			int  totalscore;				                             /*�ܳɼ�*/
			int  classrank;					                             /*�༶����*/
			int  schoolrank;				                             /*У������*/
			enum studentcategory{Undergraduate=1,Postgraduate=2};
			struct Node *next;
}NODE;

NODE *head;
void add_student_menu();                                                  /*���ѧ���˵�����*/
NODE *add_student(int select,NODE *p2,int i);                             /*���ѧ��ʵ�ֺ���*/
void change_student_menu();                                               /*�޸�ѧ����Ϣ�˵�����*/
NODE *find_node(int number);                                              /*ѧ�Ų���ѧ��*/
void change_student_1();                                                  /*�޸ı�������Ϣ*/
void change_student_2();                                                  /*�޸��о�����Ϣ*/
void delete_student();                                                    /*ɾ��ѧ����Ϣ*/    
void search_student_menu();                                               /*��ѯѧ����Ϣ�˵�����*/
void show_student(NODE *p);                                               /*��ʾѧ����Ϣ*/
void show_form();                                                         
void show_classes_student();                                              /*���༶��ʾѧ����Ϣ*/
void show_id_student();                                                   /*��ѧ�Ų���ѧ����Ϣ*/
void show_name_student();                                                 /*��������ѯѧ��*/
void show_classes_fail_student();                                         /*��ʾĳ�಻�����ѧ��*/                                       
void sort_student_menu();                                                 /*����˵�����*/
void sort_score_student();                                                /*ȫУѧ�����ֽܷ�������*/
void sort_class_score_student();                                          /*ĳ��ѧ�����ֽܷ�������*/
void statistic_student_menu();                                            /*ͳ��ѧ����Ϣ�˵�����*/
double calculate_ave(char banji[20]);                                     /*����ĳ��ĳ��ƽ����*/
void show_classes_ave_low_high();                                         /*��ʾĳ��ĳ����ߡ���͡�ƽ����*/
void show_classes_over_ave_student();                                     /*��ʾĳ��ĳ�Ƴ���ƽ���ֵ�ѧ����Ϣ*/
void show_classes_course_fail_student();                                  /*��ʾĳ��ĳ�Ʋ������ѧ����Ϣ*/
void count_classes_course_grade();                                        /*��Ŀ���ֺ���*/
void get_course_grade(char banji[20],int sel);
void read_from_file();                                                    /*��ȡ�ļ�*/
void write_to_file();                                                     /*д���ļ�*/
void calculate_totalscore();                                              /*����ѧ���ܳɼ�*/
void sort_all_student();                                                  /*����ѧ�����ֽܷ�������*/
void main()
{
	read_from_file();
	calculate_totalscore();
	int sel;
	while(1)
	{
		system("cls");
		printf("         ѧ���ɼ�����ϵͳ\n");
		printf("======================================\n");
		printf("1-���ѧ����Ϣ      2-�޸�ѧ����Ϣ\n");
		printf("3-ɾ��ѧ����Ϣ      4-��ѯѧ����Ϣ\n");
		printf("5-ѧ���ɼ�����      6-ѧ����Ϣͳ��\n");
		printf("0-�˳�\n");
		printf("======================================\n");
		printf("������ѡ�");
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
			printf("���˳�ѧ���ɼ�����ϵͳ\n");
			return;
		default:
			printf("ѡ�����������ѡ��\n");
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
	printf("��������Ҫ�����Ϣ��ѧ���ĸ�����");
	scanf("%d",&n);
	for(i=1;i<=n;)
	{
		printf("\n��ѡ��ѧ������(1-������  2-�о���):");
		scanf("%d",&select);
		if(select==1||select==2){
			p2=add_student(select,p2,i);
			i++;
		}
		else
			printf("ѡ�����������ѡ��\n");
	}
		calculate_totalscore();
		write_to_file();
}
NODE *add_student(int select,NODE *p2,int i)
{
	NODE *p1;
	if ((p1 = (NODE*)malloc(sizeof(NODE))) == NULL) {
		printf("���ܳɹ�����洢�飡\n");
		exit(0);
	}
	p1->next=NULL;
	if(select==1)
	{
		p1->category=(enum studentcategory)1;
		printf("\n������ñ������ĸ�����Ϣ\n");
		printf("����  �Ա�  ѧ��  רҵ   �༶   �����ɼ� Ӣ��ɼ� C���Գɼ�\n");
		printf("===========================================================================\n");
		scanf("%s%s%d%s%s%d%d%d",&p1->name,&p1->sex,&p1->id,&p1->specialty,&p1->classes,&p1->math,&p1->english,&p1->clanguage);
		p1->comprehensive=0;
		p1->thesis=0;
	}
	else
	{
		p1->category=(enum studentcategory)2 ;
		printf("\n��������о����ĸ�����Ϣ\n");
		printf("����  �Ա�  ѧ��  רҵ   �༶   �γ��ۺ� ��ҵ����\n");
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
	printf("(���� 0 �������˵�)\n");
	printf("====================================\n");
	printf("��ѡ��ѧ������(1-������  2-�о���):");
	scanf("%d",&select);
	if(select==1)
		change_student_1();
	if(select==2)
		change_student_2();
	if(select==0)
		return;
	else{
		printf("�������");
		
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
	printf("������ñ�������ѧ�ţ�");
	scanf("%d",&id);
	p=find_node(id);
	if(p==NULL){
		printf("�޸�����Ϣ\n");
	}
	else{
		while(select!=0){
			system("cls");
			printf("��ѡ����Ҫ�޸ĵ�����\n");
			printf("��1-����  2-�Ա�  3-רҵ  4-�༶  5-�����ɼ�  6-Ӣ��ɼ�  7-C���Գɼ�  0-���أ�\n");
		    scanf("%d",&select);
			switch(select)
			{
			case 1:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->name);break;
			case 2:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->sex);break;
			case 3:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->specialty);break;
			case 4:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->classes);break;
			case 5:printf("������Ҫ�޸ĵ�����\n");scanf("%d",&p->math);break;
			case 6:printf("������Ҫ�޸ĵ�����\n");scanf("%d",&p->english);break;
			case 7:printf("������Ҫ�޸ĵ�����\n");scanf("%d",&p->clanguage);break;
			case 0:printf("\n����\n"); return;break;
			default:printf("����������������룡\n"); break;
			}
		}
	}
}
void change_student_2()
{
	int id,select=-1;
	NODE *p;
	printf("��������о�����ѧ�ţ�");
	scanf("%d",&id);
	p=find_node(id);
	if(p==NULL){
		printf("�޸�����Ϣ");
	}
	else{
		while(select!=0){
			printf("��ѡ����Ҫ�޸ĵ�����");
			printf("1-����  2-�Ա�  3-רҵ  4-�༶  5-�γ��ۺ�  6-��ҵ����  0-����\n");
		    scanf("%d",&select);
			switch(select)
			{
			case 1:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->name);break;
			case 2:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->sex);break;
			case 3:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->specialty);break;
			case 4:printf("������Ҫ�޸ĵ�����\n");scanf("%s",p->classes);break;
			case 5:printf("������Ҫ�޸ĵ�����\n");scanf("%d",&p->comprehensive);break;
			case 6:printf("������Ҫ�޸ĵ�����\n");scanf("%d",&p->thesis);break;
			case 0:printf("\n����\n"); return;break;
			default:printf("����������������룡\n"); break;
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
	printf("�������ѧ����ѧ��:");
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
		printf("δ�ҵ���ѧ��\n");
	write_to_file();
}
void search_student_menu()
{
	system("cls");
	int select;
	NODE *p=head;
	printf("=====================================================\n");
	printf("1-��ʾȫ��ѧ����Ϣ      2-���༶��ʾѧ����Ϣ\n");
	printf("3-��ѧ�Ų���ѧ��        4-����������ѧ��\n");
	printf("5-��ѯĳ��ĳ�Ƴɼ�������ѧ��\n");
	printf("0-����\n");
	printf("=====================================================\n");
	printf("��ѡ��Ҫ���еĲ�����");
	scanf("%d",&select);
	switch(select)
	{
	    case 1:
		system("cls");printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *����������*");
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
		printf("                                                         *�о�������*");
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
		printf("\n\n���س�����\n");
		getchar();
		getchar();
		break;
		case 2:show_classes_student();break;
		case 3:show_id_student();break;
		case 4:show_name_student();break;
		case 5:show_classes_fail_student();break;
		case 0:return;break;
		default:printf("����������������룡\n"); break;
	}
}
void show_student(NODE *p)
{
	if(p->category==1)
		printf("\n%-8s%-8s%-8d%-12s%-18s%-11s%-6d%-7d%-10d%-10d%-10d%-10d%-12d%-11d",p->name,p->sex,p->id,p->specialty,p->classes,"������",p->math,p->english,p->clanguage,p->comprehensive,p->thesis,p->totalscore,p->classrank,p->schoolrank);
	else
		printf("\n%-8s%-8s%-8d%-12s%-18s%-11s%-6d%-7d%-10d%-10d%-10d%-10d%-12d%-11d",p->name,p->sex,p->id,p->specialty,p->classes,"�о���",p->math,p->english,p->clanguage,p->comprehensive,p->thesis,p->totalscore,p->classrank,p->schoolrank);
}
void show_form()
{
	printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("����   �Ա�    ѧ��       רҵ          �༶         ѧ������   ����  Ӣ��   C����   �γ��ۺ�   ��ҵ����   �ܳɼ�   �༶����   ѧУ����");
	printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");

}
void show_classes_student()
{
	NODE *p1=head;
	char banji[20];
	printf("������༶��");
	scanf("%s",banji);
	printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *����������*");
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
		printf("                                                         *�о�������*");
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
		printf("\n���س�����\n");
		getchar();
		getchar();
}
void show_id_student()
{
	NODE *p1=head;
	int number;
	printf("������ѧ��ѧ��:");
	scanf("%d",&number);
	show_form();
	if(p1->id==number)
		show_student(p1);
	else{
		printf("\n�޸�ѧ������Ϣ��\n");
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	printf("\n���س�����\n");
		getchar();
		getchar();
}
void show_name_student()
{
	NODE *p1=head;
	char xingming[10];
	printf("������ѧ��������");
	scanf("%s",xingming);
	show_form();
	if(strcmp(p1->name,xingming)==0)
		show_student(p1);
	else{
		printf("\n�޸�ѧ����Ϣ��\n");
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	printf("\n���س�����\n");
		getchar();
		getchar();
}
void show_classes_fail_student()
{
	NODE *p1=head;
	char banji[20];
	int select;
	printf("������༶��");
	scanf("%s",banji);
	printf("��������Ҫ��ѯ�Ŀ�Ŀ(1-����  2-Ӣ��  3-C����  4-�γ��ۺ�  5-��ҵ����)��");
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
			default:printf("��Ŀѡ�����");
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
	printf("1-ȫ��ѧ�����ܳɼ��Ӹߵ���������ʾ\n");
	printf("2-ĳ��ѧ�����ܳɼ��Ӹߵ���������ʾ\n");
	printf("0-����\n");
	printf("=====================================\n");
	printf("������Ҫ���еĲ���:");
	scanf("%d",&select);
	if(select==1){
		sort_all_student();
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *����������*");
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
		printf("                                                         *�о�������*");
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
		printf("\n\n���س�����\n");
		getchar();
		getchar();
	}
	if(select==2){
		p1=head;
		p2=head;
		sort_all_student();
		char banji[20];
	    printf("������༶��");
	    scanf("%s",banji);
		printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                         *����������*");
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
		printf("                                                         *�о�������*");
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
		printf("\n\n���س�����\n");
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
	printf("1-��ʾĳ��ĳ�γ̵�ƽ������ߺ���ͳɼ�    2-��ʾĳ��ĳ�γ̳����γ�ƽ���ɼ���ѧ������������\n");
	printf("3-��ʾĳ��ĳ�γ̲�����ѧ������������      4-��ʾĳ��ĳ�γ̲�ͬ�ȼ���ѧ������\n");
	printf("0-����\n");
	printf("================================================================================================\n");
	printf("������Ҫ���еĲ���:");
	scanf("%d",&select);
	switch(select)
	{
	case 1:show_classes_ave_low_high();break;
	case 2:show_classes_over_ave_student();break;
	case 3:show_classes_course_fail_student();break;
	case 4:count_classes_course_grade();break;
	case 0:return;
	default:printf("ѡ�����\n");break;
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
	printf("������༶��");
	scanf("%s",banji);
	system("cls");
	printf("��������Ҫ��ѯ�Ŀ�Ŀ(1-����  2-Ӣ��  3-C����  4-�γ��ۺ�  5-��ҵ����)��");
	scanf("%d",&select);
	while(p1!=NULL)
	{
		if(select==1)
		{
			if(strcmp(p1->classes,banji)==0 && (p1->math>ph->math))
				ph=p1;
			while(pl!=NULL){             /*��plָ��ָ�򱾿���*/
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
			while(pl!=NULL){              /*��plָ��ָ�򱾿���*/
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
			while(pl!=NULL){            /*��plָ��ָ�򱾿���*/
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
			while(pl!=NULL){             /*��plָ��ָ���о���*/
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
				while(pl!=NULL){         /*��plָ��ָ���о���*/
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
			printf("ѡ�����\n");
		p1=p1->next;
	}
	if(select==1)
	{
		ave=calculate_ave(banji,1);
		printf("�ð������ƽ���ɼ�Ϊ��%lf\n",ave);
		printf("�ð��������߳ɼ�Ϊ��%d\n",ph->math);
		printf("�ð��������ͳɼ�Ϊ��%d\n",pl->math);
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	else if(select==2)
	{
		ave=calculate_ave(banji,2);
		printf("�ð�Ӣ���ƽ���ɼ�Ϊ��%lf\n",ave);
		printf("�ð�Ӣ�����߳ɼ�Ϊ��%d\n",ph->english);
		printf("�ð�Ӣ�����ͳɼ�Ϊ��%d\n",pl->english);
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	else if(select==3)
	{
		ave=calculate_ave(banji,3);
		printf("�ð�C���Ե�ƽ���ɼ�Ϊ��%lf\n",ave);
		printf("�ð�C���Ե���߳ɼ�Ϊ��%d\n",ph->clanguage);
		printf("�ð�C���Ե���ͳɼ�Ϊ��%d\n",pl->clanguage);
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	else if(select==4)
	{
		ave=calculate_ave(banji,4);
		printf("�ð�γ��ۺϵ�ƽ���ɼ�Ϊ��%lf\n",ave);
		printf("�ð�γ��ۺϵ���߳ɼ�Ϊ��%d\n",ph->comprehensive);
		printf("�ð�γ��ۺϵ���ͳɼ�Ϊ��%d\n",pl->comprehensive);
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	else if(select==5)
	{
		ave=calculate_ave(banji,5);
		printf("�ð��ҵ���ĵ�ƽ���ɼ�Ϊ��%lf\n",ave);
		printf("�ð��ҵ���ĵ���߳ɼ�Ϊ��%d\n",ph->thesis);
		printf("�ð��ҵ���ĵ���ͳɼ�Ϊ��%d\n",pl->thesis);
		printf("\n���س�����\n");
		getchar();
		getchar();
	}
	else{
		printf("ѡ�����\n");
		printf("\n���س�����\n");
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
	printf("������༶��");
	scanf("%s",banji);
	system("cls");
	printf("��������Ҫ��ѯ�Ŀ�Ŀ(1-����  2-Ӣ��  3-C����  4-�γ��ۺ�  5-��ҵ����)��");
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
		printf("\n\n�ð������ƽ���ɼ�Ϊ��%lf\n",ave);	
		printf("�ð��������ƽ���ɼ�������Ϊ��%d\n",count);
		printf("\n���س�����\n");
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
		    printf("\n\n�ð�Ӣ���ƽ���ɼ�Ϊ��%lf\n",ave);
			printf("�ð�Ӣ�ﳬ��ƽ���ɼ�������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
		    printf("\n\n�ð�C���Ե�ƽ���ɼ�Ϊ��%lf\n",ave);
			printf("�ð�C���Գ���ƽ���ɼ�������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
		    printf("\n\n�ð�γ��ۺϵ�ƽ���ɼ�Ϊ��%lf\n",ave);
			printf("�ð�γ��ۺϳ���ƽ���ɼ�������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
		    printf("\n\n�ð��ҵ���ĵ�ƽ���ɼ�Ϊ��%lf\n",ave);
			printf("�ð��ҵ���ĳ���ƽ���ɼ�������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
	printf("������༶��");
	scanf("%s",banji);
	system("cls");
	printf("��������Ҫ��ѯ�Ŀ�Ŀ(1-����  2-Ӣ��  3-C����  4-�γ��ۺ�  5-��ҵ����)��");
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
		printf("\n�ð��������������Ϊ��%d\n",count);
		printf("\n���س�����\n");
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
			printf("\n�ð�Ӣ�ﲻ���������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
			printf("\n�ð�C���Բ����������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
			printf("\n�ð�γ��ۺϲ����������Ϊ��%d\n",count);
			printf("\n���س�����\n");
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
			printf("�ð��ҵ���Ĳ����������Ϊ��%d\n",count);
			printf("\n���س�����\n");
		getchar();
		getchar();
	} 		
	else
		printf("ѡ�����\n");
}
void count_classes_course_grade()
{
	int select;
	char banji[20];
	printf("������༶��");
	scanf("%s",banji);
	system("cls");
	printf("��������Ҫ��ѯ�Ŀ�Ŀ(1-����  2-Ӣ��  3-C����  4-�γ��ۺ�  5-��ҵ����)��");
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
	    	   printf("ѡ�����");
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
	printf("\n�˿�Ŀ�ȼ�Ϊ�ŵ�������%d\n",count1);
	printf("�˿�Ŀ�ȼ�Ϊ����������%d\n",count2);
	printf("�˿�Ŀ�ȼ�Ϊ����������%d\n",count3);
	printf("�˿�Ŀ�ȼ�Ϊ�����������%d\n",count4);
	printf("�˿�Ŀ�ȼ�Ϊ�������������%d\n",count5);
	printf("\n���س�����\n");
		getchar();
		getchar();
}
void read_from_file()
{
	NODE*p1 = NULL, *p2 = NULL;
	FILE*fp;
	if ((fp = fopen("student.txt", "r")) == NULL) {
		printf("\n���ܴ��ļ���\n");
		exit(0);
	}
	while (!feof(fp)) {		                        /*�ļ�����ĩβ*/
		if ((p1 = (NODE*)malloc(sizeof(NODE))) == NULL) {
			printf("\n�ڴ��������\n");
			fclose(fp);
			exit(0);
		}
		if (fread(p1, sizeof(NODE), 1, fp) != 1) {	/*����ĩβ���߳�������ѭ��*/
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
		printf("\n���ܴ��ļ���\n");
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
		printf("���ܳɹ�����洢�飡\n");
		exit(0);
	}
	if ((pp = (NODE*)malloc(sizeof(NODE))) == NULL) {
		printf("���ܳɹ�����洢�飡\n");
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
	head = pp->next;              /*�ָ�ͷָ��*/
}



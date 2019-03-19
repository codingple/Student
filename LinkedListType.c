#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_STUDENTS (200)

//�������� ����
typedef struct{
	int stu_num;
	char name[10];
	int age;
	char gender;
	float score;
}element;
//����� ����
typedef struct Student{
	element data;
	struct Student *before;     //���� ��带 ����ų �����ͺ���
	struct Student *after;     //���� ��带 ����ų �����ͺ���
}Student;
//��������Ϳ� ����Ʈ���̸� �����ϴ� ����ü
typedef struct{
	Student *head;     //���������
	int length;     //����� ����
}LinkedListType;
//������ ���
typedef struct StackNode{
	element data;
	struct StackNode *under;
}StackNode;
//������ ����
typedef struct{
	StackNode *top;
	int top_pos;
}LinkedStackType;






//////////////////////////////////�������̽� �Լ� ������Ÿ��//////////////////////////////////
void add_student (LinkedListType *list);					            //�л� ���� �߰�
void del_student(LinkedListType *list);                                 //�л� ���� ����
void sort_print(LinkedListType *list);						            //�л� ���� ����
void modify_student(LinkedListType *list);					            //�л� ���� ����
void search_student (LinkedListType *list, LinkedStackType *stack);     //�л� ���� �˻�
void last_student (LinkedStackType *stack);                             //���� �ֱ� �˻��� �л� ���� ���





//////////////////////////////////////��Ÿ �Լ� ������Ÿ��/////////////////////////////////////
element get_entry(LinkedListType *list, int pos);			            //������ ��ġ�� data�� ���ϴ� �Լ�
void add_last(LinkedListType *list, element d);				            //����Ʈ �������� ��� �߰�
void delete_pos(LinkedListType *list, int pos);				            //������ ��ġ�� ��带 �����ϴ� �Լ�
void init_list(LinkedListType *list);						            //����Ʈ �ʱ�ȭ
void add_pos(LinkedListType *list, element d, int pos);		            //����Ʈ�� ��� �߰�����
int search_pos(LinkedListType *list,Student *p);			            //�й��� ���Ͽ� �й��� ��ġ�� pos�� ��ȯ
void data_print(LinkedListType *list);						            //����� �����͸� ����ϴ� �Լ�
void init_stack(LinkedStackType *stack);                                //���� �ʱ�ȭ
void push(LinkedStackType *p, element d);                               //���� ���� �Լ�
void pop(LinkedStackType *p);                                           //���� pop �Լ�
void file_save(LinkedListType *list);                                   //���Ͽ� ����
void file_load(LinkedListType *list);                                   //���� �ҷ�����





///////////////////////////////////////////���� �Լ�//////////////////////////////////////////
int main (void) {
	LinkedListType list;
	LinkedStackType stack;
	int loof=1;
	int menu_select;
	int i;

	init_list(&list);
	init_stack(&stack);
	
	printf("============================================================\n");
	printf("�л��������α׷� 1.0ver\n");
	printf("============================================================\n");


	while(loof==1){
		printf("1.�Է�  2.����  3.����  4.�˻�  5.����  \n6.�ֱ��������  7.���  8.����/�ҷ�����  9.����\n");
		printf("�޴��� �����ϼ��� : ");
		scanf("%d",&menu_select);
		switch(menu_select){
			case 1:
				add_student(&list);
				printf("�Է��� �Ϸ�Ǿ����ϴ�.\n");
				break;
			case 2:
				modify_student(&list);
				break;
			case 3:
				del_student(&list);
				break;
			case 4:
				search_student(&list, &stack);
				break;
			case 5:
				sort_print(&list);
				break;
			case 6:
				last_student(&stack);
				break;
			case 7:
				data_print(&list);
				break;
			case 8:
				printf("1.���� ����  2.���� �ҷ�����\n��ɾ �Է��ϼ��� : ");
				scanf("%d", &i);

				switch (i){
			case 1 :
				file_save(&list);
				break;
			case 2:
				file_load(&list);
				break;
				}
				break;
			case 9:
				loof = 0;
				printf("���α׷��� ���� �մϴ�.\n");
				break;

			default:
				printf("�ùٸ� ���� �Է����ּ���.\n\n");

		}

		printf("\n\n");
	}

	return 0;
}





///////////////////////////////////////////�Լ� ����//////////////////////////////////////////
//���� �ʱ�ȭ
void init_stack(LinkedStackType *stack){
	stack->top = NULL;
	stack->top_pos = -1;
}

//���� �����Լ�
void push(LinkedStackType *p, element d){
	StackNode *new_node;
	new_node = (StackNode *)malloc(sizeof(StackNode));
	new_node->data = d;

	new_node->under = p->top;
	p->top = new_node;
	p->top_pos++;
}

//���� pop�Լ�
void pop(LinkedStackType *p){
	StackNode *f = p->top;
	element d = p->top->data;
	printf("�й�:%d  �̸�:%s  ����:%d  ����:%c  ����:%f\n",d.stu_num, d.name, d.age, d.gender, d.score);
	
	p->top = p->top->under;
	p->top_pos--;
	free(f);
}

//������ ��ġ�� data�� ���ϴ� �Լ�
element get_entry(LinkedListType *list, int pos){
	int i;
	element result;

	Student *p;
	p = (*list).head;

	for(i=0; i<pos+1; i++){
		result = p->data;
		p = p->after;
	}

	return result;
}


//����Ʈ �������� ��� �߰�
void add_last(LinkedListType *list, element d){
	Student *p;
	Student *new_node;
	p = list->head;

	new_node = (Student *)malloc(sizeof(Student));
	new_node->after = NULL;
	new_node->before = NULL;

	// ����Ʈ�� ù��° ��� ����
	if( p == NULL ){
		list->head = new_node;
	}
	// �ι�° ������ ����
	else{
		while( p->after != NULL ){
			p = p->after;
		}
		p->after = new_node;
		new_node->before = p;
	}

	new_node->data = d;

	(list->length)++;
}


//������ ��ġ�� ��带 �����ϴ� �Լ�
void delete_pos(LinkedListType *list, int pos){
	int i;
	Student *p;
	p = list->head;

	//ù��° ��带 ����
	if(pos == 0){
		list->head = p->after;
		p->before = NULL;
	}

	//������ ��带 ����
	else if(pos == (list->length)-1){
		while( p->after != NULL )
			p = p->after;
		p->before->after = NULL;
	}
	//�߰� ��带 ����
	else{
		for(i=0; i<pos; i++)
			p = p->after;
		(p->before->after) = p->after;
		(p->after->before) = p->before;
	}

	free(p);
	list->length--;

}


//����Ʈ �ʱ�ȭ
void init_list(LinkedListType *list){
	list->head = NULL;
	list->length = 0;
}


//����Ʈ�� ��� �߰�����
void add_pos(LinkedListType *list, element d, int pos){
	int i;
	Student *p = list->head;
	Student *new_node;

	//new_node �ʱ�ȭ
	new_node = (Student *)malloc(sizeof(Student));
	new_node->after = NULL;
	new_node->before = NULL;

	//p�� ����� ��ġ�� ����Ų��
	for(i=0; i<pos; i++)
		p = p->after;

	//new_node�� ù��°�϶�
	if(pos == 0){
		p->before = new_node;
		new_node->after = p;
		list->head = new_node;
	}

	//new_node�� p ��ġ�� ����
	else{
		new_node->after = p;
		(p->before->after) = new_node;
		new_node->before = p->before;
		p->before = new_node;
	}

	//������ ����
	new_node->data = d;

	(list->length)++;
}

//�й��� ���Ͽ� �й��� ��ġ�� pos�� ��ȯ
int search_pos(LinkedListType *list,Student *p){
	int pos=0;
	Student *step_p;
	step_p = list->head;
	while((step_p->data.stu_num) != (p->data.stu_num)){
		step_p = step_p->after;
		pos++;
	}

	return pos;
}



//����Ʈ ��ü ���
void data_print(LinkedListType *list){
   Student *p = list->head;
   while(p != NULL){
	   printf("�й�:%d  �̸�:%s  ����:%d  ����:%c  ����:%f\n",p->data.stu_num,p->data.name,p->data.age,p->data.gender,p->data.score);
      p = p->after;
   }
}

//���� ����
void file_save(LinkedListType *list){
	Student *p = list->head;
	char file_name[20];
	FILE *f;

	printf("������ ������ �̸��� �Է��ϼ��� : ");
	scanf("%s", file_name);
	f = fopen(file_name, "wt");

	while ( p != NULL ){
		fprintf(f, "%d", p->data.stu_num);
		fputs(" ", f);
		fprintf(f, "%s", p->data.name);
		fputs(" ", f);
		fprintf(f, "%d", p->data.age);
		fputs(" ", f);
		fprintf(f, "%c", p->data.gender);
		fputs(" ", f);
		fprintf(f, "%f", p->data.score);
		fputs(" ", f);
		fputs("\n", f);

		p = p->after;
	}

	fclose(f);
	printf("������ �Ϸ�Ǿ����ϴ�.\n");
}


//���� �ҷ�����
void file_load(LinkedListType *list){
	char file_name[20];
	FILE *fp;
	Student *p = list->head;
	Student *temp;
	element d;

	printf("�ҷ��� ������ �̸��� �Է��ϼ��� : ");
	scanf("%s", file_name);

	fp = fopen(file_name, "rt");

	if( p != NULL){
		printf("�ۼ����̴� �����Ͱ� �սǵ˴ϴ�.\n");

		while ( p != NULL){
			temp = p->after;
			free(p);
			p = temp;
		}

		list->head = NULL;
	}

	while( 1 ){
		fscanf(fp, "%d %s %d %c %f", &d.stu_num, d.name, &d.age, &d.gender, &d.score);
		if (feof(fp) != 0 )
			break;
		add_last(list,d);
		
	}
	printf("���� �ε尡 �Ϸ�Ǿ����ϴ�.\n");
	fclose(fp);

}

		
		



/////////////////////////�������̽� �Լ� ����///////////////////////////////

//�л� ���� �߰�
void add_student (LinkedListType *list){
	int one;
	char two[10];
	int three;
	char four;
	float five;
	Student *p;
	Student *h;
	element d;

	printf("�й�, �̸�, ����, ����, ������ �Է��Ͻÿ� : ");
	scanf("%d %s %d %c %f", &one, two, &three, &four, &five);

	d.stu_num = one;
	strcpy(d.name, two);
	d.age = three;
	d.gender = four;
	d.score = five;

	add_last(list, d);

	
	//���������� �̿��� �й��� ����Ʈ����
	if(list->length>=2){

		//p�� h�� ������ ��带 ����Ŵ
		p = list->head;
		while ( (p->after) != NULL )
			p = p->after;
		h = p;

		//p�� �й��� �� �� add_last�� ��尡 ������ ��ġ�� ����Ŵ
		while((h->data.stu_num) < (p->before->data.stu_num)){
			p = p->before;
			//p�� ù��° ����� ���
			if( p->before == NULL )
				break;
		}

		//p�� �̵��ߴٸ�, add_last�� ��尡 �Ű������Ѵٸ�
		if( h != p ){
			add_pos(list, h->data, search_pos(list, p));
			delete_pos( list, (list->length)-1 );
		}
	}

}


//�л� ���� ����
void sort_print(LinkedListType *list){
   int menu;
   int i,j,k;
   Student *p;
   element temp;
   printf("� �׸��� ������� �����ұ��?\n");
   printf("1. �й�  2. �̸�  3. ����  4. ����  5. ����\n");
   scanf("%d",&menu);

   switch(menu){

      case 1://�й��� ����
         for(i=0; i<list->length-1; i++){ //'�Ʒ��� for��'�� list�� ���̸�ŭ �ݺ��ϰ� �ϴ� for���̴�.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
               k = (p->data.stu_num) - (p->after->data.stu_num);   //�񱳰� ���ٸ� k=0, p�� ũ�ٸ� 0�ʰ���, p�� �۴ٸ� 0�̸���
               if(k > 0){        //����, p�� �������� ����� p->after�� ������� Ŭ���
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break;

      case 2://�̸��� ����
         for(i=0; i<list->length-1; i++){ //'�Ʒ��� for��'�� list�� ���̸�ŭ �ݺ��ϰ� �ϴ� for���̴�.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
               k = strcmp(p->data.name, p->after->data.name);   //�񱳰� ���ٸ� k=0, p�� ũ�ٸ� 0�ʰ���, p�� �۴ٸ� 0�̸���
               if(k > 0){        //����, p�� �������� ����� p->after�� ������� Ŭ���
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break;

      case 3://���̼� ����
         for(i=0; i<list->length-1; i++){ //'�Ʒ��� for��'�� list�� ���̸�ŭ �ݺ��ϰ� �ϴ� for���̴�.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
               k = (p->data.age) - (p->after->data.age);   //�񱳰� ���ٸ� k=0, p�� ũ�ٸ� 0�ʰ���, p�� �۴ٸ� 0�̸���
               if(k > 0){        //����, p�� �������� ����� p->after�� ������� Ŭ���
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break;         

      case 4://������ ����
         for(i=0; i<list->length-1; i++){ //'�Ʒ��� for��'�� list�� ���̸�ŭ �ݺ��ϰ� �ϴ� for���̴�.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
				k = (p->data.gender) - (p->after->data.age);   //�񱳰� ���ٸ� k=0, p�� ũ�ٸ� 0�ʰ���, p�� �۴ٸ� 0�̸���
               if(k > 0){        //����, p�� �������� ����� p->after�� ������� Ŭ���
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break; 

      case 5://������ ����
         for(i=0; i<list->length-1; i++){ //'�Ʒ��� for��'�� list�� ���̸�ŭ �ݺ��ϰ� �ϴ� for���̴�.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
				k = (p->data.score) - (p->after->data.score);   //�񱳰� ���ٸ� k=0, p�� ũ�ٸ� 0�ʰ���, p�� �۴ٸ� 0�̸���
               if(k > 0){        //����, p�� �������� ����� p->after�� ������� Ŭ���
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break; 

      default:
         printf("�ùٸ� ��ɰ��� �Է����� �ʾҽ��ϴ�.\n");
   }
   data_print(list);
}

//�л����� ����
void modify_student(LinkedListType *list){
	Student *p;
	int num;
	int modify_select;
	int new_stu_num, new_age;
	float new_score;
	char new_name[10];
	char new_gender;

	printf("������ �л��� �й��� �Է��ϼ��� : ");
	scanf("%d",&num);
	p = list->head;
	while((p->data.stu_num) != num)
		p = p->after;
	
	printf("�й�:%d  �̸�:%s  ����:%d  ����:%c  ����:%f\n",p->data.stu_num,p->data.name,p->data.age,p->data.gender,p->data.score);
	printf("1.�й�  2.�̸�  3.����\n������ �����͸� ������ : ");
	scanf("%d",&modify_select);
	
	switch(modify_select){
		case 1:
			printf("������ �й��� �Է����ּ��� : ");
			scanf("%d",&new_stu_num);
			p->data.stu_num = new_stu_num;
			printf("�й� ������ �Ϸ� �Ǿ����ϴ�.");
			break;
		case 2:
			printf("������ �̸��� �Է����ּ��� : ");
			scanf("%s",&new_name);
			strcpy(p->data.name,new_name);
			printf("�̸� ������ �Ϸ� �Ǿ����ϴ�.");
			break;
		case 3:
			printf("������ ���̸� �Է����ּ��� : ");
			scanf("%d",&new_age);
			p->data.age = new_age;
			printf("���� ������ �Ϸ� �Ǿ����ϴ�.");
			break;
		case 4:
			printf("������ ������ �Է����ּ��� : ");
			scanf("%c",&new_gender);
			p->data.gender = new_gender;
			printf("���� ������ �Ϸ� �Ǿ����ϴ�.");
			break;
		case 5:
			printf("������ ������ �Է����ּ��� : ");
			scanf("%f",&new_score);
			p->data.score = new_score;
			printf("���� ������ �Ϸ� �Ǿ����ϴ�.");
			break;
		default:
			printf("�߸��� ���� �Է��ϼ̽��ϴ�.");
	}

}

//�л� �˻�
void search_student (LinkedListType *list, LinkedStackType *stack){
	int num;
	Student *p = list->head;

	printf("�й��� �Է��ϼ��� : ");
	scanf("%d", &num);

	while( p != NULL ){
		if ( (p->data.stu_num) == num )
			break;
		p = p ->after;
	}

	if( p == NULL)
		printf("�л������� �����ϴ�.\n");
	else{
		printf("�й�:%d  �̸�:%s  ����:%d  ����:%c  ����:%f\n", p->data.stu_num, p->data.name, p->data.age, p->data.gender, p->data.score);
		push(stack, p->data);
	}
}

//���� �ֱ� �˻��� �л� ����
void last_student (LinkedStackType *stack){
	pop(stack);
}

//�л� ���� ����
void del_student(LinkedListType *list){
   Student *p;
   int num;
   int pos;
   printf("������ �л��� �й��� �Է��ϼ��� : ");
   scanf("%d",&num);
   p = list->head;
   while(p->data.stu_num != num)
      p = p->after;
   pos = search_pos(list, p);
   delete_pos(list, pos);

   printf("������ �Ϸ�Ǿ����ϴ�.\n");
}
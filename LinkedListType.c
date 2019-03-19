#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_STUDENTS (200)

//데이터의 구조
typedef struct{
	int stu_num;
	char name[10];
	int age;
	char gender;
	float score;
}element;
//노드의 구조
typedef struct Student{
	element data;
	struct Student *before;     //이전 노드를 가리킬 포인터변수
	struct Student *after;     //다음 노드를 가리킬 포인터변수
}Student;
//헤드포인터와 리스트길이를 저장하는 구조체
typedef struct{
	Student *head;     //헤드포인터
	int length;     //노드의 개수
}LinkedListType;
//스택의 노드
typedef struct StackNode{
	element data;
	struct StackNode *under;
}StackNode;
//스택의 구조
typedef struct{
	StackNode *top;
	int top_pos;
}LinkedStackType;






//////////////////////////////////인터페이스 함수 프로토타입//////////////////////////////////
void add_student (LinkedListType *list);					            //학생 정보 추가
void del_student(LinkedListType *list);                                 //학생 정보 삭제
void sort_print(LinkedListType *list);						            //학생 정보 정렬
void modify_student(LinkedListType *list);					            //학생 정보 수정
void search_student (LinkedListType *list, LinkedStackType *stack);     //학생 정보 검색
void last_student (LinkedStackType *stack);                             //가장 최근 검색한 학생 정보 출력





//////////////////////////////////////기타 함수 프로토타입/////////////////////////////////////
element get_entry(LinkedListType *list, int pos);			            //정해진 위치에 data를 구하는 함수
void add_last(LinkedListType *list, element d);				            //리스트 마지막에 노드 추가
void delete_pos(LinkedListType *list, int pos);				            //정해진 위치의 노드를 삭제하는 함수
void init_list(LinkedListType *list);						            //리스트 초기화
void add_pos(LinkedListType *list, element d, int pos);		            //리스트에 노드 중간삽입
int search_pos(LinkedListType *list,Student *p);			            //학번을 비교하여 학번이 위치한 pos를 반환
void data_print(LinkedListType *list);						            //노드의 데이터를 출력하는 함수
void init_stack(LinkedStackType *stack);                                //스택 초기화
void push(LinkedStackType *p, element d);                               //스택 삽입 함수
void pop(LinkedStackType *p);                                           //스택 pop 함수
void file_save(LinkedListType *list);                                   //파일에 저장
void file_load(LinkedListType *list);                                   //파일 불러오기





///////////////////////////////////////////메인 함수//////////////////////////////////////////
int main (void) {
	LinkedListType list;
	LinkedStackType stack;
	int loof=1;
	int menu_select;
	int i;

	init_list(&list);
	init_stack(&stack);
	
	printf("============================================================\n");
	printf("학생관리프로그램 1.0ver\n");
	printf("============================================================\n");


	while(loof==1){
		printf("1.입력  2.수정  3.삭제  4.검색  5.정렬  \n6.최근정보출력  7.출력  8.저장/불러오기  9.종료\n");
		printf("메뉴를 선택하세요 : ");
		scanf("%d",&menu_select);
		switch(menu_select){
			case 1:
				add_student(&list);
				printf("입력이 완료되었습니다.\n");
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
				printf("1.파일 저장  2.파일 불러오기\n명령어를 입력하세요 : ");
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
				printf("프로그램을 종료 합니다.\n");
				break;

			default:
				printf("올바른 값을 입력해주세요.\n\n");

		}

		printf("\n\n");
	}

	return 0;
}





///////////////////////////////////////////함수 내용//////////////////////////////////////////
//스택 초기화
void init_stack(LinkedStackType *stack){
	stack->top = NULL;
	stack->top_pos = -1;
}

//스택 삽입함수
void push(LinkedStackType *p, element d){
	StackNode *new_node;
	new_node = (StackNode *)malloc(sizeof(StackNode));
	new_node->data = d;

	new_node->under = p->top;
	p->top = new_node;
	p->top_pos++;
}

//스택 pop함수
void pop(LinkedStackType *p){
	StackNode *f = p->top;
	element d = p->top->data;
	printf("학번:%d  이름:%s  나이:%d  성별:%c  평점:%f\n",d.stu_num, d.name, d.age, d.gender, d.score);
	
	p->top = p->top->under;
	p->top_pos--;
	free(f);
}

//정해진 위치에 data를 구하는 함수
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


//리스트 마지막에 노드 추가
void add_last(LinkedListType *list, element d){
	Student *p;
	Student *new_node;
	p = list->head;

	new_node = (Student *)malloc(sizeof(Student));
	new_node->after = NULL;
	new_node->before = NULL;

	// 리스트의 첫번째 노드 삽입
	if( p == NULL ){
		list->head = new_node;
	}
	// 두번째 노드부터 삽입
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


//정해진 위치의 노드를 삭제하는 함수
void delete_pos(LinkedListType *list, int pos){
	int i;
	Student *p;
	p = list->head;

	//첫번째 노드를 삭제
	if(pos == 0){
		list->head = p->after;
		p->before = NULL;
	}

	//마지막 노드를 삭제
	else if(pos == (list->length)-1){
		while( p->after != NULL )
			p = p->after;
		p->before->after = NULL;
	}
	//중간 노드를 삭제
	else{
		for(i=0; i<pos; i++)
			p = p->after;
		(p->before->after) = p->after;
		(p->after->before) = p->before;
	}

	free(p);
	list->length--;

}


//리스트 초기화
void init_list(LinkedListType *list){
	list->head = NULL;
	list->length = 0;
}


//리스트에 노드 중간삽입
void add_pos(LinkedListType *list, element d, int pos){
	int i;
	Student *p = list->head;
	Student *new_node;

	//new_node 초기화
	new_node = (Student *)malloc(sizeof(Student));
	new_node->after = NULL;
	new_node->before = NULL;

	//p로 삽압할 위치를 가리킨다
	for(i=0; i<pos; i++)
		p = p->after;

	//new_node가 첫번째일때
	if(pos == 0){
		p->before = new_node;
		new_node->after = p;
		list->head = new_node;
	}

	//new_node를 p 위치에 삽입
	else{
		new_node->after = p;
		(p->before->after) = new_node;
		new_node->before = p->before;
		p->before = new_node;
	}

	//데이터 삽입
	new_node->data = d;

	(list->length)++;
}

//학번을 비교하여 학번이 위치한 pos를 반환
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



//리스트 전체 출력
void data_print(LinkedListType *list){
   Student *p = list->head;
   while(p != NULL){
	   printf("학번:%d  이름:%s  나이:%d  성별:%c  평점:%f\n",p->data.stu_num,p->data.name,p->data.age,p->data.gender,p->data.score);
      p = p->after;
   }
}

//파일 저장
void file_save(LinkedListType *list){
	Student *p = list->head;
	char file_name[20];
	FILE *f;

	printf("저장할 파일의 이름을 입력하세요 : ");
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
	printf("저장이 완료되었습니다.\n");
}


//파일 불러오기
void file_load(LinkedListType *list){
	char file_name[20];
	FILE *fp;
	Student *p = list->head;
	Student *temp;
	element d;

	printf("불러올 파일의 이름을 입력하세요 : ");
	scanf("%s", file_name);

	fp = fopen(file_name, "rt");

	if( p != NULL){
		printf("작성중이던 데이터가 손실됩니다.\n");

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
	printf("파일 로드가 완료되었습니다.\n");
	fclose(fp);

}

		
		



/////////////////////////인터페이스 함수 내용///////////////////////////////

//학생 정보 추가
void add_student (LinkedListType *list){
	int one;
	char two[10];
	int three;
	char four;
	float five;
	Student *p;
	Student *h;
	element d;

	printf("학번, 이름, 나이, 성별, 평점을 입력하시오 : ");
	scanf("%d %s %d %c %f", &one, two, &three, &four, &five);

	d.stu_num = one;
	strcpy(d.name, two);
	d.age = three;
	d.gender = four;
	d.score = five;

	add_last(list, d);

	
	//삽입정렬을 이용한 학번순 리스트정렬
	if(list->length>=2){

		//p와 h가 마지막 노드를 가리킴
		p = list->head;
		while ( (p->after) != NULL )
			p = p->after;
		h = p;

		//p는 학번을 비교 후 add_last된 노드가 가야할 위치를 가리킴
		while((h->data.stu_num) < (p->before->data.stu_num)){
			p = p->before;
			//p가 첫번째 노드일 경우
			if( p->before == NULL )
				break;
		}

		//p가 이동했다면, add_last된 노드가 옮겨져야한다면
		if( h != p ){
			add_pos(list, h->data, search_pos(list, p));
			delete_pos( list, (list->length)-1 );
		}
	}

}


//학생 정보 정렬
void sort_print(LinkedListType *list){
   int menu;
   int i,j,k;
   Student *p;
   element temp;
   printf("어떤 항목을 대상으로 정렬할까요?\n");
   printf("1. 학번  2. 이름  3. 나이  4. 성별  5. 평점\n");
   scanf("%d",&menu);

   switch(menu){

      case 1://학번순 정렬
         for(i=0; i<list->length-1; i++){ //'아래의 for문'을 list의 길이만큼 반복하게 하는 for문이다.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
               k = (p->data.stu_num) - (p->after->data.stu_num);   //비교가 같다면 k=0, p가 크다면 0초과값, p가 작다면 0미만값
               if(k > 0){        //만약, p의 데이터의 멤버가 p->after의 멤버보다 클경우
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break;

      case 2://이름순 정렬
         for(i=0; i<list->length-1; i++){ //'아래의 for문'을 list의 길이만큼 반복하게 하는 for문이다.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
               k = strcmp(p->data.name, p->after->data.name);   //비교가 같다면 k=0, p가 크다면 0초과값, p가 작다면 0미만값
               if(k > 0){        //만약, p의 데이터의 멤버가 p->after의 멤버보다 클경우
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break;

      case 3://나이순 정렬
         for(i=0; i<list->length-1; i++){ //'아래의 for문'을 list의 길이만큼 반복하게 하는 for문이다.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
               k = (p->data.age) - (p->after->data.age);   //비교가 같다면 k=0, p가 크다면 0초과값, p가 작다면 0미만값
               if(k > 0){        //만약, p의 데이터의 멤버가 p->after의 멤버보다 클경우
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break;         

      case 4://성별순 정렬
         for(i=0; i<list->length-1; i++){ //'아래의 for문'을 list의 길이만큼 반복하게 하는 for문이다.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
				k = (p->data.gender) - (p->after->data.age);   //비교가 같다면 k=0, p가 크다면 0초과값, p가 작다면 0미만값
               if(k > 0){        //만약, p의 데이터의 멤버가 p->after의 멤버보다 클경우
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break; 

      case 5://평점순 정렬
         for(i=0; i<list->length-1; i++){ //'아래의 for문'을 list의 길이만큼 반복하게 하는 for문이다.
			 p = list->head;
            for(j=0; j<(list->length)-i-1; j++){
				k = (p->data.score) - (p->after->data.score);   //비교가 같다면 k=0, p가 크다면 0초과값, p가 작다면 0미만값
               if(k > 0){        //만약, p의 데이터의 멤버가 p->after의 멤버보다 클경우
				   temp = p->data;
				   p->data = p->after->data;
				   p->after->data = temp;
			   }
                  p = p->after;
            }
         }         
         break; 

      default:
         printf("올바른 명령값을 입력하지 않았습니다.\n");
   }
   data_print(list);
}

//학생정보 수정
void modify_student(LinkedListType *list){
	Student *p;
	int num;
	int modify_select;
	int new_stu_num, new_age;
	float new_score;
	char new_name[10];
	char new_gender;

	printf("수정할 학생의 학번을 입력하세요 : ");
	scanf("%d",&num);
	p = list->head;
	while((p->data.stu_num) != num)
		p = p->after;
	
	printf("학번:%d  이름:%s  나이:%d  성별:%c  평점:%f\n",p->data.stu_num,p->data.name,p->data.age,p->data.gender,p->data.score);
	printf("1.학번  2.이름  3.나이\n수정할 데이터를 고르세요 : ");
	scanf("%d",&modify_select);
	
	switch(modify_select){
		case 1:
			printf("변경할 학번을 입력해주세요 : ");
			scanf("%d",&new_stu_num);
			p->data.stu_num = new_stu_num;
			printf("학번 변경이 완료 되었습니다.");
			break;
		case 2:
			printf("변경할 이름을 입력해주세요 : ");
			scanf("%s",&new_name);
			strcpy(p->data.name,new_name);
			printf("이름 변경이 완료 되었습니다.");
			break;
		case 3:
			printf("변경할 나이를 입력해주세요 : ");
			scanf("%d",&new_age);
			p->data.age = new_age;
			printf("나이 변경이 완료 되었습니다.");
			break;
		case 4:
			printf("변경할 성별을 입력해주세요 : ");
			scanf("%c",&new_gender);
			p->data.gender = new_gender;
			printf("성별 변경이 완료 되었습니다.");
			break;
		case 5:
			printf("변경할 평점을 입력해주세요 : ");
			scanf("%f",&new_score);
			p->data.score = new_score;
			printf("평점 변경이 완료 되었습니다.");
			break;
		default:
			printf("잘못된 값을 입력하셨습니다.");
	}

}

//학생 검색
void search_student (LinkedListType *list, LinkedStackType *stack){
	int num;
	Student *p = list->head;

	printf("학번을 입력하세요 : ");
	scanf("%d", &num);

	while( p != NULL ){
		if ( (p->data.stu_num) == num )
			break;
		p = p ->after;
	}

	if( p == NULL)
		printf("학생정보가 없습니다.\n");
	else{
		printf("학번:%d  이름:%s  나이:%d  성별:%c  평점:%f\n", p->data.stu_num, p->data.name, p->data.age, p->data.gender, p->data.score);
		push(stack, p->data);
	}
}

//가장 최근 검색한 학생 정보
void last_student (LinkedStackType *stack){
	pop(stack);
}

//학생 정보 삭제
void del_student(LinkedListType *list){
   Student *p;
   int num;
   int pos;
   printf("삭제할 학생의 학번을 입력하세요 : ");
   scanf("%d",&num);
   p = list->head;
   while(p->data.stu_num != num)
      p = p->after;
   pos = search_pos(list, p);
   delete_pos(list, pos);

   printf("삭제가 완료되었습니다.\n");
}
#include "stdafx.h" //подключение библиотек
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h> 
#include <malloc.h> 
#include <clocale> 
 
using namespace std; 
using namespace System; 
using namespace System::IO; 
 
#define ENTER 13 //обозначение кнопок
#define ESC 27 
#define UP 72 
#define DOWN 80 
#define HOME 71
#define END 79
 
char dan[9][55]=
{ 
 "Какой издатель имеет наименьшее количество продаж?    ",
 "Игра какого издателя вышла раньше?                    ",
 "Количество популярных игр, дороже 2000 р.             ",
 "Список издателей по алфавиту.                         ",
 "Список издателей против алфавита.                     ",
 "Диаграмма,процентное соотношение проданных копий игр. ",
 "Список игр с вводом минимальной цены и кол-вом продаж.",
 "Есть ли у разных издателей одинаковове кол-во продаж? ", 
 "Выход                                                 " 
}; //задание списка вопросов - пунктов меню
char BlankLine[ ]= "                                                        "; 
 
 
 
int menu(int n) 
{ 
 int y1=0,y2=n-1; 
 char c=1; 
 while (c!=ESC) //при нажатии кнопки ESC, меню закроется
 { 
 switch(c) { 
  case DOWN: y2=y1; y1++; break; /*программирование кнопки DOWN,
								которая позволяет перемещаться вниз по меню*/
  case UP: y2=y1; y1--; break; /*программирование кнопки UP,
								которая позволяет перещаться вверх по меню*/
  case END: y2=y1; y1=n-1; break; /*программирование кнопки END,
								которая позволяет перемещаться самый низ меню*/
  case HOME: y2=y1; y1=0; break; /*программирование кнопки HOME,
								которая позволяет перемещаться самый верх меню*/
  case ENTER: return y1+1; /*программирование кнопки ENTER,
							 которая позволяет выбрать вопрос*/
 
 } 
 if(y1>n-1){y2=n-1;y1=0;}  //условие,когда срабатывает кнопка Down
 if(y1<0)  {y2=0;y1=n-1;}  //условие,когда срабатывает кнопка UP
 Console::ForegroundColor=ConsoleColor::White; /*привыборе вопроса,
												буквы окрашиваются в белый цвет*/
 Console::BackgroundColor=ConsoleColor::Black; /*привыборе вопроса,
												план за буквами становится черным*/
 Console::CursorLeft=11; 
 Console::CursorTop=y1+5; 
 printf("%s",dan[y1]); 
 Console::ForegroundColor=ConsoleColor::Yellow; 
 Console::BackgroundColor=ConsoleColor::Cyan; 
 Console::CursorLeft=11; 
 Console::CursorTop=y2+5; 
 printf("%s",dan[y2]);
  Console::BackgroundColor=ConsoleColor::Black;
 c=getch(); 
 } // конец while(c!=ESC)... 
 exit(0); 
} 
 struct z { 
 char devel[20]; //название разработчика
 char name[20]; //название игры
 long prod;    // количество продаж
 long price;  // цена игры
 char data[11]; //дата выхода
}; 

 struct sp { 
 char razr[20]; 
 char name[20]; 
 long prod;  
 struct sp* pred; 
 struct sp* sled; 
 } ;
 void vstavka(struct z* dev,struct sp **spisok,char* name,int NC)//Вставка в список
{
int i;
struct sp *nov,*nt,*z=0;
for(nt=*spisok; nt!=0 && strcmp(nt->name,name)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->name,name)==0) return;
nov=(struct sp *) malloc(sizeof(struct sp));
strcpy(nov->name,name);
nov->pred = z;
nov->sled=nt;
nov->prod=0;
for(i=0;i<NC;i++)
if(strcmp(dev[i].name,name)==0)
{nov->prod+=dev[i].prod;strcpy(nov->razr,dev[i].devel);}
if(!z) *spisok=nov;
if(z) z->sled=nov;
if(nt) nt->pred=nov;
return;
}
 void alfalist(struct z* dev,struct sp **spisok,int NC, int a) //Список издателей по и против алфавита.
{
int i;
struct sp* nt,*z;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkCyan;
Console::Clear();
if(!*spisok)
 for(i=0;i<NC;i++)
 vstavka(dev,spisok,dev[i].name, NC);

Console::Clear();
printf("\n Алфавитный список игр");
printf("\n =============================================\n");
if (a==1){//список по алфавиту
for(nt=*spisok; nt!=0; nt=nt->sled)
printf("\n %-20s %20s %ld млн. копий ",nt->name,nt->razr,nt->prod);
}
if (a==2){//список против алфавита
for(nt=*spisok,z=0; nt!=0; z=nt,nt=nt->sled);
for(nt=z; nt!=0; nt=nt->pred)
printf("\n %-20s %20s %ld млн. копий",nt->name,nt->razr,nt->prod);
}
getch();
}
 void diagram(struct z * dev,struct sp**spisok,int NC) //диаграмма по продажам(функция создания диграммы)
{
	struct sp *nt;
	int len,i,NColor;
	long sum = 0;
	char str1[25];
	char str2[20];
	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();
	for(i=0;i<NC;i++) sum = sum+dev[i].prod ;
	if(!spisok)
	for(i=0;i<NC;i++)
	vstavka(dev,spisok,dev[i].devel,NC);
	Color=ConsoleColor::Black; NColor=0;
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		sprintf(str1,"%s",nt->razr);
		sprintf(str2,"%3.1f%%",(nt->prod*100./sum));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::White;
		Console::CursorLeft=3; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=23;
		printf("%s",str2);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for(len=0; len<nt->prod*100/sum; len++) printf(" ");
		if(NColor==14)
		{ Color=ConsoleColor::Black; NColor=0; }
	}
getch();
return ;
}
 void prodprice(struct z* dev,int NC)//"Список игр по задаваемым параметрам.(Ввод цены и продаж с клавиатуры)
{
int i;
int inprice;
int inprod;
struct z* nt;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkCyan;
Console::Clear();
printf("\n\r Введите минимальную цену(р.): ");
scanf("%d",&inprice);
printf("\n\r Введите минимальные продажи(млн.): ");
scanf("%d",&inprod);
printf("\n\r============================================================\n\r");
printf("\n\r Список игр дороже %d рублей,продажи которых выше %d млн.",inprice,inprod);
printf("\n\r============================================================\n\r");
for(i=0,nt=dev;i<NC;nt++,i++)
if (nt->price>inprice && nt->prod > inprod)
printf("\n\r %-20s %d р. %d млн. продаж",nt->name,nt->price,nt->prod);
getch();
}
 void odinak(struct z* dev,int NC)//Есть ли у разных издателей одинаковове кол-во продаж?(сложный вопрос - поиск соответствия)
{
 int i,g,k;
 
 char razr[20];
 Console::ForegroundColor=ConsoleColor::Yellow;
 Console::BackgroundColor=ConsoleColor::DarkCyan;
 Console::Clear();
 k=0;
 for(i=0;i<NC;i++)
 {
  for(g=i+1;g<NC;g++)
  {
  if(strcmp(dev[i].devel,dev[g].devel)!=0 && dev[i].prod ==dev[g].prod)
   {
    k=1;
    break;
   }
  }
  if(k)
  {
   printf("Совпадающие по продажам %d игры,издателей %s и %s",dev[g].prod,dev[i].devel,dev[g].devel);
   break;
  }


 }
 if(!k)
 {
   printf("Нет совпадений продаж");

 }
 getch();
}
  void maxim(struct z* dev,int NC)/*Какой издатель имеет наименьшее количество продаж?
						(функция поиска минимума)  */
{
int i=0; struct z best;
strcpy(best.devel,dev[0].devel);/*в переменную структуры
									записываем нулевой элемент*/
best.prod=dev[0].prod;
for(i=1;i<NC;i++)
if (dev[i].prod<best.prod)//условие поиска минимального количества продаж
{
strcpy(best.devel,dev[i].devel);
best.prod=dev[i].prod;
}
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;//задаем область, где будет выведено минимальное количество
Console::CursorTop=15;
printf("Наименьшая продажа %ld млн. копий",best.prod);// Вывод минимального количества
Console::CursorLeft=10;//задаѐм область,где будет выведено имя издателя
Console::CursorTop=16;
printf("Имеет издатель %s",best.devel);// Вывод издателя
getch();
}
void text_data(char *s,char *sd,int NC)//функция преобразования месяца 
{
char s0[3],month[12][9]={ //Инициализация массива month,содержащего 12 элементов длиной до 9 символов
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);//отделение дня от строки
strcat(s," ");//копия номера месяца(с5 символа)
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);//преобразование строки s0 в число для индексации массива month
strcat(s," ");
strncat(s,sd,4);//запись года в конец строки
return;
}
void first(struct z* dev,int NC)/*Игра какого издателя вышла раньше? (функция поиска минимальной даты)*/
{
int i;
char s[17];
struct z* best=dev;
for(i=1;i<NC;i++)
if (strcmp(dev[i].data,best->data)<0)//сравнение дат 
best=&dev[i];//запись даты в best
text_data(s,best->data,NC);
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Самая ранняя игра %s ценой %ld р.",
best->name,best->price);// Вывод  игры и ее цены
Console::CursorLeft=10;//задаѐм область,где будет выведено название и цена
Console::CursorTop=16;
printf("Изданная %s",best->devel);// Вывод издателя
Console::CursorLeft=10;//задаѐм область,где будет выведено имя издателя
Console::CursorTop=17;
printf("Вышла %s ",s); // Вывод ранней даты
getch();
}
void kolvo(struct z *dev,int NC) //Количество популярных игр, дороже 2000 р.(функция подсчета количества определенных игр)
{
int i,k=0;
for(i=0;i<NC;i++)
if (dev[i].price>2000 )//условие отбора по цене
k++;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10; //задаѐм область,где будет выведено количество игр по условию
Console::CursorTop=15;
printf("Всего игр дороже 2000 : %d",k);// Вывод количества игр подходящих по условию 
getch();
}
int main(array<System::String ^> ^args) /*на локальном уровне осуществляем открытие файла,
											считываем данные из файла в выделенную память*/
{ 
 int NC; //количество позиций 

 
 struct sp *spisok=NULL;
 int i,n; 
 FILE *in; 
 struct z *dev; 
 setlocale(LC_CTYPE,"Russian");//поддержка русского языка 
 Console::CursorVisible::set(false); //отключаем выдимость курсора
 Console::BufferHeight=Console::WindowHeight; //установка размера буфера по ширине
 Console::BufferWidth=Console::WindowWidth; //установка размера буфера по высоте
 if((in=fopen("издатели.txt","r"))==NULL) //попытка открыть файл
 { 
  printf("\nФайл издатели не открыт !"); //при неудачном открытии выводим сообщение 
  getch(); 
  exit(1); 
 } 
 fscanf(in,"%d",&NC); 
 dev=(struct z*)malloc(NC*sizeof(struct z)); //выделяем память
 for(i=0;i<NC;i++) //считываем данные из списка
  fscanf(in,"%s%s%ld%ld%s",dev[i].devel, 
   dev[i].name, &dev[i].prod, &dev[i].price,
   dev[i].data); 
 for(i=0;i<NC;i++) //выводим данные из списка на экран
  printf("\n%-20s %-20s %10ld %6ld %-10s", 
   dev[i].devel, 
   dev[i].name, dev[i].prod, dev[i].price,
   dev[i].data); 
 getch(); 
 while(1) //в цикле создаем область для вопросов и окрашиваем еѐ
 { 
	
  Console::BackgroundColor=ConsoleColor::Black; 
  Console::Clear(); 
  Console::ForegroundColor=ConsoleColor::Yellow; 
  Console::BackgroundColor=ConsoleColor::Cyan; 
  Console::CursorLeft=10; //первая точка, откуда будем закрашивать область меню 
  Console::CursorTop=4; 
  printf(BlankLine); 
  for(i=0;i<8;i++) //размещение вопросов
  { 
   Console::CursorLeft=10; 
   Console::CursorTop=i+5; 
   printf(" %s ",dan[i]); 
  } 
  Console::CursorLeft=10; //последняя точка,где будет заканчиваться выделенная область под меню
  Console::CursorTop=13;
  printf(BlankLine); 
  n=menu(8); //выбор вопроса в меню
  switch(n) { 
   case 1: maxim(dev,NC);break; 
   case 2: first(dev,NC);break; 
   case 3: kolvo(dev,NC);break; 
   case 4: alfalist(dev,&spisok,NC,1);break;
   case 5: alfalist(dev,&spisok,NC,2);break;
   case 6: diagram(dev,&spisok,NC);break; 
   case 7: prodprice(dev,NC);break;
   case 8: odinak(dev,NC);break;
   case 9: exit(0); 
  } 
 } // конец while(1)...
 return 0; 
}// конец main...






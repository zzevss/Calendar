#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <iostream>
//#include <locale>
#include <windows.h>
#include <locale.h>



struct eventS
{
	char dateEv[100];
	int input;
	char infInput[100];
	
		
};




//-------------Vvod goda i proverka vvoda---------------------------------
int inputYear()
{	
	int dateY = 0;
	
	printf("Введите значение года: \n");
	scanf("%d", &dateY);
	
	if (dateY < 1582)
	{
		system("cls");
		do
	    {
	    	printf("Значение года должно быть больше 1582! \n");
			printf("Введите повторно значение года: \n");
	    	scanf("%d",&dateY);
	    	system("cls");
	    } while (dateY <= 1582);
	}
    system("cls");
    return (dateY);
}
//-------------Vvod mes i proverka vvoda---------------------------------
int inputMonth()
{
	int dateM;
	printf("Введите значение месяца: \n");
    scanf("%d", &dateM);
    
    if (dateM < 1 || dateM > 13)
	{
		system("cls");
		do
	    {
	    	printf("Значение месяца должно быть быть в диапазоне от 1 до 12 !\n");
			printf("Введите повторно значение месяца: \n");
	    	scanf("%d",&dateM);
	    	system("cls");
	    } while (dateM < 1 || dateM > 12);
	}
    system("cls");
    return (dateM);
}

//-------------funkcija obscheta nachala mesjaca v nedele-----------------
int dayWeek(int dateM, int dateY)
{
    int a;
    int y;
    int m;
    a = (14 - dateM) / 12;
    y = dateY - a;
    m = dateM + 12 * a - 2;
    return ((7000 + (1 + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7);
}

//-------------funkcija obscheta nomera nedeli----------------------------
int nomDay(int dateM, int dateY)
{
    
    int n = 1;
    int i;
    
    int moon[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((dateY % 4 == 0) || (dateY % 400 == 0) && (dateY % 100 != 0) )
    {
        moon[1] = moon[1] + 1;
    }
    for (i = 0; i < dateM - 1; i++)
    {
        n = n + moon[i];
    }
       
    return (n); 
}






int main()
{
//-----------------Activacija Rus Kodirovki--------------------
    setlocale(LC_ALL, "Russian");
	    
    eventS one;
	
a:
	printf("Для ввода события вдите 1\nДля просмотра календаря с событиями введите 2\nДля выхода введите 3\n");
	scanf("%d", &one.input);
	
	int dateM;
    int dateY;
    int numDay;
    int moon[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int numWeek;
    int j,c,t,i;
    int key = 0;
    int key2 = 1;
    char *Month []={"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
    char taskString[100];
	
	switch ( one.input ) 
	{
//---------------------recording in file-------------------------------------
			case 1:
	  		{
				
				FILE* baseEv;	
				
				while (key2 != 0 )
				{
					system("cls");
					
					if ((baseEv = fopen("baseEv.txt","a")) == NULL)
					{
						printf("Невозможно окрыть файл!\n");
					} 
				    		
				 	else
				 	{   		
				       			
						printf ("Введите значение события ДД.ММ.ГГГГ ЧЧ:ММ .....:\n");
						gets(one.dateEv); 
						fprintf(baseEv,"%s\n", one.dateEv);
					 		
				    		
					}
					
					printf ("Для продолжения введите: 1\nДля завершения введите: 0\n");
					scanf("%d",&key2);
				}
				
				fclose(baseEv);	
				}
				
				system("cls");
				
				goto a;
				
				break;
	  		
	  		
			case 2:
//----------------Funkcii vvoda goda i mesjaca + proverka------
			    dateY = inputYear();
			    
			    dateM = inputMonth();
//----------------Funkcii obscheta nachala dnja mes -----------    
			    numDay = dayWeek(dateM, dateY);
			    
			    if (numDay == 0)
			    {
			        numDay =6;
			    }
//----------------Funkcii obscheta nomera nedeli -----------     
			    numWeek = (nomDay(dateM, dateY))/7 ;
			    
			    numWeek +=1;
			    
			    t = numDay;
			    
			    //printf("Начало месяца  = %d \n", numDay);
			    //printf("Номер Недели  = %d \n", numWeek);
			
//-------------uslovie proverky vusokosnogo goda------------
			    if ((dateY%4 == 0) || (dateY%400 == 0) && (dateY%100 != 0) )
			    {
			        moon[1]= moon[1] +1;
			    }
			
			    dateM = dateM -1;
			    
//-----------Vuvod mesjaca i goda---------------------------
			    printf("\n");
			    printf("%s", Month[dateM]);
			    printf("             Год: %d\n", dateY);
			    
//--------------cykl na vuvod dnei i nedel------------------   
			
			    printf("____________________________\n");
			    printf("НН\tПн Вт Ср Чт Пт Сб Вс\n");
			    printf("____________________________\n");
			
			    c = t - 1;
			
			    for(j = 1; j <= moon[dateM]; j++)
			    {
//--------------vivod pustuh mest --------------------------    	
			    	if (key == 0)
			    	{
				    	printf("%d", numWeek);
						if (dateM < 3)
						{
							printf("    ");
						} else {
							printf("   ");
						}
						printf("%*c",t*3,' ');
				    }
				    key = 1;
				    
//----------------------------------------------------------        
					c++;
			        t = c % 7;
			        
			        printf("%2d ",j);
			        
			        if(t == 0) 
					{
						printf("\n");
						numWeek++;
						printf("%d", numWeek);
						printf("\t");
						
					}
			    }
			
			    printf("\n\n");

				break;
	  		
  			case 3:
				return 0;
				break;
			
			default:
				printf ("Введенный символ не соответствует выбору!\n");
				break;
	}
	
	system("pause");

    return 0;
}



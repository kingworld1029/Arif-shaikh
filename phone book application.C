#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
#define MAXDB 500



//List of gloal variables
long int phone[MAXDB+1];
int i;
int room[MAXDB+1];
long int phone_tmp[MAXDB+1];
int room_tmp[MAXDB+1];
void AddEntry(int,long int);
int add_count=0;
int current_e_add;
int DeleteEntry(int,long int);
int FindPhone(long int);
int FindRoom(int);
int phone_found , room_found;
int del_entry;
int tot_del_entry=0;
int ListAll(void);
int SortallEntries(char);
int GeTotalEntries(void);
int chkstrdig(char str[],int range);
char menu(void);
void LoadDB(void);
void exitmenu(void);
void drawscreen(void);
void refreshscreen(void);

char dbload[80];


void main(void)
{
char iroom[80],iphone[80],add_quit;
char option,sortopt,exit_opt;
int phone_check,room_check,delete_check,sort_check,list_check;
int iroom_search,iroom_del;
int int_room,total_entries;
int error_iphone,error_iroom;
long int longint_iphone;
long int iphone_search;
long int iphone_del;

strcpy(dbload,"No datbase file laded (RAM mode !)") ;

do
 {
  do
   {option = menu();
    if (option == '1')
    { current_e_add = 0;
  for (i = add_count; i<MAXDB ; i++)
  {	clrscr();
	refreshscreen();
	drawscreen();
	gotoxy(1,4);
	printf("	     >> Add Entry <<     ");
	gotoxy(1,25);
	cprintf("Please add your entry , leave blank to quit to menu");
	gotoxy(1,6);

	printf("Enter the room number [%3d]",i+1);
	gets(iroom);

	if (iroom[0] == '\0')
	{ gotoxy(1,25);
	  cprintf("You choose to quit, Entry %d was not added to database",i+1);
	  getch();
	  break;

	}

	printf("Enter the phone number [%3d]",i+1);
	gets(iphone);

	if (iphone[0] == '\0')
	{ gotoxy(1,25);
	  cprintf("You choose to quit, Entry %d was not added to database",i+1);
	  getch();
	  break;

	}

	error_iroom = chkstrdig(iroom,4);
	error_iphone = chkstrdig(iphone,8);
	while(error_iroom!=0)
	{if (error_iroom == -1)
	 {  clrscr();
	    refreshscreen();
	    drawscreen();
	    gotoxy(1,4);
	    printf("     	>> Add Entry <<");
	    gotoxy(1,25);
	    cprintf("Error : room number- out of range ,your entry was greater than 4 digit");
	    gotoxy(1,6);
	    printf("Enter room number [%3d]",i+1);
	    gets(iroom);
	 }
	 if (error_iroom == -2)
	 {  clrscr();
	    refreshscreen();
	    drawscreen();
	    gotoxy(1,4);
	    printf("	     >> Add Entry <<<");
	    gotoxy(1,25);
	    cprintf("Error : room number- Charactrer(s) detected, character(s are not allowed");
	    gotoxy(1,6);
	    printf("Enter room number [%3d]",i+1);
	    gets(iroom);
	 }

	 error_iroom = chkstrdig(iroom,4);

	}
	while(error_iphone!=0)
	{if (error_iphone == -1)
	 {  clrscr();
	    refreshscreen();
	    drawscreen();
	    gotoxy(1,4);
	    printf("	     >> Add Entry <<");
	    gotoxy(1,25);
	    cprintf("Error : phone number- out of range ,your entry was greater than 8 digit");
	    gotoxy(1,6);
	    printf("room number[%3d] entry: %s",i+1,iroom);
	    gotoxy(1,7);
	    printf("Renter Phone number [%3d]",i+1);
	    gets(iphone);
	 }
	 if (error_iphone == -2)
	 {  clrscr();
	    refreshscreen();
	    drawscreen();
	    gotoxy(1,4);
	    printf("	     >> Add Entry <<");
	    gotoxy(1,25);
	    cprintf("Error : Phone number- Charactrer(s) detected, character(s are not allowed");
	    gotoxy(1,6);
	    printf("room number[%3d] entry: %s",i+1,iroom);
	    gotoxy(1,7);
	    printf("Renter room number [%3d]",i+1);
	    gets(iroom);
	 }
	 error_iphone = chkstrdig(iphone,8);
       }
       if (error_iroom == 0 && error_iphone == 0)
       {    int_room = atoi(iroom); //converts string to int
	    longint_iphone = atol(iphone); // converts string to long int
	    current_e_add++;
	    AddEntry(int_room,longint_iphone);
       }

   }
   if (add_count == MAXDB)
   { gotoxy(1,25);
     cprintf("\a Database is full : %d entries were added ",add_count);
     cprintf("that is the Maximum no that I can hold");
     getch();
   }
  }
	else
	if(option == '2')
	{ del_entry = 0;
	  clrscr();
	  refreshscreen();
	  drawscreen();
	  gotoxy(1,4);
	  printf("	     >> Delete Entry <<");
	  gotoxy(1,6);
	  printf("Enter the room no to delete");
	  scanf("%d",&iroom_del);
	  flushall();
	  printf("Enter the phone no to delete");
	  scanf("%ld",&iphone_del);
	  flushall();
	  delete_check = DeleteEntry(iroom_del,iphone_del);

	if (delete_check == 0)
	{gotoxy(1,25);
	 cprintf("Successful: ther are currently %d entries in the database ", add_count);
	 cprintf(" deleted %d.",del_entry);
	 getch();
	}
	if (delete_check == -1 )
	{gotoxy(1,25);
	 cprintf("Error: The room no or Phone no you are looking for is not found ");
	 getch();
	}
   }
   else
	if(option == '3')
	{ phone_found = 0;
	  clrscr();
	  refreshscreen();
	  drawscreen();
	  gotoxy(1,4);
	  printf("	     >> Find Room Number <<");
	  gotoxy(1,6);
	  printf("Enter the phone number to search for:");
	  scanf("%ld",&iphone_search);
	  flushall();

	  phone_check = FindPhone(iphone_search);

	if (phone_check == 0)
	{gotoxy(1,25);
	 cprintf("successful: ther are currently %d entries in the database ", add_count);
	 cprintf(" found %d.",phone_found);
	 getch();
	}
   }
   else
	if(option == '4')
	{ room_found = 0;
	  clrscr();
	  refreshscreen();
	  drawscreen();
	  gotoxy(1,4);
	  printf("	     >> Find Room Number <<");
	  gotoxy(1,6);
	  printf("Enter the room no to search for");
	  scanf("%d",&iroom_search);
	  flushall();

	  room_check = FindRoom(iroom_search);

	if (room_check == 0)
	{gotoxy(1,25);
	 cprintf("successful: ther are currently %d entries in the database ", add_count);
	 cprintf(" found %d.",room_found);
	 getch();
	}
	if (room_check == -1 )
	{gotoxy(1,25);
	 cprintf("Error: The room no  you are looking for is not found ");
	 getch();
	}
   }
   else
	if(option == '5')
	{
	  clrscr();
	  refreshscreen();
	  drawscreen();
	  gotoxy(1,4);
	  printf("	     >> List All <<\n\n");


	  list_check = ListAll();

	if (list_check == 0)
	{gotoxy(1,25);
	 cprintf("List Successful");
	 getch();
	}
	if (list_check == -1 )
	{gotoxy(1,25);
	 cprintf("Empty list ");
	 getch();
	}
   }
   else
   if(option == '6')
   {total_entries = GeTotalEntries();
   gotoxy(1,25);
   cprintf("There are currently %d entries stored in the database",total_entries);
   getch();
   }
   else
   if(option == '7')
   { clrscr();
     refreshscreen();
     drawscreen();
     gotoxy(1,4);
     printf("	     >> Sort All Entries <<");
     gotoxy(1,6);
     printf("Press A to sort database in [A]scending order");
     gotoxy(1,7);
     printf("Press D to sort database in [D]escending order");
     gotoxy(1,9);
     printf("Note: Database is sorted by phone no. entries");
     sortopt = getch();
     flushall();
     sort_check = SortAllEntries(sortopt);
     getch();
     if (sort_check == 0)
     {gotoxy(1,25);
      cprintf("Database was successfully sorted");
      getch();
     }
     if (sort_check == -1)
     {gotoxy(1,25);
      cprintf("Database was not sorted: database is empty");
      getch();
     }
   }
   else
   if(option == '8')
   { clrscr();
     refreshscreen();
     drawscreen();
     gotoxy(1,4);
     printf("	     >> Load Database <<");
     LoadDB();
   }
   else
   if(option == '9')
   {gotoxy(1,25);
    cprintf("Do you Really want to exit? press 'Y' to confirm , anykey to cancel");
    exit_opt = getch();
    flushall();
    if (exit_opt == 'Y'|| exit_opt == 'y')
    {clrscr();
     refreshscreen();
     drawscreen();
     gotoxy(1,4);
     printf("	     >> Exit to System <<");
     exitmenu();
    }
    }
    else
    {gotoxy(1,25);
     cprintf("Error: Invalid option ! Select option etween 1 to 9");
     getch();
     flushall();
     }
    }while (option > '9' || option < '1');
 } while (option !=  ' ');


}

void AddEntry(int r, long int p)
{
	room[i] = r;
	phone[i] = p;
	add_count++;
	printf("\nRoom no. [%-4d]\nPhone no. [%-8ld]\n %d Entries added",r,p,current_e_add);
	getch();
}

int DeleteEntry( int r,long int p)
{
  int k,x,del_found_flag=-1,loop_mov_stop,loop_mov,count_del=0;
  char del_me;
	for (k=0;k<add_count;k++)
	{if(add_count!=0)
	  {if (r==room[k] && p==phone[k])
	   {gotoxy(1,8);
	    printf("Match Found: \n");
	    printf("Room no . [%-4d]\tPhone no. [%-8ld] was found in record no.[%3d]\n",room[k],phone[k],k+1);
	    del_found_flag =0;
	    gotoxy(1,25);
	    cprintf("Deleted record [%3d]?. press 'Y' to conform, anykey to cancel. ",k+1);
	    del_me = getch();
	    flushall();
	    if(del_me == 'Y' || del_me == 'y')
	    {room_tmp[tot_del_entry] = room[k];
	     room[k]= -1;
	     phone_tmp[tot_del_entry] = phone[k];
	     phone[k]= -1;
	     del_entry++;
	     tot_del_entry++;
	     }
	   }
	  }
	}
	if(add_count!=0)
	{for(x=0;x<add_count;x++)
	   {for(k=0;k<add_count;k++)
	    { if(room[k] == -1 && phone[k] == -1)
	     {loop_mov_stop = 0;
	      loop_mov = 0;
	      count_del++;
	      loop_mov_stop = add_count-(k+1);
	      while(loop_mov_stop!= loop_mov)
	      {room[k+loop_mov] = room[(k+1)+loop_mov];
	       phone[k+loop_mov] = phone[(k+1)+loop_mov];
	       loop_mov++;
	      }
	     }
	   }
	}
     }

   add_count = add_count-del_entry;
   if( del_found_flag == 0)
   {return (0);}
   else
   {return (-1);}

 }


 int FindPhone(long int p)
 {
 int k,phone_found_flag = -1;
 gotoxy(1,8);
 for(k=0;k < add_count;k++)
   { if(add_count!=0)
      {if(k!=0 && (k%15) == 0 )
	{gotoxy(1,8);
	 getch();
	}
       if(p == phone[k])
       {printf("Phone no.[%-8ld] was found in record no.[%3d]\t Room no.[%-4d]",phone[k],k+1,room[k]);
       phone_found++;
       phone_found_flag = 0;

       }
      }
   }
   if(phone_found_flag == 0)
   {return (0);}
   else
   {return (-1);}

 }


int FindRoom( int r)
{
 int k,room_found_flag = -1;
 gotoxy(1,8);
 for(k=0;k<add_count;k++)
   { if(add_count!=0)
      {if(k!=0 && (k%15) == 0 )
	{gotoxy(1,8);
	 getch();
	}
       if(r == room[k])
       {printf("Room no.[%-4d] was found in record no.[%3d]\t Phone no.[%-8ld]",room[k],k+1,phone[k]);
       room_found++;
       room_found_flag = 0;

       }
      }
   }
   if(room_found_flag == 0)
   {return (0);}
   else
   {return (-1);}

 }

 int ListAll(void)
 {
 int k;
 gotoxy(1,6);
 for(k=0;k<add_count;k++)
      {if(k!=0 && (k%17) == 0 )
	{gotoxy(1,6);
	 getch();
	}
       if(room[k]!= -1 && phone[k]!= -1)
       {printf("Room no.[%3d]: %-4d\t",k+1,room[k]);
       printf("Phone no.[%3d]: %-8ld\t\n",k+1,phone[k]);
	}
      }

   if(add_count == 0)
   {return (-1);}
   else
   {return (0);}

 }

 int GeTotalEntries(void)
 {
  return (add_count);
 }


int SortAllEntries(char sel)
{
int k,room_str_tmp,sortalldone;
long int phone_str_tmp;
	if(add_count!=0)
	{do
	  {sortalldone=0;
	  for(k=0;k<add_count;k++)
	    {if((phone[k] > phone[k+1]) && (sel == 'a' || sel == 'A') && (k != add_count-1))
	      {phone_str_tmp = phone[k];
	       phone[k] = phone[k+1];
	       phone[k+1] = phone_str_tmp;
	       room_str_tmp = room[k];
	       room[k] = room[k+1];
	       room[k+1] = room_str_tmp;
	       sortalldone = 1;
	      }
	      {if((phone[k] > phone[k+1]) && (sel == 'd' || sel == 'D') && (k != add_count-1))
	      {phone_str_tmp = phone[k];
	       phone[k] = phone[k+1];
	       phone[k+1] = phone_str_tmp;
	       room_str_tmp = room[k];
	       room[k] = room[k+1];
	       room[k+1] = room_str_tmp;
	       sortalldone = 1;
	      }
	  }
	}
   }      while (sortalldone);
 }
 if((sel == 'a' || sel == 'A') && add_count!=0)
 {gotoxy(1,25);
  printf("you have choosen to sort databse in [A]scending order");
  return (0);
 }
 else
 if((sel == 'd' || sel == 'D') && add_count!=0)
 {gotoxy(1,25);
  printf("you have choosen to sort databse in [D]escending order");
  return (0);
  }
  else
  if((sel != 'a' || sel != 'A' || sel != 'd' || sel != 'D') &&  add_count !=0 )
 {gotoxy(1,12);
  printf("Invalid option ! - Database was ot sorted");
  return (0);
  }
  else
  {return (-1); }
}


int chkstrdig (char str[], int range)
{
int length=0,k;
	length = strlen(str);
	if(length > range)
	{return(-1);}
	if(length <= range)
	{  for(k=0;k<length;k++)
	   {if(isdigit(str[k])==0)
	     {return(-2);}
	   }
	   return(0);
	}
	return(0);
}


void LoadDB(void)
{
int count,nofilen,dbfilecount=0;
char finphone[80];
char finroom[80];
int error_junk;
long int l_finphone;
int i_finroom;

FILE *f1;
	gotoxy(1,6);
	printf("Enter the filename of the database");
	gotoxy(1,7 );
	printf("Example:  c:\\\mydbfile.txt");
	gotoxy(37,6);
	gets(dbload);
	flushall();
	f1=fopen(dbload,"r");
	if (f1 == NULL)
	{gotoxy(1,25);
	 fprintf(stderr,"There was an error in reading your database file!");
	 strcpy(dbload,"NO database file loaded (RAM mode!)");
	 getch();

	}
	else
	{ for(count =0 ;count< MAXDB; count++)
	   { if (!feof(f1))
	     {fscanf(f1,"%s\t%s\n",&finroom,&finphone);
	      error_junk = chkstrdig(finroom,4);
	      error_junk = chkstrdig(finphone,8);
	      if (error_junk == -1 || error_junk == -2)
		{ printf("soory! Inavalid database\n");
		printf("Working in RAM mode");
		getch();
		strcpy(dbload,"No database file loaded (RAM mode!)");
		break;
		}
	      i_finroom = atoi(finroom);
	      l_finphone = atol(finphone);
	      room[count] = i_finroom;
	      phone[count] = l_finphone;
	      dbfilecount++;
	     }
	   }
	   if(error_junk == 0)
	   {gotoxy(1,25);
	   printf("Database %s , was successfully loaded!",dbload );
	   getch();
	   add_count = dbfilecount;
	   }
	}
	fclose(f1);
}


char menu(void)
{
char optrtn;
clrscr();
window(1,1,80,25);
refreshscreen();
drawscreen();
gotoxy(1,4);
printf("[1] - Add entry\n");
printf("[2] - Delete entry\n");
printf("[3] - Find room numner\n");
printf("[4] - Find phone number\n");
printf("[5] - List All entries\n");
printf("[6] - Display total entries in the database\n");
printf("[7] - Sort entries\n");
printf("[8] - Load Database from file\n");
printf("[9] - EXIT\n");
gotoxy(1,25);
cprintf("Please select an option between 1 and 9");
gotoxy(1,15);
printf("Database loaded: %s",dbload);
gotoxy(1,14);
printf("select an option:");
optrtn = getch();
return  optrtn;
}


void exitmenu(void)
{
	char filename[20],save_opt;
	int k;
	FILE *f1;
	printf("\nDo You want to Save database before existing?");
	gotoxy(1,25);
	cprintf("press 'Y' to confirm, anykey to cancel");
	save_opt = getch();
	flushall();
	if (save_opt == 'y' || save_opt == 'Y')
	{ gotoxy(1,8);
	  printf("Please enter the filename and path to save :");
	  gotoxy(1,10);
	  printf("Example: c:\\\mydbfile.txt");
	  gotoxy(48,8);
	  gets(filename);
	  flushall();
	  f1 = fopen(filename,"a");
	  if (f1 == NULL)
	  { gotoxy(1,12);
	    fprintf(stderr,"Error while opening file %s",filename);
	    gotoxy(1,25);
	    cprintf("Database was not saved");
	    getch();

	  }
	  else
	  { for(k=0;k<add_count;k++)
	   { fprintf(f1,"%d\t%ld\n",room[k],phone[k]);}
	   fclose(f1);
	   gotoxy(1,25);
	   cprintf("Database was successfully saved in %s",filename);
	   getch();
	  }
	}
	else
	{ gotoxy(1,25);
	  cprintf("Database was not saved");
	  getch();
	}
	  clrscr();
	  gotoxy(23,10);
	  printf("THANKYOU FOR USING THIS PROGRAM");
	  gotoxy(23,11);
	  printf("CODED BY: ARIF SHAIKH ");
	  gotoxy(23,13);
	  printf("EMAIL : arifshaikh1029@gmail.com");
	  getch();
	  exit(0);

}

void drawscreen(void)
{
gotoxy(1,1);
cprintf("------------------------------------------------------------------------------");
gotoxy(1,2);
cprintf("                     *****  PHONE BOOK  *****                         BY ARIF.");

gotoxy(1,3);
cprintf("------------------------------------------------------------------------------");


}

void refreshscreen(void)
{
clrscr();
textcolor(WHITE);
textbackground(BLACK);
gotoxy(1,25);
cprintf("                                                                                                                                                                                                         ");
clrscr();
textcolor(WHITE);
textbackground(BLUE);
gotoxy(1,25);
cprintf("                                                                                                                                                                                             ");



}
















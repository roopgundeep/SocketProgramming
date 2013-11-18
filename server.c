/* tcpserver.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
char parsed_t[1000][100];
char parsed_s[1000][100];
typedef struct information
{
	char permission[100];
	char size[50];
	char month[50];
	char date[50];
	char time[50];
	char name[100];

}info;

info data[100];

typedef struct checking
{
	char name[100];
	char msg[100];
}checked;
checked msd[200];

typedef struct shortlist
{
	char name[100];
	char size[100];
	char date[100];
	char time[100];
}shortl;
shortl sh[200];


void parse_short(int kl,char *line)
{
	int i=0;
	char str[100];
	int t=0,k=0;
	int count=0;
	int length=strlen(line);
	//      printf("%d\n",length);
	for(i=0;i<length;i++)
	{   
		if(line[i]==' ')
		{   
			if(line[i+1]==' ')
				continue;
			str[k]=0;

			if(t==0)
			{   
				strcpy(sh[kl].size,str);
			}   
			else if(t==1)
			{   
				strcpy(sh[kl].date,str);
			}
			else if(t==2)
			{   
				strcpy(sh[kl].time,str);
			}   
			else if(t==3)
			{   
				strcpy(sh[kl].name,str);
			}   
			
			
			t++;
			k=0;
		}   
		else
		{   
			str[k]=line[i];
			k++;
		}   
	}   
	str[k]=0;
	strcpy(sh[kl].name,str);
}



void parse_check(int kl,char *line)
{
	int i=0;
	char str[100];
	int t=0,k=0;
	int count=0;
	int length=strlen(line);
	//      printf("%d\n",length);
	for(i=0;i<length;i++)
	{   
		if(line[i]==' ')
		{   
			if(line[i+1]==' ')
				continue;
			str[k]=0;

			if(t==0)
			{   
				strcpy(msd[kl].msg,str);
			}   
			else if(t==1)
			{   
				strcpy(msd[kl].name,str);
			}   
			t++;
			k=0;
		}   
		else
		{   
			str[k]=line[i];
			k++;
		}   
	}   
	str[k]=0;
	strcpy(msd[kl].name,str);
}




void parse_info(int kl,char *line)
{
	int i=0;
	char str[100];
	int t=0,k=0;
	int count=0;
	int length=strlen(line);
//	printf("%d\n",length);
	for(i=0;i<length;i++)
	{
		if(line[i]==' ')
		{
			if(line[i+1]==' ')
				continue;
			str[k]=0;
			
			if(t==0)
			{
				strcpy(data[kl].permission,str);
			}
			else if(t==4)
			{
				strcpy(data[kl].size,str);
			}
			else if(t==5)
			{
				strcpy(data[kl].month,str);
			}
			else if(t==6)
			{
				strcpy(data[kl].date,str);
			}
			else if(t==7)
			{
				strcpy(data[kl].time,str);
			}
			t++;
			k=0;
		}
		else
		{
			str[k]=line[i];
			k++;
		}
	}
	str[k]=0;
//	printf("%s ",str);
//	printf("\n");
	strcpy(data[kl].name,str);
//	printf("%s",data.name);
}


void parse(char *line)
{
	int i=0;
	char str[100];
	int t=0,k=0;
	int length=strlen(line);
	for(i=0;i<length;i++)
	{
		if(line[i]==' ')
		{
			str[k]=0;
			strcpy(parsed_t[t],str);
			k=0;t++;
		}
		else
		{
			str[k]=line[i];
			k++;
		}
	}
	str[k]=0;
	strcpy(parsed_t[t],str);

}

void parse2(char *line)
{
	int i=0;
	char str[100];
	int t=0,k=0;
	int length=strlen(line);
	for(i=0;i<length;i++)
	{
		if(line[i]==' ')
		{
			str[k]=0;
			strcpy(parsed_s[t],str);
			k=0;t++;
		}
		else
		{
			str[k]=line[i];
			k++;
		}
	}
	str[k]=0;
	strcpy(parsed_s[t],str);

}


int main(int argc,char **argv)
{

	int sock1, connected1, bytes_recieved1 , true = 1;  
	char send_data [1024] , recv_data[1024];       
	int sock2, connected2, bytes_recieved2;  
	struct sockaddr_in server_addr1,client_addr1;    
	struct sockaddr_in server_addr2,client_addr2;    
	int sin_size;int Port1,Port2;
	
	int sock3,sock4;
	int addr_len3, bytes_read3,addr_len4,bytes_read4;
	struct sockaddr_in server_addr3 , client_addr3;
	struct sockaddr_in server_addr4 , client_addr4;

	if ((sock3 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	if ((sock4 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}

	server_addr3.sin_family = AF_INET;
	server_addr3.sin_port = htons(4002);
	server_addr3.sin_addr.s_addr = INADDR_ANY;
	//	bzero(&(server_addr.sin_zero),8);a


	if (bind(sock3,(struct sockaddr *)&server_addr3,
				sizeof(struct sockaddr)) == -1)
	{
		perror("Bind");
		exit(1);
	}

	addr_len3 = sizeof(struct sockaddr);
	server_addr4.sin_family = AF_INET;
	server_addr4.sin_port = htons(3002);
	server_addr4.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock4,(struct sockaddr *)&server_addr4,
				sizeof(struct sockaddr)) == -1)
	{
		perror("Bind");
		exit(1);
	}

	
	addr_len4 = sizeof(struct sockaddr);

	
	if ((sock1 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
//	printf("Enter The Ports : 1 and 2\n");
	Port1=atoi(argv[1]);
	Port2=atoi(argv[2]);
//	scanf("%d %d",&Port1,&Port2);
	///socket1
	server_addr1.sin_family = AF_INET;         
	server_addr1.sin_port = htons(Port1);     
	server_addr1.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server_addr1.sin_zero),8); 

	if (bind(sock1, (struct sockaddr *)&server_addr1, sizeof(struct sockaddr))
			== -1) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(sock1, 5) == -1) {
		perror("Listen");
		exit(1);
	}
///socket 2
	server_addr2.sin_family = AF_INET;         
	server_addr2.sin_port = htons(Port2);     
	server_addr2.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server_addr2.sin_zero),8); 

	if (bind(sock2, (struct sockaddr *)&server_addr2, sizeof(struct sockaddr))
			== -1) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(sock2, 5) == -1) {
		perror("Listen");
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);
	connected1 = accept(sock1, (struct sockaddr *)&client_addr1,&sin_size);
	printf("\n I got a connection from (%s , %d)",inet_ntoa(client_addr1.sin_addr),ntohs(client_addr1.sin_port));

	connected2 = accept(sock2, (struct sockaddr *)&client_addr2,&sin_size);
	printf("\n I got a connection from (%s , %d)\n",inet_ntoa(client_addr2.sin_addr),ntohs(client_addr2.sin_port));

	//	printf("\nTCPServer Waiting for client on port 5000\n");
	fflush(stdout);


	pid_t pid=fork();

	if(pid==0)//i am getting data from terminal.......connected 1 will be used(socket 1)
	{
		//server to get udp address/
		bytes_read3 = recvfrom(sock3,recv_data,1024,0,
				(struct sockaddr *)&client_addr3, &addr_len3);
		printf("\nUDP through socket 3 established\n");
		while(1)
		{
			//		strcpy(send_data,"");
			printf("Enter the Command: ");
			gets(send_data);
			parse(send_data);
		//	printf("parse==%s\n",parsed_t[0]);
			if (strcmp(send_data , "q") == 0 || strcmp(send_data , "Q") == 0)
			{
				send(connected1, send_data,strlen(send_data), 0); 
				close(connected1);
				break;
			}
			//////
			else if(strcmp(parsed_t[0],"FileHash")==0)
			{
				send(connected1,send_data,strlen(send_data), 0);
				FILE *lk;
				lk=fopen("server_folder/clienthash.txt","w");
				while(1)
				{
					bytes_recieved1=recv(connected1,recv_data,1024,0);
					int no_bytes;
					int i=0;
					int first,second,third,fourth;
					first=recv_data[1020]-48;
					second=recv_data[1021]-48;
					third=recv_data[1022]-48;
					fourth=recv_data[1023]-48;
					no_bytes=first*1000 + second*100 + third*10 + fourth*1;
				//	printf("bytes==%d\n",no_bytes);
					if (no_bytes == 0)
					{
						break;
					}
					else
					{
						for(i=0;i<no_bytes-1;i++)
						{
							fprintf(lk,"%c",recv_data[i]);
						}
						if(recv_data[i]!='\n')
							fprintf(lk,"%c ",recv_data[i]);
						else
							fprintf(lk,"%c",recv_data[i]);
					}


				}
				fclose(lk);
				printf("\nFilehash command executed successfully\n");
			}
			//////
			else if(strcmp(parsed_t[0],"IndexGet")==0)
			{
				send(connected1,send_data,strlen(send_data), 0);
				FILE *fpj;
				if(strcmp(parsed_t[1],"ShortList")==0)
				{
					fpj=fopen("server_folder/clientshort.txt","w");
				}
				if(strcmp(parsed_t[1],"LongList")==0)
				{
					fpj=fopen("server_folder/clientlong.txt","w");
				}
				else if(strcmp(parsed_t[1],"RegEx")==0)
				{
					fpj=fopen("server_folder/clientreg.txt","w");
				}
				while(1)
				{
					bytes_recieved1=recv(connected1,recv_data,1024,0);
					int no_bytes;
					int i=0;
					int first,second,third,fourth;
					first=recv_data[1020]-48;
					second=recv_data[1021]-48;
					third=recv_data[1022]-48;
					fourth=recv_data[1023]-48;
					no_bytes=first*1000 + second*100 + third*10 + fourth*1;
					//printf("bytes==%d\n",no_bytes);
					if (no_bytes == 0)
					{
						break;
					}
					else
					{
						for(i=0;i<no_bytes-1;i++)
						{
							fprintf(fpj,"%c",recv_data[i]);
						}
						if(recv_data[i]!='\n')
							fprintf(fpj,"%c ",recv_data[i]);
						else
							fprintf(fpj,"%c",recv_data[i]);
					}


				}
				fclose(fpj);
				printf("\nIndexget command executed successfully\n");

			}


			//////
			else if(strcmp(parsed_t[0],"FileDownload")==0)
			{

				send(connected1, send_data,strlen(send_data), 0); 
				FILE *fp1;FILE *fp2;
				char sender[100];
				strcpy(sender,"server_folder/");
				strcat(sender,parsed_t[1]);
				int sequence=0;
				while(1)
				{
					if(strcmp(parsed_t[2],"udp")==0)
					{
						bytes_recieved1= recvfrom(sock3,recv_data,1024,0,
								(struct sockaddr *)&client_addr3, &addr_len3);
						int i=1,j;
						int num1=0;
						for(j=1012;j>=1002;j--)
						{    
							num1 = num1 + i*(recv_data[j]);
							i=i*10;
						}    
						if(num1!=sequence)
						{    
							sequence=sequence-1;
						}    
						else 
						{    
							sequence=sequence+1;
						}    

					}
					else
						bytes_recieved1=recv(connected1,recv_data,1024,0);
				//	recv_data[bytes_recieved1] = '\0';
					//printf("rec==%d\n",bytes_recieved1);
					int no_bytes;
					int first,second,third,fourth;
					first=recv_data[1020]-48;
					second=recv_data[1021]-48;
					third=recv_data[1022]-48;
					fourth=recv_data[1023]-48;
					no_bytes=first*1000 + second*100 + third*10 + fourth*1;
					//printf("bytes==%d\n",no_bytes);
					if (no_bytes == 0)
					{   
						break;
					}   
					else
					{
						int i=0;
						for(i=0;i<no_bytes;i++)
						{
							fp2=fopen(sender,"a");
							fprintf(fp2,"%c",recv_data[i]);
							fclose(fp2);
						}
					}

				}
				printf("server downloaded the file\n");

			}

			else if(strcmp(parsed_t[0],"FileUpload")==0)
			{
				char sef[100];
				strcpy(sef,"server_folder/");
				strcat(sef,parsed_t[1]);
				FILE *fp1=fopen(sef,"r");
				int sequence=0;
				if(fp1 == NULL)
				{
					printf("\nFile Does Not exit\n");
				}
				else
				{

					send(connected1, send_data,strlen(send_data), 0);
					FILE *fp1;FILE *fp2;
					char upload[100];
					int counter;char ch[2000];
					char c;
					char sef[100];
					strcpy(sef,"server_folder/");
					strcat(sef,parsed_t[1]);
					fp1=fopen(sef,"r");
					int sequence=0;
					if(fp1 == NULL)
						exit(EXIT_FAILURE);
				//	int sequence=0;
					while(fscanf(fp1,"%c",&c)!=EOF)
					{
						ch[counter]=c;
						counter=counter+1;
						if(counter>=1000)
						{
							ch[counter]='\0';
							ch[1020]='1';
							ch[1021]='0';
							ch[1022]='0';
							ch[1023]='0';
							if(strcmp(parsed_t[2],"udp")==0)
							{
								int i=0;
								for(i=1002;i<=1012;i++)
								{
									ch[i]=48;
								}
								i=0;
								while(sequence!=0)
								{
									ch[1012-i]=sequence%10 + 48;
									i--;
									sequence=sequence/10;
								}
								sendto(sock3, ch, 1024, 0,
										(struct sockaddr *)&client_addr3, sizeof(struct sockaddr));
								sequence=sequence+1;
							}
							else
								send(connected1,ch,1024,0);
							counter=0;
						}

					}
					fclose(fp1);
					int t=counter;
					int a=t%10;t=t/10;
					int b=t%10;t=t/10;
					int cc=t%10;t=t/10;
					int d=t%10;
					ch[1020]=d+48;
					ch[1021]=cc+48;
					ch[1022]=b+48;
					ch[1023]=a+48;
					if(strcmp(parsed_t[2],"udp")==0)
					{

						sendto(sock3, ch, 1024, 0,
								(struct sockaddr *)&client_addr3, sizeof(struct sockaddr));
					}
					else
						send(connected1,ch,1024,0);
					counter=0;
					ch[1020]='0';
					ch[1021]='0';
					ch[1022]='0';
					ch[1023]='0';
					if(strcmp(parsed_t[2],"udp")==0)
					{
						sendto(sock3, ch, 1024, 0,
								(struct sockaddr *)&client_addr3, sizeof(struct sockaddr));
					}
					else
					{
						send(connected1,ch,1024,0);
					}
					//      send(sock1,"q",'1',0);
					printf("\nServer uploaded the file\n");
				}

			}				

			else
				send(connected1, send_data,strlen(send_data), 0);  

			fflush(stdout);
		}


	}
	else
	{
		bytes_read4 = recvfrom(sock4,recv_data,1024,0,
				(struct sockaddr *)&client_addr4, &addr_len4);
		printf("\nUDP through sock 4 established\n");

		while(1)
		{   
			fflush(stdout);
			bytes_recieved2=recv(connected2,recv_data,1024,0);
			recv_data[bytes_recieved2] = '\0';
			parse2(recv_data);
			if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
			{   
				close(connected2);
				break;
			}
			/////////////
			else if(strcmp(parsed_s[0],"FileHash")==0)
			{
				if(strcmp(parsed_s[1],"Verify")==0)
				{
					////
					FILE *fpp8;char k1[100];
					strcpy(k1,"server_folder/");
					strcat(k1,parsed_s[2]);
					FILE *k11=fopen(k1,"r");
					char ch[1024];
					if(k11==NULL)
					{     
						ch[1020]='0';
						ch[1021]='0';
						ch[1022]='0';
						ch[1023]='0';
						send(connected2,ch,1024,0);     
						printf("\nFile Does not Exit\n");

					}    
					else
					{
						char kkl[100];
						strcpy(kkl,"ls -lh server_folder/");
						strcat(kkl,parsed_s[2]);
						strcat(kkl," > serverout.txt");
						system(kkl);
						FILE *fpp2;
						fpp2=fopen("serverout.txt","r");
						if(fpp2== NULL)
							exit(EXIT_FAILURE);
						char * line1 = NULL;
						size_t len1 = 0;
						ssize_t read1;
						int ll=0;
						char totalsize[100];
						while ((read1 = getline(&line1, &len1, fpp2)) != -1) 
						{
							parse_info(ll,line1);
							ll=ll+1;
						}
						///
						char ratt[100];char pp[100];
						strcpy(pp,"server_folder/");
						strcat(pp,parsed_s[2]);
						strcpy(ratt,"md5sum ");
						strcat(ratt,pp);
						strcat(ratt," > servercheck.txt");
						system(ratt);
						FILE *fpp1;
						fpp1=fopen("servercheck.txt","r");
						if(fpp1== NULL)
							exit(EXIT_FAILURE);
						char * line = NULL;
						size_t len = 0;
						ssize_t read;
						int count_info=0;
						int kk=0;int i;
						while ((read = getline(&line, &len, fpp1)) != -1)
						{
							parse_check(kk,line);
							kk=kk+1;
						}
						//char ch[1024];
						for(i=0;i<kk;i++)
						{       ///
							//			printf("%s\n",msd[i].msg);
							//			printf("%s\n",msd[i].name);
							int t=strlen(msd[i].msg);int j;
							for(j=0;j<t;j++)
							{
								ch[j]=msd[i].msg[j];
							}
							ch[j]=' ';
							ch[j+1]='\0';
							int a=t%10;t=t/10;
							int b=t%10;t=t/10;
							int cc=t%10;t=t/10;
							int d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;
							send(connected2,ch,1024,0);

							t=strlen(data[0].month);
							for(j=0;j<t;j++)
							{
								ch[j]=data[0].month[j];
							}
							ch[j]='\0';
							a=t%10;t=t/10;
							b=t%10;t=t/10;
							cc=t%10;t=t/10;
							d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;
							send(connected2,ch,1024,0);

							t=strlen(data[0].date);
							for(j=0;j<t;j++)
							{
								ch[j]=data[0].date[j];
							}
							ch[j]='\0';
							a=t%10;t=t/10;
							b=t%10;t=t/10;
							cc=t%10;t=t/10;
							d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;
							send(connected2,ch,1024,0);

							t=strlen(data[0].time);
							for(j=0;j<t;j++)
							{
								ch[j]=data[0].time[j];
							}
							ch[j]='\0';
							a=t%10;t=t/10;
							b=t%10;t=t/10;
							cc=t%10;t=t/10;
							d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;
							send(connected2,ch,1024,0);


							t=strlen(msd[i].name);
							for(j=0;j<t;j++)
							{
								ch[j]=msd[i].name[j];
							}
							ch[j]='\0';
							a=t%10;t=t/10;
							b=t%10;t=t/10;
							cc=t%10;t=t/10;
							d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;
							send(connected2,ch,1024,0);
						}
						ch[1020]='0';
						ch[1021]='0';
						ch[1022]='0';
						ch[1023]='0';
						send(connected2,ch,1024,0);
						printf("\nFileHash Verify request response send\n");
					}

				}
				else if(strcmp(parsed_s[1],"CheckAll")==0)
				{
					system("ls -lh server_folder > serverout.txt");
					FILE *fpp2;
					fpp2=fopen("serverout.txt","r");
					if(fpp2== NULL)
						exit(EXIT_FAILURE);
					char * line1 = NULL;
					size_t len1 = 0;
					ssize_t read1;
					int count_info=0;
					int kk=0;
					char totalsize[100];
					while ((read1 = getline(&line1, &len1, fpp2)) != -1) 
					{
						if(count_info==0)
						{
							strcmp(totalsize,line1);
							count_info=1;
						}
						else
						{
							parse_info(kk,line1);
							kk=kk+1;
						}
					}
					int i=0;int ll=0;
					char ch[1024];
					for(i=0;i<kk;i++)
					{
						int t=strlen(data[i].name);int j;
						for(j=0;j<t;j++)
						{
							ch[j]=data[i].name[j];
						}
						ch[j-1]='\0';
						char ratt[100];char pp[100];
						strcpy(pp,"server_folder/");
						strcat(pp,ch);
						strcpy(ratt,"md5sum ");
						strcat(ratt,pp);
						strcat(ratt," > servercheck.txt");
						//printf("%s\n",ratt);
						system(ratt);
						FILE *fpp1;
						fpp1=fopen("servercheck.txt","r");
						if(fpp1== NULL)
							exit(EXIT_FAILURE);
						char * line = NULL;
						size_t len = 0;
						ssize_t read;
						int count_info=0;
						int kk=0;
						char totalsize[100];
						//printf("klkl\n");
						while ((read = getline(&line, &len, fpp1)) != -1)
						{
							//printf("k111\n");
							parse_check(ll,line);
							//printf("k111\n");
							ll=ll+1;
						}
					}
					for(i=0;i<kk;i++)
					{
						int t=strlen(msd[i].msg);int j;
						//printf("t=%d\n",t);
						for(j=0;j<t;j++)
						{
							ch[j]=msd[i].msg[j];
						}
						ch[j]=' ';		ch[j+1]='\0';
						int a=t%10;t=t/10;
						int b=t%10;t=t/10;
						int cc=t%10;t=t/10;
						int d=t%10;
						ch[1020]=d+48;
						ch[1021]=cc+48;
						ch[1022]=b+48;
						ch[1023]=a+48;
						send(connected2,ch,1024,0);
						t=strlen(data[i].month);
						for(j=0;j<t;j++)
						{
							ch[j]=data[i].month[j];
						}
						ch[j]=' ';
						ch[j+1]='\0';
						a=t%10;t=t/10;
						b=t%10;t=t/10;
						cc=t%10;t=t/10;
						d=t%10;
						ch[1020]=d+48;
						ch[1021]=cc+48;
						ch[1022]=b+48;
						ch[1023]=a+48;
						send(connected2,ch,1024,0);
						t=strlen(data[i].date);
						for(j=0;j<t;j++)
						{
							ch[j]=data[i].date[j];
						}
						ch[j]=' ';
						ch[j+1]='\0';
						a=t%10;t=t/10;
						b=t%10;t=t/10;
						cc=t%10;t=t/10;
						d=t%10;
						ch[1020]=d+48;
						ch[1021]=cc+48;
						ch[1022]=b+48;
						ch[1023]=a+48;
						//printf("%s ",ch);
						send(connected2,ch,1024,0);
						t=strlen(data[i].time);
						for(j=0;j<t;j++)
						{
							ch[j]=data[i].time[j];
						}
						ch[j]=' ';
						ch[j+1]='\0';
						a=t%10;t=t/10;
						b=t%10;t=t/10;
						cc=t%10;t=t/10;
						d=t%10;
						ch[1020]=d+48;
						ch[1021]=cc+48;
						ch[1022]=b+48;
						ch[1023]=a+48;
						//printf("%s ",ch);
						send(connected2,ch,1024,0);
						t=strlen(data[i].name);
						for(j=0;j<t;j++)
						{
							ch[j]=data[i].name[j];
						}
						ch[j]='\0';
						a=t%10;t=t/10;
						b=t%10;t=t/10;
						cc=t%10;t=t/10;
						d=t%10;
						ch[1020]=d+48;
						ch[1021]=cc+48;
						ch[1022]=b+48;
						ch[1023]=a+48;
						//printf("%s \n",ch);
						send(connected2,ch,1024,0);
					}
					ch[1020]='0';
					ch[1021]='0';
					ch[1022]='0';
					ch[1023]='0';
					send(connected2,ch,1024,0);
					printf("\nFileHash CheckAll request response send\n");

				}

			}



			//////////////
			else if(strcmp(parsed_s[0],"IndexGet")==0)
			{
				//	info data[100];
				///
				int flag_k=0;
				if(strcmp(parsed_s[1],"LongList")==0)
				{   
					system("ls -lh server_folder > serverout.txt");
				}   
				else if(strcmp(parsed_s[1],"RegEx")==0)
				{   
					char rat[100];
					strcpy(rat,"ls -lh server_folder/");
					char kl[100];
					strcpy(kl,"server_folder/");
					strcat(kl,parsed_s[2]);
					FILE *rt;
					rt=fopen(kl,"w");
					if(rt == NULL)
					{
				//		flag_k=1;
					}
					strcat(rat,parsed_s[2]);
					strcat(rat," > serverout.txt");
					system(rat);
				}
				else if(strcmp(parsed_s[1],"ShortList")==0)
				{
					system("ls -lh server_folder --full-time | awk '{print $5,$6,$7,$9}' > serverout.txt");
				}
				char ch[1024];
				if(flag_k==1)
				{	
					ch[1020]='0';
					ch[1021]='0';
					ch[1022]='0';
					ch[1023]='0';
					send(connected2,ch,1024,0);
					printf("\nFile does not exit\n");


				}
				else
				{
					FILE *fpp;
					fpp=fopen("serverout.txt","r");
					if(fpp== NULL)
						exit(EXIT_FAILURE);
					char * line = NULL;
					size_t len = 0;
					ssize_t read;
					int count_info=0;
					int kk=0;
					char totalsize[100];
					while ((read = getline(&line, &len, fpp)) != -1) 
					{
						if(count_info==0)
						{
							strcmp(totalsize,line);
							count_info=1;
						}
						else
						{
							if(strcmp(parsed_s[1],"ShortList")==0)
							{
								//printf("hi\n");
								parse_short(kk,line);
								kk=kk+1;
							}
							else
							{							
								parse_info(kk,line);
								kk=kk+1;
							}
						}
					}
					int i;
					FILE *fpk;
				//	char ch[1024];
					//////
					if(strcmp(parsed_s[1],"ShortList")==0)
					{
						char low_date[100];
						char low_time[100];
						char up_date[100];
						char up_time[100];
						strcpy(low_date,parsed_s[2]);
						strcat(low_date,parsed_s[3]);
						strcpy(up_date,parsed_s[4]);
						strcat(up_date,parsed_s[5]);
						for(i=0;i<kk;i++)
						{
							char lp[100];
							strcpy(lp,sh[i].date);
							strcat(lp,sh[i].time);
							//	printf("date=%s time=%s name=%s",sh[i].date,sh[i].time,sh[i].name);
							if(strcmp(lp,low_date)>=0 && strcmp(lp,up_date)<=0)
							{

								//	printf("date=%s time=%s name=%s",sh[i].date,sh[i].time,sh[i].name);
								int t=strlen(sh[i].size);int j;
								for(j=0;j<t;j++)
								{
									ch[j]=sh[i].size[j];
								}
								ch[j]=' ';
								ch[j+1]='\0';
								int a=t%10;t=t/10;
								int b=t%10;t=t/10;
								int cc=t%10;t=t/10;
								int d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;
								send(connected2,ch,1024,0);
								///////
								t=strlen(sh[i].date);
								for(j=0;j<t;j++)
								{
									ch[j]=sh[i].date[j];
								}
								ch[j]='\0';
								a=t%10;t=t/10;
								b=t%10;t=t/10;
								cc=t%10;t=t/10;
								d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;				
								send(connected2,ch,1024,0);


								t=strlen(sh[i].time);
								for(j=0;j<t;j++)
								{
									ch[j]=sh[i].time[j];
								}
								ch[j]='\0';
								a=t%10;t=t/10;
								b=t%10;t=t/10;
								cc=t%10;t=t/10;
								d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;				
								send(connected2,ch,1024,0);



								//////
								t=strlen(sh[i].name);
								for(j=0;j<t;j++)
								{
									ch[j]=sh[i].name[j];
								}
								ch[j]='\0';
								a=t%10;t=t/10;
								b=t%10;t=t/10;
								cc=t%10;t=t/10;
								d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;				
								send(connected2,ch,1024,0);
							}
						}
						ch[1020]='0';
						ch[1021]='0';
						ch[1022]='0';
						ch[1023]='0';
						send(connected2,ch,1024,0);
						printf("\nIndexget Shortlist request response send\n");
					}
					//////////
					else if(strcmp(parsed_s[1],"LongList")==0 || strcmp(parsed_s[1],"RegEx")==0)
					{
						for(i=0;i<kk;i++)
						{					
							///
							int t=strlen(data[i].size);int j;
							for(j=0;j<t;j++)
							{
								ch[j]=data[i].size[j];
							}
							ch[j]=' ';
							ch[j+1]='\0';
							int a=t%10;t=t/10;
							int b=t%10;t=t/10;
							int cc=t%10;t=t/10;
							int d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;
							send(connected2,ch,1024,0);
							///////
							if(strcmp(parsed_s[1],"RegEx")!=0)
							{
								t=strlen(data[i].month);
								for(j=0;j<t;j++)
								{
									ch[j]=data[i].month[j];
								}
								ch[j]=' ';
								ch[j+1]='\0';
								a=t%10;t=t/10;
								b=t%10;t=t/10;
								cc=t%10;t=t/10;
								d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;
								send(connected2,ch,1024,0);
								//////////
								t=strlen(data[i].date);
								for(j=0;j<t;j++)
								{
									ch[j]=data[i].date[j];
								}
								ch[j]=' ';
								ch[j+1]='\0';
								a=t%10;t=t/10;
								b=t%10;t=t/10;
								cc=t%10;t=t/10;
								d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;
								send(connected2,ch,1024,0);
								//////
								t=strlen(data[i].time);
								for(j=0;j<t;j++)
								{
									ch[j]=data[i].time[j];
								}
								ch[j]=' ';
								ch[j+1]='\0';
								a=t%10;t=t/10;
								b=t%10;t=t/10;
								cc=t%10;t=t/10;
								d=t%10;
								ch[1020]=d+48;
								ch[1021]=cc+48;
								ch[1022]=b+48;
								ch[1023]=a+48;
								send(connected2,ch,1024,0);
							}
							//////
							t=strlen(data[i].name);
							for(j=0;j<t;j++)
							{
								ch[j]=data[i].name[j];
							}
							ch[j]='\0';
							a=t%10;t=t/10;
							b=t%10;t=t/10;
							cc=t%10;t=t/10;
							d=t%10;
							ch[1020]=d+48;
							ch[1021]=cc+48;
							ch[1022]=b+48;
							ch[1023]=a+48;				
							send(connected2,ch,1024,0);
						}
						ch[1020]='0';
						ch[1021]='0';
						ch[1022]='0';
						ch[1023]='0';
						send(connected2,ch,1024,0);
						printf("\nIndexget Longlist/RegEx request response sended\n");
					}
				}
				
			}
			else if(strcmp(parsed_s[0],"FileDownload")==0)
			{   
				int counter;char ch[2000];
				char c;FILE *fp;
				char sef[100];
				strcpy(sef,"server_folder/");
				strcat(sef,parsed_s[1]);
				fp=fopen(sef,"r");
				if(fp == NULL)
				{
					ch[1020]='0';
					ch[1021]='0';
					ch[1022]='0';
					ch[1023]='0';
					send(connected2,ch,1024,0);
					printf("\nFILE does not exit\n");
					//exit(EXIT_FAILURE);
				}
				else
				{
					int sequence=0;
					while(fscanf(fp,"%c",&c)!=EOF)
					{   
						ch[counter]=c;
						counter=counter+1;
						if(counter>=1000)
						{   
							ch[counter]='\0';
							ch[1020]='1';
							ch[1021]='0';
							ch[1022]='0';
							ch[1023]='0';
							if(strcmp(parsed_s[2],"udp")==0)
							{
								int i=0;
								for(i=1002;i<=1012;i++)
								{
									ch[i]=48;
								}
								i=0;
								while(sequence!=0)
								{
									ch[1012-i]=sequence%10 + 48;
									i--;
									sequence=sequence/10;
								}
								sendto(sock4, ch, 1024, 0,
										(struct sockaddr *)&client_addr4, sizeof(struct sockaddr));
							}
							else
							{
								send(connected2,ch,1024,0);
							}
							counter=0;
						}   

					}   
					fclose(fp);
					int t=counter;
					int a=t%10;t=t/10;
					int b=t%10;t=t/10;
					int cc=t%10;t=t/10;
					int d=t%10;
					ch[1020]=d+48;
					ch[1021]=cc+48;
					ch[1022]=b+48;
					ch[1023]=a+48;
					if(strcmp(parsed_s[2],"udp")==0)
					{
						sendto(sock4, ch, 1024, 0,
								(struct sockaddr *)&client_addr4, sizeof(struct sockaddr));
					}
					else
					{
						send(connected2,ch,1024,0);
					}
					counter=0;
					ch[1020]='0';
					ch[1021]='0';
					ch[1022]='0';
					ch[1023]='0';
					if(strcmp(parsed_s[2],"udp")==0)
					{
						sendto(sock4, ch, 1024, 0,
								(struct sockaddr *)&client_addr4, sizeof(struct sockaddr));
					}
					else
						send(connected2,ch,1024,0);
					//      send(sock1,"q",'1',0);
					printf("\nDATA send by server\n");
				}

			}
			else if(strcmp(parsed_s[0],"FileUpload")==0)
			{
				FILE *fp1;FILE *fp2;
				char send[100];
				strcpy(send,"server_folder/");
				strcat(send,parsed_s[1]);
				int sequence=0;
				while(1)
				{
					if(strcmp(parsed_s[2],"udp")==0)
					{
						bytes_recieved2 = recvfrom(sock4,recv_data,1024,0,
								(struct sockaddr *)&client_addr4, &addr_len4);
						int i=1,j;
						int num1=0;
						for(j=1012;j>=1002;j--)
						{    
							num1 = num1 + i*(recv_data[j]);
							i=i*10;
						}    
						if(num1!=sequence)
						{    
							sequence=sequence-1;
						}    
						else 
						{    
							sequence=sequence+1;
						}    

					}
					else
					{
						bytes_recieved2=recv(connected2,recv_data,1024,0);
					}
					//	recv_data[bytes_recieved1] = '\0';
				//	printf("rec==%d\n",bytes_recieved2);
					int no_bytes;
					int first,second,third,fourth;
					first=recv_data[1020]-48;
					second=recv_data[1021]-48;
					third=recv_data[1022]-48;
					fourth=recv_data[1023]-48;
					no_bytes=first*1000 + second*100 + third*10 + fourth*1;
					//printf("bytes==%d\n",no_bytes);
					if (no_bytes == 0)
					{   
						break;
					}   
					else
					{
						int i=0;
						for(i=0;i<no_bytes;i++)
						{
							fp2=fopen(send,"a");
							fprintf(fp2,"%c",recv_data[i]);
							fclose(fp2);
						}
					}


				}
					printf("server the file got uploaded\n");
	


			}

			else
				printf("\nRecieved data  from client 2= %s \n" , recv_data);

			fflush(stdout);
		}   

	}


	close(connected1);
	close(connected2);
	return 0;
} 

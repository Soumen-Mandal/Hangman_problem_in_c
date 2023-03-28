//Header file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>


//Driver code
int main()
{
    //Initialize the variables
    int i,j,lives=5,flag = 0;
    int num, k, count =0;
    char ch;
    char next_ch;
    char *temp;
    char c[500][50] ,*a,*b;

    //Reading from file
    FILE *fp;
    if(NULL == (fp = fopen("movie-list.txt","r"))){
        printf("File not found.");
    }

        for(i=1;i<374;i++){
            fgets(c[i],50,fp);
        }
    fclose(fp);
    
    //Generate a random number and choose that movie
    srand(time(NULL));
    num = (rand() % 374)+1;
   
    a = (char*)calloc(strlen(c[num]),sizeof(char));

    for(i=0;i<strlen(c[num])-1;i++){
        a[i] = c[num][i];
    }
    a[i] = '\0';
    
    /*Here you can print the full movie name and line number
    that has been choosen from the file*/
    //printf("The %d movie is %s\n",num,a);
    
    printf("Guess the movie name by a single character or by whole name\n");

    b = (char*)calloc(strlen(a),sizeof(char));
    strcpy(b,a);  //copy a in b

    /*Here we generate three random mumber and omit the character
    as define in the problem*/
    for(j=0;j<3;j++){
        int p = rand() % (strlen(a));
        for(k=0; k<strlen(a); k++){
            if(a[k] == b[p]){
                b[k] = '_';
            }
        }  
        b[p] = '_';  
    }

    printf("%s\t\t\t\tlives=%d\n",b,lives);

    /*Starting the main loop and the loop will be breaked either
    lives will be finished or the guesses is right*/
    while(lives != 0 && strcmp(a,b) != 0){
        ch = getchar();          //taking two character first
        next_ch = getchar();
        flag = 0;
        /*when the user guess only one character and the next is '\n'
        then this loop works*/
        if(next_ch == '\n'){
            count++;
            for(i=0;i<strlen(a);i++){
                if(b[i]=='_' && a[i]==toupper(ch)){
                    b[i] = a[i];
                    flag = 1;
                }
            }
        }
        /*when the user guess the entire name of the movie
        then this loop works*/
        else{
            count++;
            free(temp);
            temp = (char*)calloc(50,sizeof(char));
            i = 0;
            temp[0]=toupper(ch);
            i++;
            ch = next_ch;
            temp[i]=toupper(ch);
            i++;
            while((ch = getchar()) != '\n'){
                temp[i] = toupper(ch);
                i++;
            }
            temp[i] = '\0';
            if(strcmp(a,temp) == 0){
                flag = 1;
                b = temp;
            }
        } 

            if(flag==0){                    //if user guess the wrong thing
                lives--;                      //then the lives goes down by 1
                printf("Wrong guess!\n");
            }

            printf("%s\t\t\t\tlives=%d\n\n",b,lives);
    }
    //if the user guess the right name
    if(strcmp(a,b)==0)
        printf("Correct! Your score is %d\n",count);


return 0;

}
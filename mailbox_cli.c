#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CONST_SIZE 4096
FILE * BC_pointer;
FILE * MB_pointer;
char * MESSAGE_STRUCT[5] = {"ID: ", "Sender: ", "Receiver: ", "Subject: ", "The content of the letter: "};


unsigned int CheckBitCard(){
    char new_buffer[CONST_SIZE];
    unsigned int counter = 0, i = 0;
    BC_pointer = fopen("bitcard.txt", "r");
    fscanf(BC_pointer, "%s", new_buffer);
    while(*(new_buffer + i) != NULL)i++;
    if(i == 6) return 1;
    else return i;
    }

void ShowMessageByID(unsigned int id){
    unsigned int length = CheckBitCard(), counter = 1, parserPos = 0;
    char new_buffer[1126];
    MB_pointer = fopen("mailbox.txt", "r");
    while(fgets(new_buffer, 1126, MB_pointer)){
        if(id == counter){ 
            char * sepator = strtok(new_buffer, ";");
            while(sepator != NULL) {
                printf( "\n%s %s", MESSAGE_STRUCT[parserPos], sepator);
                parserPos++;
                sepator = strtok(NULL, ";");
            }
            break;
        }
        counter++;
    }
    fclose(MB_pointer);
}

char * getField(unsigned int field, char *new_buffer){
    char * buf = malloc(sizeof(char) * (strlen(new_buffer)+1));
    strcpy(buf, new_buffer);
    unsigned int parserPos = 0;
    char * sepator = strtok(buf, ";");
    while(sepator != NULL) {
        if(field == parserPos) return sepator;
        parserPos++;
        sepator = strtok(NULL, ";");
    }
}

unsigned int checkIfDeleted(unsigned int id){
    char new_buffer[CONST_SIZE];
    BC_pointer = fopen("bitcard.txt", "r");
    fscanf(BC_pointer, "%s", new_buffer);
    if(new_buffer[id+5] == 0){
        fclose(BC_pointer);
        return 1;
    }else{
        fclose(BC_pointer);
        return 0;
    }
}

void showAllWithSubject(char *s){
    unsigned int length = CheckBitCard();
    int lastByte = 0;
    char new_buffer[1126];
    MB_pointer = fopen("mailbox.txt", "r");
        while(fgets(new_buffer, 1126, MB_pointer)){
            int i = 0;
            char *field = getField(3, new_buffer);
            if(strstr(field, s) != NULL){
                for(int number = 0; number < 5; number++){
                    printf("%s", MESSAGE_STRUCT[number]);
                    printf("%s", getField(number, new_buffer));
                    printf("\n");
                }
                continue;
            }
        }

    fclose(MB_pointer);
}

void showDeleted(){
    char new_buffer[CONST_SIZE];
    unsigned int i = 0;
    BC_pointer = fopen("bitcard.txt", "r");
    fscanf(BC_pointer, "%s", new_buffer);
    while(i < CONST_SIZE){
        if(new_buffer[i] == '0'){
            ShowMessageByID(i+1);
        }
        i++;
    }
    fclose(BC_pointer);
}

unsigned int addMessageToBC(){
    unsigned int i=0;
    char new_buffer[CONST_SIZE];
    BC_pointer = fopen("bitcard.txt", "r");
    fscanf(BC_pointer, "%s", new_buffer);
    
    while(*(new_buffer + i) != NULL){
        i++;   
    }   
    i++;
    new_buffer[i] = 1;
    fclose(BC_pointer);
    BC_pointer = fopen("bitcard.txt", "a");
    fprintf(BC_pointer, "%d", 1);
    fclose(BC_pointer);
    if(i == 6) return 1;
    else return i;
    
}

int deleteMessage(unsigned int id){
    char new_buffer[CONST_SIZE];
    BC_pointer = fopen("bitcard.txt", "r");
    fscanf(BC_pointer, "%s", new_buffer);
    fclose(BC_pointer);
    new_buffer[id-1] = '0';
    BC_pointer = fopen("bitcard.txt", "w");
    fprintf(BC_pointer, "%s", new_buffer);
    fclose(BC_pointer);
    return id-1;
}

void addMessageEntryToStorage(unsigned int id, char *subject, char *message, char *sender, char *receiver){
    MB_pointer = fopen("mailbox.txt", "a");
    fprintf(MB_pointer, "%d;%s;%s;%s;%s\n", id, subject, message, sender, receiver);
    fclose(MB_pointer);
}

void addMessage(char *subject, char *message, char *receiver, char *sender){
    unsigned int index = addMessageToBC();
    addMessageEntryToStorage(index, receiver, sender, subject, message);
};

void getAllMessagesWithSender(char *s){
    unsigned int length = CheckBitCard();
    int lastByte = 0;
    char new_buffer[1126];
    MB_pointer = fopen("mailbox.txt", "r");
        while(fgets(new_buffer, 1126, MB_pointer)){
            int i = 0;
            char *field = getField(1, new_buffer);
            if(strcmp(field, s) == 0){
                for(int number = 0; number < 5; number++){
                    printf("%s", MESSAGE_STRUCT[number]);
                    printf("%s", getField(number, new_buffer));
                    printf("\n");
                }
                continue;
            }
        }

    fclose(MB_pointer);
}

void getAllMessagesWithReceiver(char *s){
    unsigned int length = CheckBitCard();
    int lastByte = 0;
    char new_buffer[1126];
    MB_pointer = fopen("mailbox.txt", "r");
        while(fgets(new_buffer, 1126, MB_pointer)){
            int i = 0;
            char *field = getField(2, new_buffer);
            if(strcmp(field, s) == 0){
                for(int number = 0; number < 5; number++){
                    printf("%s", MESSAGE_STRUCT[number]);
                    printf("%s", getField(number, new_buffer));
                    printf("\n");
                }
                continue;
            }
        }

    fclose(MB_pointer);
}

void showStory(char *user1, char *user2){
    unsigned int length = CheckBitCard();
    int lastByte = 0;
    char new_buffer[1126];
    MB_pointer = fopen("mailbox.txt", "r");
        while(fgets(new_buffer, 1126, MB_pointer)){
            int i = 0;
            char *field1 = getField(1, new_buffer);
            char *field2 = getField(2, new_buffer);
            if((strcmp(field1, user1) == 0 || strcmp(field1, user2) == 0)&&(strcmp(field2, user1) == 0 || strcmp(field2, user2) == 0)){
                for(int number = 0; number < 5; number++){
                    printf("%s", MESSAGE_STRUCT[number]);
                    printf("%s", getField(number, new_buffer));
                    printf("\n");
                }
                continue;
            }
        }

    fclose(MB_pointer);
}

int main(){
    int select;
    char subject[60], message[1000], receiver[30], sender[30];
    while(1){
        printf("\nOptions:\n");
        printf("\n1. New Message\n2. Delete Message\n3. Find by ID\n4. Find by Sender\n5. Find by Receiver\n6. View full dialog\n7. Show deleted\n8. Find by subject");
        printf("\n\nSelect option: ");
        scanf("%d", &select);
        if(select == 1){
            printf("\nEnter Sender: ");
            scanf("%s", sender);
            printf("\nEnter Receiver: ");
            scanf("%s", receiver);
            printf("\nEnter Subject: ");
            scanf("%s", subject);
            printf("\nEnter Message: ");
            scanf("%s", message);
            addMessage(subject, message, receiver, sender);
            printf("\n*** Success ***\n");
        }
        if(select == 2){
            unsigned int id;
            printf("\nEnter ID: ");
            scanf("%d", &id);
            if(checkIfDeleted(id) == 1){
                printf("\n*** Letter was deleted ***\n");
            }else{
                deleteMessage(id);
                printf("\n*** Letter successfully deleted ***\n");
            }
        }
        if(select == 3){
            unsigned int id;
            printf("\nInput ID: ");
            scanf("%d", &id);
            if(CheckBitCard() >= id){
                if(checkIfDeleted(id) == 1){
                    printf("\n *** Message was deleted ***\n");
                }else{
                    ShowMessageByID(id);
                }
            }else{
                printf("\n *** Incorrect ID ***\n");
            }
        }
        if(select == 4){
            printf("\nEnter Sender: ");
            scanf("%s", sender);
            getAllMessagesWithSender(sender);
        }
        if(select == 5){
            printf("\nEnter Receiver: ");
            scanf("%s", sender);
            getAllMessagesWithSender(sender);
        }
        if(select == 6){
            char sender2[30];
            printf("\nEnter sender #1: ");
            scanf("%s", sender);
            printf("\nEnter sender #2: ");
            scanf("%s", sender2);
            showStory(sender, sender2);
        }
        if(select == 7){
            showDeleted();
        }
        if(select == 8){
            char subject[60];
            printf("\nEnter subject name: ");
            scanf("%s", subject);
            showAllWithSubject(subject);
        }
    }
};

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

struct Keyword
{
    char word[20];
    int risk;
};

struct Email
{
    int id;
    char sender[50];
    char subject[100];
    char content[500];
    int score;
    char status[20];
};

struct Node
{
    struct Email email;
    struct Node *next;
};

struct Keyword keywords[] =
{
    {"otp", 20},
    {"password", 20},
    {"bank", 15},
    {"lottery", 15},
    {"urgent", 10},
    {"winner", 10},
    {"click", 5},
    {"verify", 10},
    {"claim", 10},
    {"prize", 10},
    {"account", 10},
    {"suspended", 15}
};

int keywordCount = 12;

/* Convert text to lowercase */
void convertLower(char text[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = tolower(text[i]);
    }
}

/* Analyze email */
int analyzeEmail(char content[])
{
    int score = 0;
    int i;

    convertLower(content);

    printf("\nSuspicious Keywords Found:\n");

    for (i = 0; i < keywordCount; i++)
    {
        if (strstr(content, keywords[i].word) != NULL)
        {
            printf("%s +%d\n",
                   keywords[i].word,
                   keywords[i].risk);

            score = score + keywords[i].risk;
        }
    }

    return score;
}

/* Classify email */
void classifyEmail(int score, char status[])
{
    if (score <= 20)
    {
        strcpy(status, "SAFE");
    }
    else if (score <= 50)
    {
        strcpy(status, "SUSPICIOUS");
    }
    else
    {
        strcpy(status, "FRAUDULENT");
    }
}

/* Add email to linked list */
void addHistory(struct Node **head, struct Email email)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->email = email;
    newNode->next = *head;

    *head = newNode;
}

/* Display history */
void displayHistory(struct Node *head)
{
    printf("\n========================================\n");
    printf("       EMAIL ANALYSIS HISTORY\n");
    printf("========================================\n");

    while (head != NULL)
    {
        printf("\nEmail ID : %d\n", head->email.id);
        printf("Sender   : %s\n", head->email.sender);
        printf("Subject  : %s\n", head->email.subject);
        printf("Score    : %d\n", head->email.score);
        printf("Status   : %s\n", head->email.status);

        head = head->next;
    }
}

int main()
{
    struct Email email;
    struct Node *history = NULL;

    printf("========================================\n");
    printf("       EMAIL FRAUD DETECTION SYSTEM\n");
    printf("========================================\n");

    email.id = 1;

    printf("\nEnter Sender: ");
    fgets(email.sender, sizeof(email.sender), stdin);
    email.sender[strcspn(email.sender, "\n")] = '\0';

    printf("Enter Subject: ");
    fgets(email.subject, sizeof(email.subject), stdin);
    email.subject[strcspn(email.subject, "\n")] = '\0';

    printf("Enter Email Content: ");
    fgets(email.content, sizeof(email.content), stdin);
    email.content[strcspn(email.content, "\n")] = '\0';

    email.score = analyzeEmail(email.content);

    classifyEmail(email.score, email.status);

    printf("\n========================================\n");
    printf("Risk Score : %d\n", email.score);
    printf("Status     : %s\n", email.status);
    printf("========================================\n");

    addHistory(&history, email);

    displayHistory(history);

    return 0;
}

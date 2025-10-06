#include <stdio.h>
#include <string.h>
typedef struct Website{
    char url[100];
    char title[100];
} Website;


typedef struct Websites{
    Website sites[100];
    int top;
} Websites;

void createWebsite(Website* w, const char* url, const char* title){
    strcpy(w->url, url);
    strcpy(w->title, title);
}

void createWebsites(Websites* w){
    w->top = 0;
}

void pushWebsite(Websites* w, Website site){
    w->sites[w->top] = site;
    w->top++;
    
}

void popWebsite(Websites* w){
    w->sites[w->top - 1];
    w->top--;
    printf("Back to previous website\n");
}

int main(){
    Websites stack;
    createWebsites(&stack);
    Website w1, w2, w3;
    createWebsite(&w1, "https://www.google.com", "Google");
    createWebsite(&w2, "https://www.facebook.com", "Facebook");
    createWebsite(&w3, "https://www.youtube.com", "YouTube");

    pushWebsite(&stack, w1);
    pushWebsite(&stack, w2);
    pushWebsite(&stack, w3);

    printf("Current website: %s - %s\n", stack.sites[stack.top - 1].title, stack.sites[stack.top - 1].url);

    popWebsite(&stack);
    printf("Current website: %s - %s\n", stack.sites[stack.top - 1].title, stack.sites[stack.top - 1].url);
    popWebsite(&stack);
    printf("Current website: %s - %s\n", stack.sites[stack.top - 1].title, stack.sites[stack.top - 1].url);
    popWebsite(&stack);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "musicians.h"

void print_musician(musician_t *self){
    printf("\tName:\t\t%10s\n\tSurname:\t%10s\n\tBirthday:\t%10s\n\tAlbums:\t%10d\n\tRating:\t%10.2f\n\tGenre:\n\t\tName:\t%10s\n\t\tSpeciality:%10s\n\t\tInstruments:\n\t\t\t%10s\n\t\t\t%10s\n", self->name, self->surname, self->date, self->albums, self->rating, self->genre->name, self->genre->speciality, self->genre->instruments[0], self->genre->instruments[1]);
}

void xml_out(char *text){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return;
    }
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            printf("Tag name <%s>\n", xCur->name);
            for(xmlNode *xJ = xCur->children; xJ != NULL; xJ = xJ->next){
                if(XML_ELEMENT_NODE == xJ->type){
                    if(strcmp(xJ->name, "genre") == 0){
                        xmlNode *xGenre = xJ;
                        char *name = xmlGetProp(xGenre, "name");
                        printf("\t%10s: %s\n", xGenre->name, name);
                        for(xmlNode *xIn = xGenre->children->next; xIn != NULL; xIn = xIn->next){
                            if(XML_ELEMENT_NODE == xIn->type){
                                const char *content = xmlNodeGetContent(xIn);
                                printf("\t%10s: %s\n", xIn->name, content);
                            }
                        }
                        continue;
                    }
                    const char *content = xmlNodeGetContent(xJ);
                    printf("\t%10s: %s\n", xJ->name, content);
                }
            }
        }
        printf("\n");
    }
}

int musicians_count(char *text){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return 0;
    }
    int count = 0;
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            count++;
        }
    }
    return count;
}

void xml_extract(char *text, list_t *list){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return;
    }

    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    int i = 0;
    for(xmlNode * xCur = xRootEl->children; NULL != xCur, i < musicians_count(text); xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            musician_t *musicians = new_musician();
            for(xmlNode *xJ = xCur->children; xJ != NULL; xJ = xJ->next){
                if(XML_ELEMENT_NODE == xJ->type){
                    if(!strcmp(xJ->name, "genre")){
                        xmlNode *xCath = xJ;
                        char *name = xmlGetProp(xCath, "name");
                        strcpy(musicians->genre->name, name);
                        for(xmlNode *xGr = xCath->children->next; xGr != NULL; xGr = xGr->next){
                            if(XML_ELEMENT_NODE == xGr->type){
                               if(!strcmp(xGr->name, "instruments")){
                                    int j = 0;
                                    for(xmlNode *xAgr = xGr->children->next; xAgr != NULL; xAgr = xAgr->next){
                                        if(XML_ELEMENT_NODE == xAgr->type){
                                            if(!strcmp(xAgr->name, "instrument")){
                                                const char *content = xmlNodeGetContent(xAgr);
                                                musicians->genre->instruments[j] = content;
                                                j++;
                                            }
                                        }
                                    }
                                    continue;
                                } else if(!strcmp(xGr->name, "speciality")){
                                    const char *content = xmlNodeGetContent(xGr);
                                    strcpy(musicians->genre->speciality, content);
                                }
                            }
                        }
                        continue;
                    }
                    else {
                        const char *content = xmlNodeGetContent(xJ);
                        if(!strcmp(xJ->name, "name")){
                            strcpy(musicians->name, content);
                        }
                        else if(!strcmp(xJ->name, "surname")){
                            strcpy(musicians->surname, content);
                        }
                        else if(!strcmp(xJ->name, "birthday")){
                            strcpy(musicians->date, content);
                        }
                        else if(!strcmp(xJ->name, "albums")){
                            musicians->albums = atoi(content);
                        }
                        else if(!strcmp(xJ->name, "rating")){
                            musicians->rating = atof(content);
                        }
                    }
                }
            }
            i++;
            list_add(list, musicians);
        }
    }
}

char *musician_to_message(musician_t *self, int id){
    if(!self)
        return NULL;
    char buff[MSG_LENGTH];
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * teacherNode = NULL;
	xmlNode * genreNode = NULL;
    doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "teachers");
	xmlDocSetRootElement(doc, rootNode);
	char strBuf[100];
	teacherNode = xmlNewChild(rootNode, NULL, "teacher", NULL);
	sprintf(strBuf, "%i", id);
	xmlNewChild(teacherNode, NULL, "id", strBuf);
	xmlNewChild(teacherNode, NULL, "firstName", self->name);
	xmlNewChild(teacherNode, NULL, "lastName", self->surname);
	xmlNewChild(teacherNode, NULL, "birthday", self->date);
	sprintf(strBuf, "%i", self->albums);
	xmlNewChild(teacherNode, NULL, "albums", strBuf);
	sprintf(strBuf, "%f", self->rating);
	xmlNewChild(teacherNode, NULL, "rating", strBuf);
	genreNode = xmlNewChild(teacherNode, NULL, "genre", NULL);
	xmlNewProp(genreNode, "name", self->genre->name);
	xmlNewChild(genreNode, NULL, "speciality", self->genre->speciality);
	xmlNewChild(genreNode, NULL, "instrument", self->genre->instruments[0]);
	xmlNewChild(genreNode, NULL, "instrument", self->genre->instruments[1]);
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlBufferFree(bufferPtr);
    return buff;
}

char *all_musicians_to_message(list_t *list){
    if(list_count(list) == 0){
        return NULL;
    }
    char buff[MSG_LENGTH];
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
    doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "musicians");
	xmlDocSetRootElement(doc, rootNode);
	char strBuf[100];
    for(int i = 0; i  < list_count(list); i++){
        musician_t *self = list_get(list, i);
        int id = list_id(list, i);
        xmlNode * musicianNode = NULL;
        xmlNode * genreNode = NULL;
        musicianNode = xmlNewChild(rootNode, NULL, "musician", NULL);
        sprintf(strBuf, "%i", id);
        xmlNewChild(musicianNode, NULL, "id", strBuf);
        xmlNewChild(musicianNode, NULL, "firstName", self->name);
        xmlNewChild(musicianNode, NULL, "lastName", self->surname);
        xmlNewChild(musicianNode, NULL, "birthday", self->date);
        sprintf(strBuf, "%i", self->albums);
        xmlNewChild(musicianNode, NULL, "albums", strBuf);
        sprintf(strBuf, "%f", self->rating);
        xmlNewChild(musicianNode, NULL, "rating", strBuf);
        genreNode = xmlNewChild(musicianNode, NULL, "genre", NULL);
        xmlNewProp(genreNode, "name", self->genre->name);
        xmlNewChild(genreNode, NULL, "speciality", self->genre->speciality);
        xmlNewChild(genreNode, NULL, "instrument", self->genre->instruments[0]);
        xmlNewChild(genreNode, NULL, "instrument", self->genre->instruments[1]);
    }
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    return buff;
}

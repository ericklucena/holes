/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-24 21:50:03
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 00:55:37
*/

#ifndef _ELUCENAP_CIRCULARLIST_H
#define _ELUCENAP_CIRCULARLIST_H

#include <stdio.h>

typedef struct _ELUCENAP_CIRCULARLIST_H{
    Node *head;
} CircularList;

CircularList* newCircularList();
void insertOnHead(CircularList *list, Node *node);
void insertBefore (Node *node, Node *newNode);
void insertAfter (Node *node, Node *newNode);
Node* removeNode (Node *node);
void printCircularList(CircularList *list);

#endif

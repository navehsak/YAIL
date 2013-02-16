#include<iostream>
#include<cstring>
#include<list>
#include "tokens.h"
using namespace std;

#ifndef __NODE_TYPE
#define __NODE_TYPE
    
class Node{
    protected:
               int nodeType;
    public:
            Node( int nType ){
                nodeType = nType;
            }
            
            int getType(void){
                return nodeType;
            }
            
            virtual void dummy(void){
            }
};

class Identifier: public Node{
    protected:
               char* name;
    public:
           Identifier( char* n ): Node( __ident ){
                name = new char[ strlen(n) + 1 ];
                strcpy( name, n );
           }
           
           char* getName(void){
                return name;
           }
};

class String: public Node{
    protected:
                char* string;
                int length;
    public:
             String( char* str ) : Node( __string ){
                length = strlen(str);
                string = removeQuotes( str, length );                
             }
             
             char* getString(void){
                return string;
             }
             
             int getLength(void){
                return length;
             }
             
             char* removeQuotes( char* str, int length ){
                char *target = new char[ length - 1 ];
                int j = 0;
                for( int i = 0; str[i] != '\0'; i++ ){
                    if( str[i] != '"' ){
                        target[j++] = str[i];
                    }
                }
                target[j] = '\0';
                return target;
             }
};

class Operator: public Node{
    protected:
              list<Node*> *operands;
              int nops;
    public:
            Operator( int nType, int nOps, list<Node*> *ops ): Node( nType ){
                nops = nOps;
                operands = ops;
            }
            list<Node*>* getOperands(void){
                return operands;
            }
            int getOpsLength(void){
                return nops;
            }
};

class List : public Node{
    protected:
              list<Node*> nodeList;
    public:
             List( int nodeType ): Node( nodeType ){
             }
             
             void push( Node* node ){
                nodeList.push_back(node);
             }
             
             Node* pop(void){
                Node* rval = get(0);
                nodeList.pop_front();
                return rval;
             }
             
             Node* get( int index ){
                list<Node*>::iterator it;
                it = nodeList.begin();
                for( int i = 0; i < index && it != nodeList.end(); ++it, i++ );
                return *it;
             }
             
             int getLength(void){
                return nodeList.size();
             }
             
             void clear(){
                nodeList.clear();
             }
};

class ParameterList : public List{
    public:
             ParameterList() : List( __params ){
             }
};

class ArgumentList : public List{
    public:
             ArgumentList() : List( __args ){
             }
};

class StatementList : public List{
    public:
             StatementList(): List( __stmtlist ){
             }
};

class FunctionCall : public Node{
    protected:
              Identifier *functName;
              ParameterList *plist;
    public:
            FunctionCall( Identifier *ident, ParameterList *pList ) : Node( __funct_call ){
                functName = ident;
                plist = pList;
            }
};

class FunctionDefinition : public Node{
    protected:
              Identifier    *functName;
              ArgumentList  *arglist;
              StatementList *statementList;
    public:
           FunctionDefinition( Identifier *ident, ArgumentList *argList, StatementList *stmtList ): Node( __funct_def ){
                functName = ident;
                arglist = argList;
                statementList = stmtList;
           }
           
           StatementList* getStatementList(void){
                return statementList;
           }
           
           ArgumentList* getArgumentList(void){
                return arglist;
           }
           
           Identifier* getFunctName(void){
                return functName;
           }
};
#endif

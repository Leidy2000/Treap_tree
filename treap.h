#ifndef TREAP_H_INCLUDED
#define TREAP_H_INCLUDED

#include<iostream>
#include<queue>
#include<stdlib.h>  //Ҫ��
#include<stdio.h>
#include<fstream>
#include<time.h>
using namespace std;

//�ṹ��  treap���Ľڵ�
struct treapNode
{
    int element;//ֵ
    int priority;
    treapNode *leftChild,   //����
                 *rightChild;  //�Һ���

    treapNode() {leftChild = rightChild = NULL;}
    treapNode(const int& theElement, int pri):element(theElement){leftChild = rightChild = NULL; priority = pri;}
    treapNode(const int& theElement, int pri, treapNode *theLeftChild, treapNode *theRightChild):element(theElement){
        leftChild = theLeftChild; priority = pri; rightChild = theRightChild;
    }
};

//�� treap��
class treapTree
{
public:
    treapTree() {root = NULL; treeSize = 0;}//���캯����ʼ��
    bool empty() const {return treeSize == 0;}//�ж϶����������Ƿ�Ϊ��
    int size() const {return treeSize;}//���ض�����������Ԫ�ظ���

    void insert(treapNode* &now, int& theElement);//����Ԫ�غ���
    void init(int* a, int n);
    void insertx(int& theElement) {insert(root, theElement);}
    void erase(treapNode* &now, int& theElement);//ɾ��Ԫ�غ���
    void deletex(int& theElement) {erase(root, theElement);}

    //���ؼ������������������
    void output(string an) {levelOrder(root, an); return;}
    void level()  {cout<<height(root)<<endl;}
    void ascend()  {preOrder(root);}
private:
    treapNode *root;//ָ��binaryTreeNode<E>���͵�ָ�룬ָ������
    int treeSize;           //����Ԫ�ظ���
    //�����������ʽ��Ϊ˽�г�Ա
    static void levelOrder(treapNode *t, string an);
    //���ʽڵ㣬����ڵ�ؼ����Լ�������Ԫ�ظ���
    static void visit(treapNode *t){cout<<"( "<<t->element<<" , "<<t->priority<<" )"<<endl;}

    static void zag(treapNode* &t)
    {
        treapNode* tmp = t->rightChild;
        if(tmp == NULL)
            return;
        t->rightChild = tmp->leftChild;
        tmp->leftChild = t;
        t = tmp;
    }

    static void zig(treapNode* &t)
    {
        treapNode* tmp = t->leftChild;
        if(tmp == NULL)
            return;
        t->leftChild = tmp->rightChild;
        tmp->rightChild = t;
        t = tmp;
    }

    static int rand1 ( )  {
        static int seed = 233;
        return seed = ( int ) seed * 482711LL % 2147483647;
    }

    static int height(treapNode* t)
    {
        if(t == NULL)
            return 0;
        int hl = height(t->leftChild);
        int hr = height(t->rightChild);
        if(hl > hr)
            return ++hl;
        else
            return ++hr;
    }

    static void preOrder(treapNode* t)
    {
        if(t != NULL){
            visit(t);
            preOrder(t->leftChild);
            preOrder(t->rightChild);
        }
    }
};

//�������
void treapTree::levelOrder(treapNode *t, string an)
{
    fstream outfile("graph.gv", ios::out);
    outfile<<"graph G{"<<endl;
    outfile<<"node[shape=record];"<<endl;
    queue<treapNode*> q;
    if(t != NULL && t->leftChild == NULL && t->rightChild == NULL){
        stringstream ss;
        ss << t->element;
        string a = ss.str();
        ss.str("");
        ss << t->priority;
        string c = ss.str();
        ss.str("");
        string struct1 = a + "[shape=record,label=\"<f0> " + a + "|<f1> " + c + "\"];";
        outfile<<struct1<<endl;
        outfile<<"}"<<endl;
        outfile.close();
        string order = "dot -Tpng graph.gv -o " + an + ".png";
        const char *p = order.data();
        system(p);
        return;
    }
    while(t != NULL){
        if(t->leftChild != NULL){
            stringstream ss;
            ss << t->element;
            string a = ss.str();
            ss.str("");
            ss << t->priority;
            string c = ss.str();
            ss.str("");
            string struct1 = a + "[shape=record,label=\"<f0> " + a + "|<f1> " + c + "\"];";
            outfile<<struct1<<endl;
            ss << t->leftChild->element;
            string b = ss.str();
            ss << t->leftChild->priority;
            string d = ss.str();
            ss.str("");
            string struct2 = b + "[shape=record,label=\"<f0> " + b + "|<f1> " + d + "\"];";
            outfile<<struct2<<endl;
            string ed = a;
            ed += " -- ";
            ed += b;
            ed += " ; ";
            outfile<<ed <<endl;
        }
        if(t->rightChild != NULL){
            stringstream ss;
            ss << t->element;
            string a = ss.str();
            ss.str("");
            ss << t->priority;
            string c = ss.str();
            ss.str("");
            string struct1 = a + "[shape=record,label=\"<f0> " + a + "|<f1> " + c + "\"];";
            outfile<<struct1<<endl;;
            ss << t->rightChild->element;
            string b = ss.str();
            ss << t->rightChild->priority;
            string d = ss.str();
            ss.str("");
            string struct2 = b + "[shape=record,label=\"<f0> " + b + "|<f1> " + d + "\"];";
            outfile<<struct2<<endl;
            string ed = a;
            ed += " -- ";
            ed += b;
            ed += " ; ";
            outfile<<ed <<endl;
        }

        if(t->leftChild != NULL)
            q.push(t->leftChild);
        if(t->rightChild != NULL)
            q.push(t->rightChild);

        if(q.empty() ){
            outfile<<"}"<<endl;
            outfile.close();
            string order = "dot -Tpng graph.gv -o " + an + ".png";
            const char *p = order.data();
            system(p);
            return;
        }
        else{
            t = q.front();
            q.pop();
        }
    }
}

void treapTree::insert(treapNode* &now, int& theElement)
{
    if(now == NULL)
    {
        treeSize++;
        now = new treapNode (theElement, rand());
        return;
    }

    if(now->element < theElement)
    {
        insert(now->rightChild, theElement);
        if(now->rightChild->priority < now->priority)
            zag(now);
    }
    else if(now->element > theElement)
    {
        insert(now->leftChild, theElement);
        if(now->leftChild->priority < now->priority)
            zig(now);
    }
}

void treapTree::init(int* a, int n)
{
    srand((int)time(0));
    for(int i = 1; i <= n; i++)
        insert(root, a[i]);
}

void treapTree::erase(treapNode* &now, int& theElement)
{
    if(now == NULL)
        return;

    if(now->element == theElement){
        if(now->rightChild == NULL && now->leftChild == NULL){
            cout<<"find "<< theElement<<"_ɾ�������ɹ�"<<endl;
            now = NULL; return;
        }
        else if(now->rightChild == NULL && now->leftChild != NULL){
            now = now->leftChild;
            cout<<"find "<< theElement<<"_ɾ�������ɹ�"<<endl;
        }
        else if(now->leftChild == NULL && now->rightChild != NULL){
            cout<<"find "<< theElement<<"_ɾ�������ɹ�"<<endl;
            now = now->rightChild;
        }
        else{
            if(now->leftChild->priority < now->rightChild->priority){
                zig(now);
                erase(now->rightChild, theElement);
            }
            else{
                zag(now);
                erase(now->leftChild, theElement);
            }
        }
    }
    else if(now->element > theElement)
        erase(now->leftChild, theElement);
    else
        erase(now->rightChild, theElement);
}

#endif // TREAP_H_INCLUDED
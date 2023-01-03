#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;

//creating a stack using linked list
typedef struct node
{
    char data;
    node *next;
}node;

class stack
{
    node *top;
public:
    stack() //constructor to initialise top
    {
      top=NULL;
    }
    int isempty()
    {
        if(top==NULL)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    void push(int x)
    {
        node *p=new node();
        p->data=x;
        p->next=top;
        top=p;
    }
    int pop()
    {
        node *todelete=top;
        int x;
        x=todelete->data;
        top=top->next;
        delete todelete;
        return x;
    }
    int topValue()
    {
        return top->data;
    }
};

    stack st;
    int prefixEval(string s)
    {
      for(int i=s.length() -1;i>=0;i--)
      {
          if(s[i]>='0' && s[i]<='9')
          {
              st.push(s[i]-'0');
          }
          else
          {
              int op1=st.topValue();
              st.pop();
              int op2=st.topValue();
              st.pop();

              switch(s[i])
              {
                  case '+':
                  {
                      st.push(op1+op2);
                      break;
                  }
                  case '-':
                  {
                      st.push(op1-op2);
                      break;
                  }
                  case '*':
                  {
                      st.push(op1*op2);
                      break;
                  }
                  case '/':
                  {
                      st.push(op1/op2);
                      break;
                  }
                  case '^':
                  {
                      st.push(pow(op1,op2));
                      break;
                  }

              }
          }
      }
        return st.topValue();
    }

    int postfixEval(string s)
    {
        for(int i=0;i<s.length();i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                st.push(s[i] - '0');
            } else {
                int op2 = st.topValue();
                st.pop();
                int op1 = st.topValue();
                st.pop();
                switch (s[i]) {
                    case '+': {
                        st.push(op1 + op2);
                        break;
                    }
                    case '-': {
                        st.push(op1 - op2);
                        break;
                    }
                    case '*': {
                        st.push(op1 * op2);
                        break;
                    }
                    case '/': {
                        st.push(op1 / op2);
                        break;
                    }
                    case '^': {
                        st.push(pow(op1, op2));
                        break;
                    }
                }

            }
        }
            return st.topValue();
        }

        int prec(char c)
        {

           if(c=='+' || c=='-')
           {
               return 1;
           }
           else if(c=='*' || c=='/')
           {
               return 2;
           }
           else if(c=='^')
           {
               return 3;
           }
           else //which is if its a bracket
           return -1;
        }

        string infixtoPostfix(string s)
        {
        string result;
             for(int i=0;i<s.length() ; i++)
             {
                 if(s[i]>='a' && s[i]<='z' || s[i]>='A' && s[i]<='Z' )
                 {
                    result+=s[i];
                 }
                 else if(s[i] == '(')
                 {
                     st.push(s[i]);
                 }
                 else if(s[i] == ')')
                 {
                     while(st.isempty()!=1 && st.topValue()!='(' )
                     {
                         result+=st.topValue();
                         st.pop();
                     }
                     if(st.isempty()!=1)
                     {
                         st.pop();
                     }
                 }
                 else {
                     while (st.isempty() != 1 && prec(s[i]) < prec(st.topValue())) {
                         result += st.topValue();
                         st.pop();
                     }
                     st.push(s[i]);
                 }
             }
           while(st.isempty()!=1)
           {
               result+=st.topValue();
               st.pop();
           }
           return result;
        }

string infixtoPrefix(string s)
{
    reverse(begin(s),end(s));
    string result;
    for(int i=0;i<s.length() ; i++)
    {
        if(s[i]>='a' && s[i]<='z' || s[i]>='A' && s[i]<='Z' )
        {
            result+=s[i];
        }
        else if(s[i] == ')')
        {
            st.push(s[i]);
        }
        else if(s[i] == '(')
        {
            while(st.isempty()!=1 && st.topValue()!=')' )
            {
                result+=st.topValue();
                st.pop();
            }
            if(st.isempty()!=1)
            {
                st.pop();
            }
        }
        else {
            while (st.isempty() != 1 && prec(s[i]) < prec(st.topValue())) {
                result += st.topValue();
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while(st.isempty()!=1)
    {
        result+=st.topValue();
        st.pop();
    }
    reverse(begin(result),end(result));
    return result;
}
int main()
{
        int prefix_value=prefixEval("-+7*45+20");
        cout<<"Evaluated value of prefix expression "<<prefix_value<<endl;
        int postfix_value= postfixEval("46+2/5*7+");
        cout<<"Evaluated value of postfix expression "<<postfix_value<<endl;
    cout<<infixtoPostfix("(A+B)*(C+D)")<<endl;
    cout<<infixtoPrefix("(A+B)*(C+D)");
    return 0;
}

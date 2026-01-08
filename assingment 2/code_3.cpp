#include<iostream>
#include<cstring>
using namespace std;

struct node{
    float weight;
    char sender_name[50];
    char reciver_name[50];
    int priority;
    int id;
    node* next=NULL;

    node(int id,float weight,int priority,char sender[50],char reciver[50]){
        this -> id=id;
        this->weight=weight;
        this-> priority=priority;
        strncpy(this->sender_name,sender,50);
        strncpy(this->reciver_name,reciver,50);

    }

};
struct node_table{
    int id;
    node* adress;
    node_table* next=nullptr;
    node_table(int id,node*adress){
        this-> id=id;
        this-> adress=adress;
    }
};
class hash_table{
    private:
    node_table* table[10];
    public:
    hash_table(){
        for (int i = 0; i < 10; i++)
        {
            table[i]=nullptr;
        }
        
    }
    int hashfun(int id){
        int final_val=id;
        int temp1;
        int temp2;
        while(final_val/10 != 0){
            temp1=final_val%10;
            temp2=final_val/10;
            final_val=temp1+temp2;
        }
        return final_val;
    
    }
    ~hash_table(){
        for (int i = 0; i < 10; i++) {
            node_table* current = table[i];
            while (current != nullptr) {
                node_table* next = current->next;
                delete current;
                current = next;
            }
        }

    }
    void insert(int id,node*adress) {
        int index = hashfun(id);
        node_table* newNode = new node_table(id,adress);
        newNode->next = table[index];
        table[index] = newNode;
    }

    node* exists(int id) {
        int index = hashfun(id);
        node_table* current = table[index];
        while (current != nullptr) {
            if (current->id == id) return current->adress;
            current = current->next;
        }
        return nullptr;
    }

    bool delete_id(int id) {
        int index = hashfun(id);
        node_table* current = table[index];
        node_table* prev = nullptr;

        while (current != nullptr) {
            if (current->id == id) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }

                delete current;
                return true; 
            }

            prev = current;
            current = current->next;
        }

        return false; 
    }



};

class stack
{
    private:
        node*top=nullptr;
        hash_table id_container;

        node* node_input_taker_creater(){ // also does the function of adding id to our finde
            int id,prio;
            float weight;
            char reciver[50],sender[50];
            cout<<"enter id : "<<"\0";
            cin>> id ;
            cout<<"\nenter priority : "<<"\0";
            cin>> prio ;
            cout<<"\nenter weight : "<<"\0";
            cin>> weight ;
            cout<<"\nenter sender's name: "<<"\0";
            cin>> sender;
            cout<<"\nenter recivers name: "<<"\0";
            cin>> reciver;
            node* new_node=new node(id,weight,prio,sender,reciver) ;
            id_container.insert(id,new_node);
            return new_node;
        }
    public:
        ~stack();
        void add_parcel(){
            // cout<<"2"<<endl;
            node* new_node=node_input_taker_creater();
            node* temp=top;
            if (top==nullptr|| top->priority>=new_node->priority){
                top=new_node;
                new_node->next=temp;
                return;
            }

            while(temp->next != nullptr & temp->priority<new_node->priority){
                temp=temp->next;
            }
          new_node->next=temp->next;
          temp->next=new_node;
          return;
        }
        void dispatch_parcel(){
            if (top==nullptr)
            {
                cout<<"no parcel to dispatch"<<endl;
                return;
            }
            node*temp=top->next;
            top->next=nullptr;
            int id_to_delete=top->id;
            id_container.delete_id(id_to_delete);//deltetes fro hash table too
            display_all();
            top=temp;

            delete top;


        }
        void view_next(){
            node*temp=top;
            if (temp==nullptr){
                cout<<"no parcel to dispatch next"<<endl;
                return;
            }
            temp=top;


            cout <<"parcel ID : "<<temp->id<<endl;
            cout <<"parcel  Weight : "<<temp->weight<<endl;
            cout <<"parcel  Priority : "<<temp->priority<<endl;
            cout <<"parcel Sender's name : "<<temp->sender_name<<endl;
            cout <<"parcel Reciver's name : "<<temp->reciver_name<<endl;

        }
        void display_all(){
            node*temp=top;
            if (top==nullptr){
                cout<<"no parcel in the stack"<<endl;
                return;
            }

            while(temp !=nullptr){
                cout <<"parcel ID : "<<temp->id<<endl;
                cout <<"parcel  Weight : "<<temp->weight<<endl;
                cout <<"parcel  Priority : "<<temp->priority<<endl;
                cout <<"parcel Sender's name : "<<temp->sender_name<<endl;
                cout <<"parcel Reciver's name : "<<temp->reciver_name<<endl;
                cout<<endl;
                temp=temp->next;
            }
        }
        void count_by_priority(){
            int prio_1=0;
            int prio_2=0;
            int prio_3=0;
            node*temp=top;
            while(temp!= nullptr){
                if (temp->priority==1)
                {
                    prio_1+=1;
                }
                else if (temp->priority==2)
                {
                    prio_2+=1;
                }
                else
                {
                    prio_3+=1;
                }
                temp=temp->next  ; 
                     }
                cout << "priority 1 : "<<prio_1<<endl;
                cout << "priority 2 : "<<prio_2<<endl;
                cout << "priority 3 : "<<prio_3<<endl;

            }
        void exit(){
            cout<<"ending the program ...."<<endl;
            return;
        }
        void search_parcel(){
            int parcel_id;
            cout<<"Enter parcel id : "<<"\0";
            cin>>parcel_id;
            node*temp=id_container.exists(parcel_id);

            if (temp != nullptr){
                cout<<"parcel found ... "<<endl<<endl;
                cout <<"parcel ID : "<<temp->id<<endl;
                cout <<"parcel  Weight : "<<temp->weight<<endl;
                cout <<"parcel  Priority : "<<temp->priority<<endl;
                cout <<"parcel Sender's name : "<<temp->sender_name<<endl;
                cout <<"parcel Reciver's name : "<<temp->reciver_name<<endl;

            }else{

                cout<<"parcel NOT found "<<endl;
            }
            return;
        }

        
    };
    stack::~stack(){
        node*temp=top;
        while(temp!=nullptr){
            node*val=temp->next;
            delete temp;
            temp=val;
        }
    }


int main(){

    stack parcel_app;
    int input;
    while (input!=7)
    {   cout<<"\n";
        cout<<"starting the program"<<endl;
        cout<<"\n";
        
        cout<<"ADD PARCEL -> PRESS 1"<<endl;
        cout<<"DISPATCH PARCEL -> PRESS 2"<<endl;
        cout<<"VIEW NEXT -> PRESS 3"<<endl;
        cout<<"DISPLAY ALL -> PRESS 4"<<endl;
        cout<<"COUNT PARCEL BY PRIORITY -> PRESS 5"<<endl;
        cout<<"SEARH PARCEL-> PRESS 6"<<endl;
        cout<<"EXIT -> PRESS 7"<<endl;
        
        cout<<"\n";
        cout<<"enter input "<<"\0";
        cin>>input;
        cin.ignore();
        cout<<"\n";
        cout<<"processing your request ........."<<endl;
        cout<<"\n";

        if (input==1)
        {
           parcel_app.add_parcel();
        }     
        else if (input==2)
        {
            parcel_app.dispatch_parcel();
        }
        else if (input==3)
        {
            parcel_app.view_next();
        }
        else if (input==4)
        {
            parcel_app.display_all();
            
        }
        else if (input==5)
        {
            parcel_app.count_by_priority();
            
        }
        else if (input==6)
        {
            parcel_app.search_parcel();
            
        }
        
        else if (input==7){
        //    cout<<7<<endl;
            parcel_app.exit();
            break;
           
        }else{
            cout<<"please check the instruction "<<endl;
        }
        
    }
    
}



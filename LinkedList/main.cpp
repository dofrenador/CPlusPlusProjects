#include <iostream>
#include <string>

using namespace std;
struct Node //Declarion of a node
{
    string input;
    Node *next;
};
class LinkedList
{
public:
    LinkedList(); //prototypes
    ~LinkedList();
    void insert(int index,string input);
    void insertEnd(string input);
    void print();
    void deleteLine(int index);
    void searchLine(string input);
    void editLine(int index,string input);
    Node *getHead();
private:
    Node *head;
    bool contains(string str1, string str2);
};
Node*LinkedList :: getHead()
{
    return head;
}
bool LinkedList:: contains(string str1,string str2) // str1 is always > str2
{

    int len1 = str1.length(); // 11
    int len2 = str2.length(); //3

    if(len2 > len1)
    {
        return contains(str2,str1); // converse the arguments to make str1> str2
    }
    for(int i = 0; i <= len1-len2; i++)
    {
        string str = str1.substr(i,len2);
        if(str == str2)
        {
            return true;
        }
    }
    return false;
}

LinkedList::LinkedList() //Constructor
{
    this->head = NULL;
}
LinkedList::~LinkedList() {//Destructor

    Node *current = head;
    while( current != NULL ) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
    /*Node *prev = current;
    while(current != NULL)
    {
        prev = current;
        current = current->next;
        prev->next = NULL;
        delete prev;
    }*/
    //cout << "List deleted" << endl;
}

void LinkedList:: insert(int index,string input)
{
    input = input.substr(1,input.length()-2);
    Node *newNode = new Node();
    newNode->input = input;
    newNode->next = NULL;

    if ( head == NULL ) { // if the list is empty
        head = newNode;
        return;
    }
    if ( index == 1 ) { //make the node head
        newNode->next = head;
        head = newNode;
        return;
    }
    Node *current = head;
    Node *previous = NULL;

    int counter = 1;
    while (current != NULL && counter < index) {
        previous = current;
        current = current->next;
        counter++;
    }
    if(index > counter) // check conditions
        return;
    newNode->next = previous->next; // iterate
    previous->next = newNode;
}
void LinkedList::insertEnd(string input)
{
    input = input.substr(1,input.length()-2); //DENEME
    Node *temp = new Node();
    temp->input = input;
    temp->next = NULL;
    if(head == NULL) // if the head is empty
    {
        head = temp;
    }
    else
    {
        Node *current = head;
        while(current->next !=NULL)
        {
            current = current ->next;
        }
        current->next = temp;
    }
}
void LinkedList::deleteLine(int index)
{
    Node *current = head;
    Node *prev = current;
    if(index == 1) // keep track of the head !
    {
        head = current->next;
        return;
    }
    for(int i = 1; i < index; i++) {
        prev = current;
        if ( current->next == NULL )
            return;
        else
            current = current->next;
    }
    prev->next = current->next;

}
void LinkedList::editLine(int index,string input)
{
    input = input.substr(1,input.length()-2);
    Node *current = head;
    if(head == NULL)
    {
        //cout << "The list does not contain any previous data\n";
        return;
    } else
    {

        int lineCounter = 1;
        while (current != NULL)
        {
            if ( index == lineCounter )
            {
                current->input = input;
            }
            lineCounter++;
            current = current->next;
        }
    }
}
void LinkedList:: searchLine(string input)
{
    input = input.substr(1,input.length()-2);
    Node *current = head;
    int counter = 1;
    bool found = false;
    if(current == NULL)
    {
        cout << "The list is empty\n";
    }
    while(current != NULL)
    {
        string data = current->input;
        if (contains(data, input))
        {
            cout <<counter<<" " << data << endl;
            found = true;
        }
        counter++;
        current = current->next;
    }
    if(!found)
        cout << "not found\n";
}
void LinkedList::print()
{
    int index = 1;
    Node * current = head;
    if(current == NULL)
    {
        //cout <<"The list is empty!";
        return;
    }
    while(current != NULL)
    {
        cout <<index << " " << current->input << "\n";
        current = current->next;
        index++;
    }
}

int main() {

    LinkedList *list = new LinkedList();
    string keyword,input;
    int num;
    bool quitRequest = false;
    while(!quitRequest && input.length() < 80)
    {

        cin >> keyword;
        if(keyword == "insertEnd")
        {
            cin.ignore(100,' ');
            getline(cin,input);
            list->insertEnd(input);
        }
        else if(keyword == "insert")
        {
            cin >> num;
            cin.ignore(100,' ');
            getline(cin,input);
            list->insert(num,input);
        }
        else if(keyword == "delete")
        {
            cin >> num;
            list->deleteLine(num);
        }
        else if(keyword == "edit")
        {
            cin >> num;
            cin.ignore(100,' ');
            getline(cin,input);
            list->editLine(num,input);
        }
        else if(keyword == "print")
        {
            list->print();
        }
        else if(keyword == "search")
        {
            cin.ignore(100,' ');
            getline(cin,input);
            list->searchLine(input);
        }
        else if(keyword == "quit")
        {
            delete list;
            quitRequest = true;
        }
    }
    return 0;
}






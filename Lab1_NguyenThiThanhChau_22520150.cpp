//Lab 1
//NguyenThiThanhChau- 22520150
#include <iostream>
#include <cstdlib>  
#include <ctime>
using namespace std;

class Node {
public:
    Node* next;
    int data;
    Node*random;
    Node(int value) : data(value), next(nullptr), random(nullptr) {}
};

class SingleLinkedList {
public:
    Node* head;
    SingleLinkedList() : head(nullptr) {}

    void addNode(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() {
        if (head == nullptr) {
            cout << "error";
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int getLength() {
        int length = 0;
        Node* temp = head;
        while (temp) {
            length++;
            temp = temp->next;
        }
        return length;
    }
 SingleLinkedList addTwoNumbers(SingleLinkedList& list1, SingleLinkedList& list2) {
      //Reverse 2 list to plus from head to tail Đ
    Node* prev1 = nullptr; // Initialize a pointer storing the previos values
    Node* curr1 = list1.head;//// Initialize a pointer reading from head to tail list
    while (curr1) {  
        Node* next = curr1->next; 
        curr1->next = prev1; // let next node = previous node
        prev1 = curr1;// set node behind curr will be current
        curr1 = next;// and curr will be the next
    }
    list1.head = prev1;// the last node is updated to the head

    Node* prev2 = nullptr;//same
    Node* curr2 = list2.head;
    while (curr2) {
        Node* next = curr2->next;
        curr2->next = prev2;
        prev2 = curr2;
        curr2 = next;
    }
    list2.head = prev2;

    // Plus 2 reversed lists
    Node* cur1 = list1.head;
    Node* cur2 = list2.head;
    SingleLinkedList result;//constructer a signle link list
    int carry = 0;// for example 9+3 = 12 remembering 1

    while (cur1 != nullptr || cur2 != nullptr || carry != 0) {
        // if one of 2 nodes is null let 0 value
        int x = (cur1 != nullptr) ? cur1->data : 0;
        int y = (cur2 != nullptr) ? cur2->data : 0;

        int sum = carry + x + y;
        result.addNode(sum % 10);// take the lasst digit of phần dư into result list.
        carry = sum / 10; //update carry for the next calculation

        if (cur1 != nullptr) cur1 = cur1->next;
        if (cur2 != nullptr) cur2 = cur2->next;
    }

    // Reverse list to print correctly the order of list 
    Node* prevResult = nullptr;
    Node* currResult = result.head;
    while (currResult) {
        Node* next = currResult->next;
        currResult->next = prevResult;
        prevResult = currResult;
        currResult = next;
    }
    result.head = prevResult;

    return result;
}

  SingleLinkedList copyList(){
  	SingleLinkedList newList;//neww list  to hold the copied nodes
  	Node* curr =head;
 
  //Create copies of nodes and interleave them with original node
   	while(curr!=nullptr){
  		Node*copy= new Node(curr->data);
  		copy->next=curr->next;
  		curr->next=copy;
  		curr=copy->next;
	  }
	  //// Reset current to head
	  curr=head;
	  
	   // Assign random pointers to the copied nodes
	  while(curr!=nullptr){
	  	Node*copy =curr->next;
	  	if(curr->random!=nullptr){
	  		copy->random=curr->random->next;// Link random pointer to the copied node
	  	
		  }
		else{
			copy->random=nullptr;// Move to the next original node
		}	
		curr=copy->next;
	  }
	  // Separate the copied nodes from the original list
	  curr = head;// Reset current to head
        Node* newHead = nullptr;// Head for the new list
        Node* newTail = nullptr;//Tail for the new list
        while (curr != nullptr) {
            Node* copy = curr->next;// Get the copy node
            curr->next = copy->next;// Restore the original list's next pointer
            if (newHead == nullptr) {
                newHead = copy;// Set the new head if it's the first copy
                newTail = newHead;// Set the tail
            } else {
                newTail->next = copy;// Link the copy to the new list
                newTail = newTail->next;
            }
            curr = curr->next;
        }

        newList.head = newHead;
        return newList;
	  
}

   void printListWithRandomPointers() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "Data: " << temp->data;
            if (temp->random != nullptr) {
                cout << ", Random: " << temp->random->data;
            } else {
                cout << ", Random: NULL";
            }
            cout << endl;
            temp = temp->next;
        }
    }
    
 void swapNodes(int a, int b) {
        if (a == b) return;

        Node *preva = nullptr, *curra = head;
        //find the node a
        while (curra && curra->data != a) {// run untill reaching a
            preva = curra;
            curra = curra->next;
        }
        
       //find the node b
        Node *prevb = nullptr, *currb = head;
        while (currb && currb->data != b) {
            prevb = currb;
            currb = currb->next;
        }

        if (!curra || !currb) return;//a and b is not found => return

        if (preva) {//if a not nulll
            preva->next = currb; //let node a =b
        } else {
            head = currb; // If `b` is the head, update the head to point to `a`
        }

        if (prevb) {
            prevb->next = curra;//let b  =a
        } else {
            head = curra; // If `b` is the head, update the head to point to `a`
        }

Node* temp = currb->next; // Store next of 'b'
currb->next = curra->next; // Point 'b' to the next of 'a'
curra->next = temp; // Point 'a' to the next of 'b'
    }
    //giống biến tempt trong đổi vj trí hai phần tử bthg
    
    
    void removeNthFromEnd(int n) {
    Node* first = head;// Pointer to traverse the list
    Node* second = head;//// Pointer to find the node before the one to be removed

// if first tranverse to the end (n) and first == null. That mean n is out of the range. Ex delete node 4th but list has 2 3  so first tranverse from 2th to 3th =null => not available
    for (int i = 0; i < n; ++i) {
        if (first == nullptr) return;  
        first = first->next;// node first được cập nhật là thằng phía sau mà phía sau chính là n và cũng chính là thằng cần được xóa
    }

    if (first == nullptr) {// this first was updated after get rid ôf the for loop
        Node* temp = head;//Nếu sau khi di chuyển n lần mà first là nullptr, điều này có nghĩa là danh sách có ít hơn n nút, tức là cần xóa nút đầu tiên.
        head = head->next;
        delete temp;
        return;
    }


    while (first->next != nullptr) {
        first = first->next;// di chuyển first tại vị trí n xuống cuối danh sách
        second = second->next;// từ đầu tới vị trí cần xoá
    }// ý là khoảng cách từ first tới n = khoảng cách từ second tới node cần xóa

    Node* temp = second->next;// Second đã di chuyển tới vị trí cần xóa thì xóa
    second->next = temp->next;
    delete temp;
}


  void SeparateList(SingleLinkedList& list1, SingleLinkedList& list2) {
        SingleLinkedList oddList;
        SingleLinkedList evenList;
        Node* p = list1.head;//// Con trỏ p để duyệt qua list1
        Node* q = list2.head;// Con trỏ p để duyệt qua list2

        while (p != nullptr) {// xét duyệt danh sách 1
            if (p->data % 2 == 1) {//  nếu lẻ thì add vào danh sách lẻ
                oddList.addNode(p->data);
            } else {
                evenList.addNode(p->data);// còn lại thêm vào chẵn
            } 
            p = p->next;
        }

        while (q != nullptr) {// xét duyệt danh sách 2
            if (q->data % 2 == 1) {
                oddList.addNode(q->data);
            } else {
                evenList.addNode(q->data);
            }
            q = q->next;
        }

        cout << "Odd list:" << endl;
        oddList.display();// in danh sách lẻ

        cout << "Even list:" << endl;
        evenList.display();// in danh hách chẵn
    }
    
	void  dividedList(int n){// the number of parts that you want to divided
	int length = getLength();// check length of the list
	int partSize =length/n; // kích thước phần tử cơ bản của mỗi phần
	int extraSize=length%n;// số  phần tử dư ra 
		Node* curr =head;
		for(int i = 0 ; i < n;i++)
		{
			int currentSize=partSize;// cho kích thước hiện tại bằng số phần tử trung bình trong mỗi hàng
			
			if(extraSize>0){
				currentSize = partSize + 1;//thêm phân tử dư vào hàng đầu
				extraSize--;
			}
			// in ra số phần tử cần in trong một hàng
			for(int j = 0 ; j < currentSize; j++){
				if(curr!=nullptr){
					cout<<curr->data<<" ";
					curr=curr->next;
				}
			}
			cout<<endl;// mỗi lần làm xong xuống hàng để tính hàng tiếp theo
		}
	}
void removeZeroSum() 
{Node *mamamia = new Node(0);  // Tạo một node giả có giá trị 0.
    mamamia->next = head;  // Liên kết node giả với head.
    Node *curr = mamamia;  // Con trỏ `curr` bắt đầu từ node giả.

    // Duyệt qua từng node trong danh sách.
    while (curr != nullptr) {
        Node *runner = curr->next;  // Con trỏ `runner` để kiểm tra từ node tiếp theo.
        int sum = 0;  // Biến sum dùng để tính tổng các giá trị từ `curr` đến `runner`.

        // Duyệt qua các node tiếp theo để kiểm tra tổng.
        while (runner != nullptr) {
            sum += runner->data;  // Cộng giá trị của node `runner` vào tổng.

            if (sum == 0) {  // Nếu tổng bằng 0, xóa đoạn này.
                Node *temp = curr->next;
                while (temp != runner) {
                    Node *nodeToDelete = temp;
                    temp = temp->next;
                    delete nodeToDelete;  // Xóa từng node trong đoạn có tổng bằng 0.
                }

                // Liên kết node hiện tại với node sau đoạn đã xóa.
                curr->next = runner->next;
                break;  // Thoát khỏi vòng lặp vì đoạn đã được xóa.
            }

            runner = runner->next;  // Tiếp tục kiểm tra node tiếp theo.
        }

        // Nếu không có đoạn có tổng bằng 0, di chuyển con trỏ `curr`.
        if (runner == nullptr || sum != 0) {
            curr = curr->next;
        }
    }

    // Cập nhật lại head của danh sách.
    head = mamamia->next;
    delete mamamia;  // Xóa node giả.
}
void automaticInput() {
        srand(time(nullptr));   // Khởi tạo bộ sinh số ngẫu nhiên 

        int numEntries = rand() % 21 + 39;  
        cout << "Number of Entries: " << numEntries << endl;

        for (int i = 0; i < numEntries; ++i) {
            int value = rand() % 199 - 99;  // tạo  bộ nhớ ngẫu nhiên chạy từ  99 tới 199 là công thức random theo khoảng
            addNode(value);
        }
    }



};

int main() {
    SingleLinkedList list1,list2,result;
    SingleLinkedList oddList,evenList;	
    Node* mergedList = nullptr;
    int choice;
    while (true) {
        cout << "=====MENU=====\n";
        cout << "1. Add Two Numbers\n";
        cout << "2. Copy List With Random Pointers\n";
        cout << "3. Swap Nodes in a Linked List\n";
        cout << "4. Remove the N-th Node from the End of a List\n";
        cout << "5. Separate Odd and Even Nodes in a Linked List Medium\n";
        cout << "6. Divide a Linked List into Parts\n";
        cout << "7. Remove Zero-Sum Consecutive Nodes from a Linked List\n";
        cout << "8. Write a function to input values for a list using the automatic input method, with values selected from the range [-99; 99].\n";
        cout << "9. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
            	   cout << "Enter the first linked list (end with -1):" << endl;
    		while (true) {
	        int x;
	        cin >> x;
	        if (x == -1) break;
	        list1.addNode(x);
		}
		
		    cout << "Enter the second linked list (end with -1):" << endl;
		    while (true) {
		        int x;
		        cin >> x;
		        if (x == -1) break;
		        list2.addNode(x);
		 }
            result = result.addTwoNumbers(list1, list2);
            cout << "Result after adding two numbers: ";
            result.display();
                break;
            case 2:{
            	  cout << "Enter the first linked list (end with -1):" << endl;
    		while (true) {
	        int x;
	        cin >> x;
	        if (x == -1) break;
	        list1.addNode(x);
		}// xet random pointer 
			list1.head->random = list1.head->next->next; 
			list1.head->next->random = list1.head;      
   			list1.head->next->next->random = list1.head->next; 
                 cout << "Copying list with random pointers..." << endl;
                SingleLinkedList copiedList = list1.copyList();
                cout << "Original list with random pointers:" << endl;
                list1.printListWithRandomPointers();
                cout << "Copied list with random pointers:" << endl;
                copiedList.printListWithRandomPointers();
                break;
        }
            case 3: {
            	cout << "Enter the first linked list (end with -1):" << endl;
		    	while (true) {
			    int a;
			    cin >> a;
			    if (a == -1) break;
			    list1.addNode(a);
			}
	            int x, y;
    			cout << "Enter the values of the nodes to swap:" << endl;
   				cin >> x >> y;
   				list1.swapNodes(x, y);
    			cout << "List after swapping nodes " << x << " and " << y << ":" << endl;
   				list1.display();
    
	        	break;
            }
            case 4:
			{
			cout << "Enter the linked list (end with -1):" << endl;
		    while (true) {
		        int x;
		        cin >> x;
		        if (x == -1) break;
		        list1.addNode(x);
		    }
		
		    int n;
		    cout << "Enter the position from the end to remove:" << endl;
		    cin >> n;
		
		    list1.removeNthFromEnd(n);
		    cout << "List after removing the " << n << "-th node from the end:" << endl;
		    list1.display();

                break;
            }
            case 5: {
                  cout << "Enter the first linked list (end with -1):" << endl;
                while (true) {
                    int x;
                    cin >> x;
                    if (x == -1) break;
                    list1.addNode(x);
                }

                cout << "Enter the second linked list (end with -1):" << endl;
                while (true) {
                    int x;
                    cin >> x;
                    if (x == -1) break;
                    list2.addNode(x);
                }

                list1.SeparateList(list1, list2);
                
                
                
               break;
            }
            case 6:
               {
               	  cout << "Enter the first linked list (end with -1):" << endl;
                while (true) {
                    int x;
                    cin >> x;
                    if (x == -1) break;
                    list1.addNode(x);
                }
                cout<<"enter how many part you want:";
                int k ; cin>>k;
                list1.dividedList(k);
               	
               	break;
			   }
				
            case 7:
               {
               	cout << "Enter the linked list (end with -1):" << endl;
    while (true) {
        int x;
        cin >> x;
        if (x == -1) break;
        list1.addNode(x);
    }

    cout << "Removing zero-sum consecutive nodes from the list..." << endl;
    list1.removeZeroSum();
    cout << "List after removing zero-sum consecutive nodes: ";
    list1.display();
			   
                break;
            }
            case 8: {
                
                SingleLinkedList list;

		    list.automaticInput();
		
		    // Hi?n th? danh sách
		    cout << "Generated list with random values:" << endl;
		    list.display();
                break;
            }
            case 9:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}



#include<iostream>
using namespace std;
class Node{
	public:
		//storing the  data
		int data;
		//kids
		Node *left;
		Node *right;
		Node *parent;
		Node(int value){
			data = value;
			left = NULL;
			right = NULL;
			parent = NULL;	
	}
};
class BiST{
	public:
		Node *root;
		BiST(){
			root = NULL;
		}
		void insert(int value){
			insertHelper(root,value);
		}
		void insertHelper(Node * current, int value){
			//Base case 
			if(current == NULL){
				current = new Node(value); 
				if (root == NULL) root = current;	
				return;
			}
			 
			
			//Else ,  comparing the current data with value
			else if(value <  current->data){
				//If the value is less than current data, then move left and call insert
				//if left is NULL,insert it.
		
				if(current->left == NULL)	{
					current->left = new Node(value);
					current->left->parent = current;
				}
				//else, then  move to the left and call insert.
				else insertHelper(current->left , value);
			}
			else{
				//move right and call insert
				
				if (current->right == NULL) {
					current->right = new Node(value);
					current->right->parent = current;
				}
				else insertHelper(current->right,value);
			}			
		}
		//displaying	
		void display(){
			display2(root);
			cout<<endl;
		}
		
		void display2(Node *current){
			//Base condition
			if (current == NULL) return;
			//Display left kid
			display2(current->left);
			//display current
			cout<<current->data<<" , ";
			//display right kid
			display2(current->right);
		}
		//searching the node with the given value
		Node * search1(Node * current,int value){
			//if not present or present return current
			if (current == NULL || current->data == value) return current;
			//searching left and right node
			else if(value<current->data){
				return search1(current->left,value);
			}
			else return search1(current->right,value);
		}
		// find if an element exists or not.
		bool search(int value){
			//if found , print so.
			if(search1(root,value)!=NULL) {
				cout<<"found"<<endl;
				return 1;
			}
			//if not then, print. 
			else {
				cout<<"Not found"<<endl;return 0;	
			}
		}
		//find minimum.
		int find_min(int value){
			//search for a branch
				Node *current = search1(root,value);
			//take the minimum of that branch
			    Node *min = find_min1(current);
			    cout<<endl;
			    return min->data;
		}
		Node *find_min1(Node *current){
			//find minimum recursion
			if(current->left == NULL ){
				return current;	
			}
			else if(current == NULL){
			    return NULL;
			}
			//recursion carried to left
			else return find_min1(current->left);
		}
		

		
		
		
		//int height();
		void deleteNode(int value){
			//search deleting node
			Node *current = search1(root,value);
			if(current == NULL){
			    return;
			}
			else{
				//replacing the values
			    if(current->left == NULL){ 
				    replace_at_parent1(current->right,current);
			    }
    			else if(current->right == NULL){ 
    				replace_at_parent1(current->left,current);
    			}
    			else{ 
    			    Node *temp = find_min1(current->right);
    			    if(current == root){
    	                current->data = temp->data;
    	                replace_at_parent1(NULL,temp);
    				    delete temp;
    			    }
    			    else{
    				    replace_at_parent1(temp,current);
    				    temp->parent = current->parent;
    				    temp->left = current->left;
    				    delete temp;
    			    }
    			}
			}
			
		}
		
		void replace_at_parent(int value1,int value2){
			Node *rep = search1(root,value2);
			Node *current = search1(root,value1);
			replace_at_parent1(current,rep);
		}
		void replace_at_parent1(Node *current,Node *rep){
			if(rep == root){
				root = current;	
			}
			else if(current == root){
				return;
			}
			else{
				if(rep->data > rep->parent->data){
				    if(current == NULL){
			            rep->parent->right = NULL;
			        }
			        else{
			            rep->parent->right = current;
    					if(current->data > current->parent->data){
    						current->parent->right = NULL;
    					}
    					else current->parent->left = NULL;
    					current->parent = rep->parent;
			        }
					
				}
				else{
				    if(current == NULL){
			            rep->parent->left = NULL;
			        }
			        else{
			     	rep->parent->left = current;
					if(current->data>current->parent->data){
						current->parent->right = NULL;
					}
					else current->parent->left = NULL;
					current->parent = rep->parent;       
			        }
				
				}
			}
			print2DUtil(root,0);
		}     
		void print2DUtil(Node *root, int space){
			// Base case  
			if (root == NULL)  
			    return;  
			// Increase distance between levels  
			space += 5;  
			// Process right child first  
			print2DUtil(root->right, space);  

			// Print current node after space  
			// count  
			cout<<endl;  
			for (int i = 5; i < space; i++)  
			    	cout<<" ";  
				cout<<root->data<<"\n";  

			// Process left child  
			print2DUtil(root->left, space);  
			}  

			// Wrapper over print2DUtil()  
			void print2D(){  
                cout << "******************************" << endl;
                // Pass initial space count as 0  
                print2DUtil(root, 0);  
                cout << "******************************" << endl;
             }
		//void Range_search(k,l);
	
};
int main(){
	BiST t1;
	int k,n,x,min,rep,curr,dlt;
	cout<<"How many elemens do you need?"; cin>>n; cout<<endl;
	cout<<"Enter the elements"<<endl;
	for(int i = 0; i < n ; i++){
		cin>>k;	
		t1.insert(k);	
	}
	t1.print2D();
	cout<<"Type the element which you want to search ";
	cin>>x;cout<<endl;
	t1.search(x);
	cout<<"Find the minimum of :";
	cin>>min;cout<<endl;
	cout<<t1.find_min(min)<<endl;
	cout<<"Which element do you want to replace :";
	cin>>rep;cout<<endl;
	cout<<"With what element do you want to replace :";
	cin>>curr;cout<<endl;
	t1.replace_at_parent(curr,rep);
	cout<<"Which element do you want to delete :";
	cin>>dlt;cout<<endl;
	t1.deleteNode(dlt);
}

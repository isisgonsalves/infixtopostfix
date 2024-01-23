#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

#define MAXLEN 100

struct Stack {

        float element[MAXLEN];
      	int top;

};


Stack * initStack () {

      Stack * s;

      s = (Stack *) malloc (sizeof (Stack));
      s->top = -1;

      return s;
}


bool isEmpty ( Stack * s ) {
      return (s->top == -1);
}


bool isFull ( Stack * s ) {
      return (s -> top == MAXLEN - 1);
}


void push ( Stack * s , float n ) {
      if (isFull(s)) {
         cout << "Stack is full." << endl;
         return;
      }
      s->top = s->top + 1;
      s->element[s->top] = n;
}


float pop ( Stack * s ) {
      float n;

      if (isEmpty(s)) {
         cout << "Stack is empty." << endl;
      }
      n = s->element[s->top];
      s->top = s->top - 1;

      return n;
}


int operatorCheck (char sym){
	
	//Check if its an operator
	
	if(sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym =='^')
		return 1;
	else
		return 0;
}


int priorityCheck ( char sym ){
	
	//to check priority of the operators
	
    if(sym == '+' || sym =='-'){
        return(1);
    }
 
    if(sym == '*' || sym =='/'){
        return(2);
    }
    
    if(sym == '^'){
        return(3);
    }
 
    return -1;
}


void toCString (string s, char c[]) {

	int a;
	int length = s.length();
	
	for (int i=0; i<length; i=i+1) 
		c[i] = s[i];
	
	c[length] = '\0';
	
}


bool isValid (char infix[]){

// function to check unbalanced parentheses

Stack * check ; 
check = initStack();
int i=0;
	
	while(infix[i] != '\0'){
		
		if(infix[i] == '('){
			push(check, infix[i]);
		}
		if(infix[i] == ')'){
			if (check->element[check->top] == '(')
					pop(check);
			else
				return false; 
		}
	i++;
	}
		if (isEmpty(check)==false)
			return false;
		else
			return true;
}


float evaluate (char postFix[], Stack * result){
	
	//evaluates the postfix expression
	
	int i=0;
	char operation; 
	float val1=0.0;
	float val2=0.0;
	float valResult=0.0;
	
	while (postFix[i] != '\0'){
		
		//cout<<postFix[i]<<endl;
		
		if(postFix [i] >='0' && postFix[i]<='9'){ //if element at i is a digit, push onto stack
	        	   
	        	push(result, postFix[i] - '0'); 
	    }      
      	else{
      		
      		// else ... element at i is an operator
		    // so pop the 2 elements at top then check each and perform the specified operation 
		    //push the result onto the result stack.
      		
      		val2= pop(result);
      		val1= pop(result);
      		operation = postFix[i];
      		
      		if(operation == '+'){
      			//valResult = val1 + val2;
      			//cout<<"RES: "<<valResult<<endl;
      			push(result, val1 + val2);
			}
			else 	
				if(operation == '-'){
	      			//valResult = val1 - val2;
	      			//cout<<"RES: "<<valResult<<endl;
	      			push(result, val1 - val2);
			 	 }
			 	 else 	
					if(operation == '*'){
		      			//valResult = (val1 * val2);	
		      			//cout<<"RES: "<<valResult<<endl;
		      			push(result, val1 * val2);
				 	 }
				 	 else 	
						if(operation == '/'){
			      			//valResult = val1 / val2;
			      			//cout<<"RES: "<<valResult<<endl;
			      			push(result, val1 / val2);
					 	 }
					 	 else 	
							if(operation == '^'){
//				      			valResult = pow(val1, val2);
//				      			cout<<"RES: "<<valResult<<endl;
				      			push(result, pow(val1, val2));
						 	 }
		  } 
	i++;
 	}//end of while loop
 	
 	//last element in stack is the final answer, so pop it and retturn popped value
 	
	float popVal= pop(result); 
	
	return popVal;
}


void * toPostFix (char infix [], Stack * result, ofstream &out){
    
	int i=0;
	int c=0;
	char popVal;
	
	Stack * postFix; 
	postFix = initStack();
	
	//check if the infix string is valid first, if it isnt go to error message...
	
	if(isValid(infix)){ 
	
	 	char postFixstr [MAXLEN];	//intialize the string after each expression
		  
		    while(infix[i]!='\0'){ 
			
		    	if(infix[i] == '('){
		    		
					push(postFix, infix[i]);
					
				} 
		    	else
		    		if(infix[i]== ')' ){
								 
						 while(postFix->element[postFix->top] != '('){
						 	
						 	//add top to the postfix string and pop until ( is reached...
						 	
						 	postFixstr[c]= postFix->element[postFix->top]; 
						 	c++;
						 	pop(postFix);
						 	
						 }
						 
						 if(postFix->element[postFix->top] == '('){
						 	
						 	postFixstr[c]= postFix->element[postFix->top];
						 	pop(postFix);
						 	
						 }
			        }
			        else
						if(operatorCheck(infix[i])==1){
							
							//if the element at i is an operator...
					  	
						  		while (!isEmpty(postFix) && priorityCheck(postFix->element[postFix->top]) >= priorityCheck(infix[i])){
						  			
						  			//and stack is not empty and the priority of the element has a lower priority than the element at top...add it to string and pop the stack.
						  			
						  			postFixstr[c]= postFix->element[postFix->top];
						  			c++;
						  			pop(postFix);
						  			
								  }
								  
							 	  push(postFix, infix[i]);
						  }
						  else  
						  
					        if(infix[i]>='0' && infix[i]<='9'){
					        	
					        	//if element at i is a digit, add to string
					        	
					        	   postFixstr[c]= infix[i];
						           c++;
						           
					        }      
					i++;
					
				}//end while loop
				
					while(!isEmpty(postFix)){ //if elements still in stack, add to postfix string nd pop stack.
					
						postFixstr[c]= postFix->element[postFix->top];
						pop(postFix);
						c++;
						
					}
					
			
			int a=0;
			
			cout<<"Postfix Expression: ";
			
			out<<"Postfix Expression: ";
			
			while ( postFixstr[a]!= '\0'){
				
				cout<< postFixstr[a]; //it will print postfix conversion 
				
				out<< postFixstr[a]; //it will print postfix conversion 
				
				a++;
			}
			
			cout<<endl;
			
			out<<endl;
			
			float final = evaluate(postFixstr, result); //calling the evaluation function
			
			cout<<"Postfix Evaluation: "<< final <<endl<<endl; 
			
			out<<"Postfix Evaluation: "<< final <<endl<<endl; 
	}
	else{
	
		cout<<"This is an invalid Infix Expression. Unable to convert..." <<endl<<endl; //it will print the error message
		
		out<<"This is an invalid Infix Expression. Unable to convert..." <<endl<<endl; //it will print the error message
	}	
}


int main() {
	
	ifstream in; //declare input file
	ofstream out; //declare output file 
	

	Stack * result;
	result = initStack();
            
	string line; 
	
	char inFix[MAXLEN];	
	char postFixstr[MAXLEN];  
    
    in.open("input.txt");
	out.open("output.txt");
	
	
	if (!in.is_open()) {
		cout << "\nERROR: File cannot be found...Try again\n";
		return 0;
	}
	
	inFix={20/2-(5+12-2)};
	
	toPostFix(inFix,result, out);
	
//	cout<<"\t\t\t\t---------------------------------------------------\n";
//	cout<<"\t\t\t\tCOMP 1603 ASSIGNMENT 3: Infix, Postfix & Evaluation\n";
//	cout<<"\t\t\t\t---------------------------------------------------\n\n\n";
//	
//	out<<"\t\t\t\t---------------------------------------------------\n";
//	out<<"\t\t\t\tCOMP 1603 ASSIGNMENT 3: Infix, Postfix & Evaluation\n";
//	out<<"\t\t\t\t---------------------------------------------------\n\n\n";

//	getline (in, line);
//	
//		while (line != "$"){
//	
//			cout<<"Infix Expression  : "<<line<<endl;
//			
//			out<<"Infix Expression  : "<<line<<endl;
//			
//			toCString(line, inFix); //converted string to cstring 
//			
//			toPostFix(inFix,result, out); //to covert infix expression to postfix expression
//			
//			getline (in, line);
//		
//		}
	
    return 0;

}


#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Notepad {
  vector<string>allContent;
  stack<vector<string>> undoStack;
  stack<vector<string>> redoStack;
 
public:
    vector<string>copyText;
    Notepad(string text){
        allContent=split(text,'\n');
    }
     
    vector<string>split(string text,char delim){
       vector<string> ans;
        string line = "";
        
        for(auto it : text){
            if(it == delim){
                ans.push_back(line);
                line = "";
            } else {
                line += it;
            }
        }
        if (!line.empty()) {
            ans.push_back(line); // Add the last line if not empty
        }
        return ans;
     }
  void display(){
      if(allContent.size()==0){
          cout<<"No Content to display!";
          return;
      }
      for(auto it :allContent){
          cout<<it<<" ";
      }
  }
 void display(int start, int end){
      if(static_cast<size_t>(start)>allContent.size()){
          cout<<"The value start exceeds the number of lines";
          return;
      }
        if(static_cast<size_t>(end)>allContent.size()){
          cout<<"The value End exceeds the number of lines";
          return;
      }
      
      if(start>end){
          cout<<" Invalid start and end Entered!";
          return;
      }
      
      for(auto it=allContent.begin()+start-1;it!=allContent.begin()+end;it++){
          cout<<*it<<endl;
      }
  }
  void insert(int pos, string text){
       if(static_cast<size_t>(pos)>allContent.size()){
          cout<<"The value Position exceeds the number of lines";
          return;
      }
      undoStack.push(allContent);
      allContent.insert(allContent.begin()+pos,text);
  };
  void deleteText(int pos){
       if(static_cast<size_t>(pos)>allContent.size()){
          cout<<"The value Position exceeds the number of lines";
          return;
      }
       undoStack.push(allContent);
      allContent.erase(allContent.begin()+pos);
  }
  void deleteText(int start, int end){
    if(static_cast<size_t>(start)>allContent.size()){
          cout<<"The value start exceeds the number of lines";
          return;
      }
        if(static_cast<size_t>(end)>allContent.size()){
          cout<<"The value End exceeds the number of lines";
          return;
      }
      
      if(start>end){
          cout<<" Invalid start and end Entered!";
          return;
      }
       undoStack.push(allContent);
      for(auto it=allContent.begin()+start-1;it!=allContent.begin()+end;it++){
         allContent.erase(it);
      }
  }
  void copy(int start, int end){
      if(static_cast<size_t>(start)>allContent.size()){
          cout<<"The value start exceeds the number of lines";
          return;
      }
        if(static_cast<size_t>(end)>allContent.size()){
          cout<<"The value End exceeds the number of lines";
          return ;
      }
      
      if(start>end){
          cout<<" Invalid start and end Entered!";
          return ;
      }
      for(auto it=allContent.begin()+start-1;it!=allContent.begin()+end;it++){
        copyText.push_back(*it);
      }
  };
  void paste(int pos) {
    if (static_cast<size_t>(pos) > allContent.size()) {
        cout << "The value Position exceeds the number of lines";
        return;
    }

    undoStack.push(allContent);
    allContent.insert(allContent.begin() + pos, copyText.begin(), copyText.end());
};
  void undo(){
      if(undoStack.empty()){
          cout<<" Cannot Undo !";
          return;
      }
      redoStack.push(allContent);
      allContent=undoStack.top();
      undoStack.pop();
      
  };
  void redo(){
        if(redoStack.empty()){
          cout<<" Cannot Redo !";
          return;
      }
      undoStack.push(allContent);
      allContent=redoStack.top();
      redoStack.pop();
};
};

 int main() {
    string inputText = "Line 1\nLine 2\nLine 3\nLine 4\nLine 5";
    Notepad myNotepad(inputText);
    
    cout << "Displaying all lines:" << endl;
    myNotepad.display();
    cout << endl;
    cout<<endl<<"*******************************"<<endl;

    cout << "Displaying lines 2 to 4:" << endl;
    myNotepad.display(2, 4);
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    cout << "Displaying lines 1 to 10 (end exceeds content):" << endl;
    myNotepad.display(1, 10);
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    cout << "Displaying lines 4 to 2 (invalid range):" << endl;
    myNotepad.display(4, 2);
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    myNotepad.insert(3, "Hello i am under water!");
    cout << "After Insertion:" << endl;
    myNotepad.display();
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    myNotepad.deleteText(3);
    cout << "After Deletion:" << endl;
    myNotepad.display();
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    myNotepad.deleteText(3, 5);
    cout << "After Multiple Deletions:" << endl;
    myNotepad.display();
    cout << endl;
    
    cout<<endl<<"*******************************"<<endl;


    myNotepad.copy(2, 4);
    cout << "Copy Test: Copied lines 2 to 4" << endl;

    myNotepad.paste(2);
    cout << "Paste Test: Pasted copied lines at position 2" << endl;
    cout << "After Pasting:" << endl;
    myNotepad.display();
    cout << endl;
     cout<<endl<<"*******************************"<<endl;


    myNotepad.undo();
    cout << "Undo Test: After Undoing" << endl;
    myNotepad.display();
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    myNotepad.redo();
    cout << "Redo Test: After Redoing" << endl;
    myNotepad.display();
    cout << endl;
      cout<<endl<<"*******************************"<<endl;


    return 0;
}


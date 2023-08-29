// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Comment {
    string id;
    string userId;
    string parentId;
    string postId;
    string description;
    vector<Comment> replies;

public:

    Comment(string description){
        this->description=description;
        this->id=getUniqueId();
    }
    
    string getUniqueId(){
        static int i=0;
        i++;
        return 'c'+to_string(i);
    }
    
  void addNestedDescription(const string &id, const string &description) {
    for (auto &it : replies) {  // Use reference here
        if (it.id == id) {
            it.setDescription(description);
            return;
        }
    }
}

void addNestedDelete(const string &id) {
    int i = 0;
    for (auto &it : replies) {  // Use reference here
        if (it.id == id) {
            replies.erase(replies.begin() + i);
            return;
        }
        i++;
    }
}
    // Setters
    void setId(const string &newId) {
        id = newId;
    }

    void setUserId(const string &newUserId) {
        userId = newUserId;
    }

    void setParentId(const string &newParentId) {
        parentId = newParentId;
    }

    void setPostId(const string &newPostId) {
        postId = newPostId;
    }

    void setDescription(const string &newDescription) {
        description = newDescription;
    }

    void setReplies(const vector<Comment> &newReplies) {
        replies = newReplies;
    }

  
    // Getters
    string getId() const {
        return id;
    }

    string getUserId() const {
        return userId;
    }

    string getParentId() const {
        return parentId;
    }

    string getPostId() const {
        return postId;
    }

    string getDescription() const {
        return description;
    }

    vector<Comment> getReplies() const {
        return replies;
    }

    
    void addComment(Comment& comment){
        replies.push_back(comment);
    }
};


class Post{
    string id;
    vector<Comment>comments;
    public:
    Post(){
        this->id=getUniqueId();
    };
    
     void setId(const string &newId) {
        id = newId;
    }

    string getId() const {
        return id;
    }

    // Setter and Getter for comments
    void setComments(const vector<Comment> &newComments) {
        comments = newComments;
    }

    vector<Comment> getComments() const {
        return comments;
    }
    
    string getUniqueId(){
        static int i=0;
        i++;
        return 'p'+to_string(i);
    }
    
    void addComment(Comment&comment){
        comments.push_back(comment);
    }
    
     void addNestedComments(const string &id, Comment &comment) {
        for (auto &it : comments) {
            if (it.getId() == id) {
                it.addComment(comment);
                return;
            }
        }
    }
    
    void editComment(string parentId,string commentId,string description){
        
        for(auto it:comments){
            if(it.getId()==parentId){
                
                if(parentId==commentId){
                    it.setDescription(description);
                }else{
                    it.addNestedDescription(commentId,description);
                }
            }
        }
    }
    
    void deleteComment(string parentId,string commentId){
         
         int i=0,index=-1;

        for(auto it:comments){
            if(it.getId()==parentId){
                
                if(parentId==commentId){
                   index=i;
                   break;
                }else{
                    it.addNestedDelete(commentId);
                    break;
                }
            }
            i++;
        }
        
        if(index!=-1){
            comments.erase(comments.begin()+i);
        }
    }
};

class User {
    string id;
    string name;

public:
    User(string name) {
        this->id = getUniqueId();
        this->name = name;
    }

    // Getter for ID (no setter for ID as it's set in the constructor)
    string getId() const {
        return id;
    }

    // Setter and Getter for Name
    void setName(const string &newName) {
        name = newName;
    }

    string getName() const {
        return name;
    }

    // Function to generate unique IDs
    string getUniqueId() {
        static int i = 0;
        i++;
        return 'u' + to_string(i);
    }
    
    void addCommentToPost(Post&post,Comment&comment){
        comment.setUserId(this->id);
        comment.setPostId(post.getId());
        comment.setParentId(comment.getId());
        post.addComment(comment);
        
    };
    void replyToComment(Post&post,string parentId,Comment&comment){
         comment.setUserId(this->id);
        comment.setPostId(post.getId());
        comment.setParentId(parentId);
        post.addNestedComments(parentId,comment);
    };
   void editComment(Post &post, const string &parentId, const string &commentId, const string &description) {
    for (auto &it : post.getComments()) {
        if (it.getId() == parentId) {
            if (parentId == commentId) {
                it.setDescription(description);
            } else {
                it.addNestedDescription(commentId, description);
            }
        }
    }
}

    void deleteComment(Post&post,string parentId,string commentId){
        for(auto it:post.getComments()){
            if(it.getId()==commentId){
                if(it.getUserId()!=this->id){
                    cout<<" Unauthorized user! Cannot Delete";
                    return ;
                }
            }
        }
        
        post.deleteComment(parentId,commentId);
    };
    
};

int main() {
    User u1("L");
    Comment c1("First Comment");
    Comment c2("Second Comment");
    Comment c22("Second nested comment");
    Comment c11("First nested comment");
    Comment c12("First Second nested comment");
    Comment c13("First Third nested comment");

    Post p;
    u1.addCommentToPost(p, c1);
    u1.addCommentToPost(p, c2);
    u1.replyToComment(p, c1.getId(), c11);
    u1.replyToComment(p, c1.getId(), c12);
    u1.replyToComment(p, c1.getId(), c13);
    u1.replyToComment(p, c2.getId(), c22);

    cout << "Printing Comments and Replies:" << endl;
    for (Comment c : p.getComments()) {
        cout << c.getDescription() << endl;
        for (Comment cmt : c.getReplies())
            cout << "\t" << cmt.getDescription() << endl;
    }

    cout << "***********************************************************************" << endl;

    string s12 = "1st 2nd comment";
    string s11 = "1st 1st comment";

    u1.editComment(p, c1.getId(), c11.getId(), s11);

    cout << "Printing Comments and Replies after editing:" << endl;
    for (Comment c : p.getComments()) {
        cout << c.getDescription() << endl;
        for (Comment cmt : c.getReplies())
            cout << "\t" << cmt.getDescription() << endl;
    }

    cout << "***********************************************************************" << endl;

    u1.deleteComment(p, c1.getId(), c12.getId());

    cout << "Printing Comments and Replies after deleting:" << endl;
    for (Comment c : p.getComments()) {
        cout << c.getDescription() << endl;
        for (Comment cmt : c.getReplies())
            cout << "\t" << cmt.getDescription() << endl;
    }

    cout << "***********************************************************************" << endl;

    u1.deleteComment(p, c1.getId(), c1.getId());

    cout << "Printing Comments and Replies after deleting main comment:" << endl;
    for (Comment c : p.getComments()) {
        cout << c.getDescription() << endl;
        for (Comment cmt : c.getReplies())
            cout << "\t" << cmt.getDescription() << endl;
    }

    return 0;
}

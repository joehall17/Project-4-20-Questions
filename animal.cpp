/*
	animal.cpp

	author: L. Henke and C. Painter-Wakefield
	date: 04 November 2019

	Animal/20 questions program for CSCI 262, starter code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class node {
public:
    string data;
    node* left;
    node* right;
};

void play_game(node*);
node* read_game_tree();
void write_game_tree(node*);
void writingToFile(node* x, ofstream &fin);
void delete_game_tree(node*);
node* read_preorder(ifstream& file);

int main() {
	node* root = read_game_tree();
	if (root == nullptr) return -1;

	while (true) {
		string tmp;
		int choice;

		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		cin >> choice;

		switch (choice) {
    		case 1:
    			play_game(root);
    			break;
    		case 2:
    			write_game_tree(root);
                cout << "Game file saved in 'animal_game_tree.txt'\n\n" << endl;
    			break;
    		case 3:
    			break;
    		default:
    			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}

	delete_game_tree(root);
	return 0;
}

/**
 * Sets up the recursive call to the read_preorder
 * @return root of the tree
 */
node* read_game_tree() {
    // TODO: Implement me. See implementation hints! Reading is more complex than it may seem.
    ifstream file("animal_game_tree.txt");
    node *root = read_preorder(file);
    file.close();
    return root;
}

node* read_preorder(ifstream& file){
    node* root = new node;
    string x;
    getline(file, x);
    if((x).at(1) == 'Q'){
       root->data = x.substr(3);
       root->left = read_preorder(file);
       root->right = read_preorder(file);
    }
    else{
        root->data = x.substr(3);
        root-> left = nullptr;
        root->right = nullptr;
    }
    root->data = x.substr(3);
    return root;
}


void play_game(node* root) {
    // TODO: Implement me.
    bool answer;
    char c;
    char add;
    node* sec;
    vector<string> questions;

    while (root != nullptr){
        cout << root -> data << " (y/n): ";
        cin >> c;

        if (c == 'y'){
            questions.push_back(root -> data + " YES");

            if ((root -> left == nullptr && root -> right == nullptr)){
                cout << "YAY! I guessed your animal!\n\n";
                answer = 1;

                ///hopefully good
                break;
            }

            sec = root;
            root = root -> left;
        }
        else if (c == 'n'){
            questions.push_back(root -> data + " NO");

            if ((root -> left == nullptr && root -> right == nullptr)){
                cout << "BOO! I don't know!" << endl << endl;
                answer = 0;


                break;
            }

            sec = root;

            root = root -> right;
        }

    }

    if(answer == 0){
        cout << "Would you like to expand the game tree? [y/n]: ";
        cin >> add;
        ///Works i think
        cin.ignore();

        if(add == 'y'){
            node* nQ = new node;
            node* a = new node;
            node* q = root;
            cout << "I asked the following: " << endl;

            for(const string& s: questions){
                cout << s << endl;
            }
            cout << "" << endl;

            string userq;
            string usera;

            cout << "Enter a new animal in the form of a question," << endl << "e.g., 'Is it a whale?': " ;
            getline(cin, usera);
            cout << "Now enter a question for which the answer is 'yes' for your new" << endl << "animal, and which does not contradict your previous answers: ";
            getline(cin, userq);
            cout << endl;

            ///Point to for answer
            a -> data = usera;

            a -> right = nullptr;
            a -> left = nullptr;

            ///The new Question point
            nQ -> data = userq;

            nQ -> right = q;
            nQ -> left = a;


            sec -> right = nQ;
        }

    }
}

void write_game_tree(node* root) {
    ofstream fin("animal_game_tree.txt");
    writingToFile(root, fin);
}

void writingToFile(node* x, ofstream &fin){
    ///Base case
    if (x == nullptr){
        return;
    }

    if (x -> left == nullptr && x -> right == nullptr){
        fin << "#A " + x -> data << endl;
    }
    else{
        fin << "#Q " + x -> data << endl;
    }
    ///Write the left
    writingToFile(x -> left, fin);

    ///Write to the right
    writingToFile(x -> right, fin);
}


// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "AssassinsList.h"
#include "strlib.h"
#include "cassert"

AssassinsList::AssassinsList(istream& input) {
    // TODO: write this member
    gameRing_begin = NULL;
    graveyard_begin = NULL;
    gameRing_size = 0;
    graveyard_size = 0;

    assert(input!=NULL);

    while(true){
        string name;
        getline(input, name);
        if(input.fail()) break;
        if(gameRing_begin==NULL) gameRing_begin = new Node(name,NULL);
        else{
            Node *current = gameRing_begin;
            gameRing_begin = new Node(name,current);
        }
        gameRing_size++;
    }

    Node *current = gameRing_begin;
    while(current->next!=NULL)
        current=current->next;
    current->next=gameRing_begin;
}

AssassinsList::~AssassinsList() {
    // TODO: write this member
    delete gameRing_begin;
    delete graveyard_begin;
}

void AssassinsList::printGameRing() {
    // TODO: write this member
    Node *current = gameRing_begin;
    for(int i=0; i<gameRing_size; i++) {
        cout << current->name << " " << "is targeting"
             << " " << current->next->name << endl;
        current = current->next;
    }
}

void AssassinsList::printGraveyard() {
    // TODO: write this member
    Node *current = graveyard_begin;
    for(int i=0; i<graveyard_size; i++){
        cout << current->name << " " << "was eliminated by"
             << " " << current->killer << endl;
        current = current->next;
    }
}

bool AssassinsList::isAlive(string& player) {
    // TODO: write this member
    Node *current = gameRing_begin;
    for(int i=0; i<gameRing_size; i++){
        if(toLowerCase(current->name)==toLowerCase(player)) return true;
        else current = current->next;
    }
    return false;
}

bool AssassinsList::isDead(string& player) {
    // TODO: write this member
    Node *current = graveyard_begin;
    for(int i=0; i<graveyard_size; i++){
        if(toLowerCase(current->name)==toLowerCase(player)) return true;
        else current = current->next;
    }
    return false;
}

bool AssassinsList::isGameOver() {
    // TODO: write this member
    if(gameRing_size==1) return true;
    return false;
}

string AssassinsList::winner() {
    // TODO: write this member
    if(isGameOver()) return gameRing_begin->name;
    return "";
}

void AssassinsList::eliminate(string& player) {
    // TODO: write this member
    if(!isGameOver()) {
        Node* current = gameRing_begin;
        Node* preview;
        Node* eliminate;

        for(int i=0;i<gameRing_size;i++){
            if(toLowerCase(current->next->name)==toLowerCase(player)){
                preview = current;
                eliminate = current->next;
                current->next = current->next->next;
                if(eliminate == gameRing_begin) gameRing_begin = current->next;
                break;
            }
            else current = current->next;
        }

        gameRing_size--;

        if(graveyard_begin==NULL){
            graveyard_begin = new Node(eliminate->name,NULL);
            graveyard_begin->killer = preview->name;
        }
        else{
            Node* current_ptr = graveyard_begin;
            graveyard_begin = new Node(eliminate->name,current_ptr);
            graveyard_begin->killer = preview->name;
        }

        graveyard_size++;
   }
}

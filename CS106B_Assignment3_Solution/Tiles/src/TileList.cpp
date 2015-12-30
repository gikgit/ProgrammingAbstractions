// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
#include "strlib.h"

TileList::TileList() {
    // TODO: write this member
    m_size = 0;
    m_capacity = 10;
    m_element = new Tile[m_capacity]();
}

TileList::~TileList() {
    // TODO: write this member
    delete[] m_element;
}

void TileList::addTile(Tile tile) {
    // TODO: write this member
    if(m_size < m_capacity) {
        *(m_element+m_size) = tile;
        m_size++;
    }
}

void TileList::drawAll(GWindow& window) const{
    // TODO: write this member
    for(int i=0; i<m_size; i++)
        (m_element+i)->draw(window);
}

int TileList::indexOfTopTile(int x, int y) const{
    // TODO: write this member
    for(int i=m_size-1; i>=0; i--)
        if((m_element+i)->contains(x,y)) return i;
    return -1;
}

void TileList::raise(int x, int y) {
    // TODO: write this member
    int index = indexOfTopTile(x,y);
    Tile topmost = *(m_element+index);
    for(int i=index; i<m_size-1; i++)
        *(m_element+i) = *(m_element+i+1);
    *(m_element+m_size-1) = topmost;
}

void TileList::lower(int x, int y) {
    // TODO: write this member
    int index = indexOfTopTile(x,y);
    Tile topmost = *(m_element+index);
    for(int i=index-1; i>=0; i--)
        *(m_element+i+1) = *(m_element+i);
    *(m_element) = topmost;
}

void TileList::remove(int x, int y) {
    // TODO: write this member
    int index = indexOfTopTile(x,y);
    for(int i=index+1; i<m_size; i++)
        *(m_element+i-1) = *(m_element+i);
    m_size--;
    if(m_size==0) cout << "list is empty" << endl;
}

void TileList::removeAll(int x, int y) {
    // TODO: write this member
    int count = 0;
    int index = 0;
    for(int i=m_size-1; i>=0; i--)
        if((m_element+i)->contains(x,y)) count++;
    for(int i=0; i<m_size; i++){
        if(!(m_element+i)->contains(x,y)) {
            *(m_element+index) = *(m_element+i);
            index++;
        }
    }
    m_size-=count;
}

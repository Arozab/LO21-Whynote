#include "notes.h"
#include "notes.cpp"
#include "timing.h"
#include "timing.cpp"
#include <windows.h>

int main() {

    try{
        NotesManager& manager=NotesManager::getInstance();
       	manager.getNewArticle("22","NoteTest","Ceci est une note d'essai pour verifier le bon fonctionnement");
       	Article& a1=manager.getArticle("22");
       	a1.afficher();
       	 NotesManager& manager2=NotesManager::getInstance();
	//manager.getNewNote("22");
    }
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}



#include "notes.h"
#include "timing.h"
#include "relation.h"
#include <windows.h>

int main() {

    try{
        NotesManager& manager=NotesManager::getInstance();
       	manager.getNewArticle("22","NoteTest","Ceci est une note d'essai pour verifier le bon fonctionnement");
       	Article& a1=manager.getArticle("22");
       	a1.afficher();
       	manager.getNewNoteAvecFichier("22","NoteAvecFichierTest","Description de la note","/Documents/LO21-WHYNOTE/test.txt");
       	NoteAvecFichier& a2=manager.getNoteAvecFichier("22");
       	a2.afficher();
       /*	manager.getNewTache("4","Tache","Go farm mid","Imporant",en_cours);
       	Tache& a3=manager.getTache("3");
       	a3.afficher();*/

       //NotesManager& manager2=NotesManager::getInstance();
	//manager.getNewNote("22");
    }
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}

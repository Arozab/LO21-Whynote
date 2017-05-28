#include "notes.h"
#include "timing.h"
#include "relation.h"
#include <windows.h>

int main() {

    try{
        NotesManager& manager=NotesManager::getInstance();
       	Article& a1=manager.getNewArticle("22","NoteTest","Ceci est une note d'essai pour verifier le bon fonctionnement");
       	//Article& a1=manager.getNotes("22");
        a1.afficher();
       	manager.getNewNoteAvecFichier("22","NoteAvecFichierTest","Description de la note","/Documents/LO21-WHYNOTE/test.txt");
       	NoteAvecFichier& a2=manager.getNoteAvecFichier("22");
       	a2.afficher();
        Tache& a3=manager.getNewTache("4","Tache","Go farm mid","Important",Date(15,06,2017),en_cours);
        a3.afficher();

        //NotesManager& manager2=NotesManager::getInstance();
        //manager.getNewN("22","NoteTest1","Ceci est une note d'essai pour verifier le bon fonctionnement1");
    }
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}

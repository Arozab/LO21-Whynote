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
        Article* pt1=&a1;
        Notes& a1_bis=manager.edition(pt1);
        a1_bis.afficher();
        Notes& a1_old=a1_bis.getOldVersion(0);
        a1_old.afficher();

       	NoteAvecFichier& a2=manager.getNewNoteAvecFichier("11","NoteAvecFichierTest","Description de la note","/Documents/LO21-WHYNOTE/test.txt");
       	a2.afficher();
       	NoteAvecFichier* pt2=&a2;
        Notes& a2_bis=manager.edition(pt2);
        a2_bis.afficher();

        Tache& a3=manager.getNewTache("4","Tache","Go farm mid","Important",Date(15,06,2017),en_cours);
        a3.afficher();
        Tache* pt3=&a3;
        Notes& a3_bis=manager.edition(pt3);
        a3_bis.afficher();

        //NotesManager& manager2=NotesManager::getInstance();
        //manager.getNewN("22","NoteTest1","Ceci est une note d'essai pour verifier le bon fonctionnement1");
    }
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}

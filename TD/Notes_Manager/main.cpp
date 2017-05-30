#include "Notes.h"
#include <windows.h>

void creation(){
	NotesManager& manager=NotesManager::getInstance();
	Article& a1=manager.getNewArticle("article_1");
	a1.setTitle("Avant Propos");
	a1.setText("Il faut toujours bien lire un sujet avant de commencer.");

	Article& a2=manager.getNewArticle("article_2");
	a2.setTitle("Objectifs");
	a2.setText("Comprendre la difference entre la composition et l'aggregation ainsi que les relations entre classes.");

	Article& a3=manager.getNewArticle("article_3");
	a3.setTitle("Objectifs");
	a3.setText("Apprendre comment implementer un design pattern.");
}

void affichage(){
    NotesManager& manager=NotesManager::getInstance();	manager.load("tmp.dat");
	Article& a1=manager.getArticle("article_1");
	Article& a2=manager.getArticle("article_2");
	Article& a3=manager.getArticle("article_3");
	std::cout<<a1<<"\n";
	std::cout<<a2<<"\n";
	std::cout<<a3<<"\n";


	/*NotesManager& m=NotesManager::getInstance();	m.load("tmp.dat");
	NotesManager::Iterator it;

	for(it= m.getIterator();!it.isDone(); it.next()){
		std::cout<<it.current()<<"\n";
		it.current().setText(""); // modification possible
	}*/
	//...
	/*const NotesManager& mconst=NotesManager::getInstance();
	for(NotesManager::ConstIterator it= mconst.getIterator();!it.isDone();it.next()){
		std::cout<<it.current()<<"\n"; //ok
		//it.current().setText(""); // modification impossible
	}*/

}

int main() {
	try {
		//creation(); // cette ligne peut être mise en commentaire après la 1ère exécution
		affichage();
	}
	catch(NotesException& e){
		std::cout<<e.getInfo()<<"\n";
	}
	system("pause");
	return 0;
}

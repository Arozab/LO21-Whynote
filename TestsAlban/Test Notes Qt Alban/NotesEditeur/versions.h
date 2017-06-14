
#include <QtGui>
#include <QtXml>
#include <QWidget>

#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
#include <QComboBox>

#include "notes.h"

using namespace std;
class VersionsManager{
    
    //doit etre déclaré en friend class dans notes.h,et les différents types de notes

	private:
		vector<Notes*> versions;
		unsigned int nbVersions;
        const QString vFile;	//pour le fichier contenant les notes
		QString vId;

		VersionsManager();
		~VersionsManager();
		VersionsManager(const VersionsManager& m);
		VersionsManager& operator=(const VersionsManager& m);

		struct Handler
		{
			VersionsManager* instance;
			Handler():instance(nullptr){}
			~Handler(){
				delete instance;
				instance=nullptr;
			}
		};
		static Handler handler;	//le destructeur sera appelé automatiquement à la fin du programme pour cet objet

	public:
        static VersionsManager& getInstance();
        static void libererInstance();
        static VersionsManager& recupererInstance();

        QString getFilename()const{return vFile;}
		unsigned int getNbVersions() const {return nbVersions;}
        Notes* getVersions(unsigned int i)const{return versions[i];} //permet d'afficher individuellement chaque version
        QString getId()const{return vId;}
        
        void addVersion( Notes* n,QString& id);  //permet d'ajouter d'ajouter une version dans le fichier des versions
		void loadVersion(const QString& id); //permet de charger les versions dans le vecteur & changer d'id & recuperer le nombre de versions
        void restoreVersion(const QString& id, unsigned int numeroVersion);

        void loadTacheFromXML(vector<Notes*> versions, QXmlStreamReader& xml,const QString& idSearch);//Sous-fonction de loadVersion
        void loadFichierFromXML(vector<Notes*> versions, QXmlStreamReader& xml,const QString& idSearch);//Sous-fonction de loadVersion
        void loadArticleFromXML(vector<Notes*> versions, QXmlStreamReader& xml,const QString& idSearch);//Sous-fonction de loadVersion
        
        QDomElement VersionXMLFactory(QString& type, Notes* n,QDomDocument doc);
        void updateComboBox(QComboBox* combobox);

};
